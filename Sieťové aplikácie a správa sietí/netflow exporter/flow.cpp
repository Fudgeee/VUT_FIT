#include <iostream>
#include <string.h>
#define __FAVOR_BSD
#include <pcap.h>
#include <ctype.h>
#include "flow.h"
#include <map>

#include <errno.h>
#define __FAVOR_BSD
#include <sys/socket.h>
#define __FAVOR_BSD
#include <netinet/in.h>
#define __FAVOR_BSD
#include <netinet/ip.h>
#define __FAVOR_BSD
#include <netinet/tcp.h>
#define __FAVOR_BSD
#include <netinet/udp.h>
#define __FAVOR_BSD
#include <netinet/ip_icmp.h>
#define __FAVOR_BSD
#include <arpa/inet.h>
#define __FAVOR_BSD
#include <netinet/if_ether.h> 
#include <inttypes.h>
#include <tuple>
#include<unistd.h>
#define __FAVOR_BSD
#include<netdb.h>
#define __FAVOR_BSD
#include <netinet/ether.h> 
#include <time.h>

using namespace std;

#ifndef PCAP_ERRBUF_SIZE
#define PCAP_ERRBUF_SIZE (256)
#endif
#define SIZE_ETHERNET (14)       // offset of Ethernet header to L3 protocol
#define MICROSECS (1000000)     // const of conversion to microseconds
time_t active_timer = 0;
time_t inactive_timer = 0;
int flow_cache_size = 0;
string netflow_collector = "127.0.0.1:2055";
string c_ip = "127.0.0.1";
string c_port = "2055";
uint32_t src_ip;
uint32_t dst_ip;
uint16_t src_port;
uint16_t dst_port;
uint8_t protocol;
uint8_t flag = 0;
timeval first_time;     // init time
timeval time_last;      // time of actual record
uint16_t bytes;
uint8_t my_tos;
bool booted = false;    // control if init time exists
int flows_total = 0;    // count of all flows
int exp_size_packet;
int n;
char errbuf[PCAP_ERRBUF_SIZE];  // constant defined in pcap.h
const u_char *packet;
struct ip *my_ip;
const struct tcphdr *my_tcp;    // pointer to the beginning of TCP header
const struct udphdr *my_udp;    // pointer to the beginning of UDP header
const struct icmphdr *my_icmp;  // pointer to the beginning of ICMP header
struct pcap_pkthdr header;  
struct ether_header *eptr;
FILE *filename = stdin;
pcap_t *handle;         // file/device handler
u_int size_ip;

tuple<uint32_t, uint32_t, uint16_t, uint16_t, uint8_t> key_tuple;
tuple<tuple<uint32_t, uint32_t, uint16_t, uint16_t, uint8_t>, int> exp_key_tuple;
map <tuple<uint32_t, uint32_t, uint16_t, uint16_t, uint8_t>, nf_v5_record_t> flow_map;
map <tuple<tuple<uint32_t, uint32_t, uint16_t, uint16_t, uint8_t>, int>, nf_v5_record_t> exp_flow_map; //expired flows are sent to exp map to wait for conditions to send

bool IsDigitFunc(char *str){ //control if values contain only numerical characters
    for(int i = 0; i < strlen(str); i++){
        if (isdigit(str[i]) == int(0)){
            return false;
        }
    }
    return true;
}

void argParse(int argc, char *argv[]){ // parsing of arguments

    active_timer = 60*MICROSECS; // defaul value of active timer in microseconds
    inactive_timer = 10*MICROSECS; // defaul value of active timer in microseconds
    flow_cache_size = 1024; // defaul value of flow cache
    for (int i = 1; i < argc; i++){
        if(strcmp(argv[i], "-f") == 0){
            filename = fopen(argv[++i],"r");
            n = 0;
            continue;
        }
        if(strcmp(argv[i], "-c") == 0){
            netflow_collector = argv[++i];
            c_ip = netflow_collector.substr(0, netflow_collector.find(":")); // ip from netflow_collector
            c_port = netflow_collector.substr(netflow_collector.find(":")+1); // port from netflow_collector
            continue;
        }
        if(strcmp(argv[i], "-a") == 0){
            if(IsDigitFunc(argv[++i])){
                active_timer = (atoi(argv[i]))*MICROSECS; // active timer in microseconds
            }
            else{
                printf("Active_timer requires number!\n");
                exit(1);
            }
            continue;
        }
        if(strcmp(argv[i], "-i") == 0){
            if(IsDigitFunc(argv[++i])){
                inactive_timer = (atoi(argv[i]))*MICROSECS; // inactive timer in microseconds
            }
            else{
                printf("Inactive_timer requires number!\n");
                exit(1);
            }
            continue;
        }
        if(strcmp(argv[i], "-m") == 0){
            if(IsDigitFunc(argv[++i])){
                flow_cache_size = atoi(argv[i]); // flow cache size
            }
            else{
                printf("Flow_cache_size requires number!\n");
                exit(1);
            }
            continue;
        }
        printf("Wrong value \"%s\".\n", argv[i]); // wrong value in arguments
        exit(1);
    }
}

void flow_create(tuple<uint32_t, uint32_t, uint16_t, uint16_t, uint8_t> key_tuple, uint8_t flag, uint16_t bytes, timeval time_last1){ // function for creation of flows and inserting them to map
    nf_v5_record_t *flow_record = new nf_v5_record_t;
    if(flow_map.find(key_tuple) == flow_map.end()){ 
        // flow not found in map -> creating new flow
        if (!booted){ // control for setting init time
            first_time = time_last1;
            booted = true;
        }
        flow_record->srcaddr = src_ip;
        flow_record->dstaddr = dst_ip;
        flow_record->srcport = src_port;
        flow_record->dstport = dst_port;
        flow_record->prot = protocol;
        flow_record->First = ((time_last1.tv_sec - first_time.tv_sec)*MICROSECS + time_last1.tv_usec - first_time.tv_usec); // first time of flow in MICROSECONDS
        flow_record->dPkts = 1;
        flow_record->tcp_flags = flag;
        flow_record->dOctets = bytes;
        flow_record->Last = flow_record->First; // last time of flow in MICROSECONDS
        flow_record->tos = my_tos;
        // setting unused values to 0
        flow_record->nexthop = 0;
        flow_record->input = 0;
        flow_record->output = 0;
        flow_record->pad1 = 0;
        flow_record->src_as = 0;
        flow_record->dst_as = 0;
        flow_record->src_mask = 0;
        flow_record->dst_mask = 0;
        flow_record->pad2 = 0;
        //
        flow_map[key_tuple] = *flow_record;
    }
    else if ((((((time_last.tv_sec - first_time.tv_sec)*MICROSECS) + time_last.tv_usec - first_time.tv_usec) - (flow_map[key_tuple].Last)) > inactive_timer)|| (flow_map[key_tuple].tcp_flags & TH_FIN) || (flow_map[key_tuple].tcp_flags & TH_RST) || (((flow_map[key_tuple].Last) - (flow_map[key_tuple].First)) > active_timer)){
        // control of previous packet inactive timer when flow already exists, after removing inactive flow, new flow is inserted
        exp_key_tuple = make_tuple((key_tuple), (int)exp_flow_map.size());
        exp_flow_map[exp_key_tuple] = flow_map[key_tuple]; // moving expired flows to expired map to wait for ... conditions to export
        flow_map.erase(flow_map.find(key_tuple)); // remove flow from active map
        // creating new flow
        nf_v5_record_t *flow_record1 = new nf_v5_record_t;
        flow_record1->srcaddr = src_ip;
        flow_record1->dstaddr = dst_ip;
        flow_record1->srcport = src_port;
        flow_record1->dstport = dst_port;
        flow_record1->prot = protocol;
        flow_record1->First = ((time_last1.tv_sec - first_time.tv_sec)*MICROSECS + time_last1.tv_usec - first_time.tv_usec);
        flow_record1->dPkts = 1;
        flow_record1->tcp_flags = flag;
        flow_record1->dOctets = bytes;
        flow_record1->Last = flow_record1->First;
        flow_record1->tos = my_tos;
        // setting unused values to 0
        flow_record1->nexthop = 0;
        flow_record1->input = 0;
        flow_record1->output = 0;
        flow_record1->pad1 = 0;
        flow_record1->src_as = 0;
        flow_record1->dst_as = 0;
        flow_record1->src_mask = 0;
        flow_record1->dst_mask = 0;
        flow_record1->pad2 = 0;
        //
        flow_map[key_tuple] = *flow_record1;
    }
    else{
        // updating values of flow, if flow exists
        flow_map[key_tuple].tcp_flags |= flag;
        flow_map[key_tuple].dOctets += bytes;
        flow_map[key_tuple].Last = ((time_last1.tv_sec - first_time.tv_sec)*MICROSECS + time_last1.tv_usec - first_time.tv_usec);
        flow_map[key_tuple].dPkts += 1;
    }
    flows_total++; // incresing count of total packets
}

nf_v5_header_t header_create(uint16_t size, uint32_t sysuptime, uint32_t secs, uint32_t nsecs, uint32_t seq){
    nf_v5_header_t flow_header;
    flow_header.version = htons(5);
    flow_header.count = htons(size);
    flow_header.SysUptime = ntohl(sysuptime);
    flow_header.unix_secs = htonl(secs);
    flow_header.unix_nsecs = htonl(nsecs); //nanoseconds
    flow_header.flow_sequence = htonl(flows_total);
    flow_header.engine_type = 0;
    flow_header.engine_id = 0;
    flow_header.sampling_interval = htons(0);
    return flow_header;
}

void export_function(nf_v5_packet_t packet_packet, string c_ip , string c_port, int size_p){ // function for establishing UDP connection
    int sock;                        // socket descriptor
    struct sockaddr_in server; // address structures of the server and the client
    struct hostent *servent;         // network host entry required by gethostbyname()
    memset(&server,0,sizeof(server)); // erase the server structure
    server.sin_family = AF_INET;                  
    // make DNS resolution of the first parameter using gethostbyname()
    if ((servent = gethostbyname(c_ip.c_str())) == NULL){ // check the first parameter
        printf("gethostbyname() failed\n");
        exit(1);
    }
    // copy the first parameter to the server.sin_addr structure
    memcpy(&server.sin_addr,servent->h_addr,servent->h_length);
    server.sin_port = htons(atoi(c_port.c_str()));        // server port (network byte order)    
    if ((sock = socket(AF_INET , SOCK_DGRAM , IPPROTO_UDP)) == -1){   //create a client socket
        printf("socket() failed\n");
        exit(1);
    }
    sendto(sock, &packet_packet, size_p, 0, (struct sockaddr *)&server, sizeof(server)); // sending packet to collector
    close(sock);
}

nf_v5_packet_t packet_create(map <tuple<tuple<uint32_t, uint32_t, uint16_t, uint16_t, uint8_t>, int>, nf_v5_record_t> *mapa){
    nf_v5_packet_t packet_packet;
    packet_packet.header = header_create(exp_flow_map.size(), (((time_last.tv_sec - first_time.tv_sec)*MICROSECS) + time_last.tv_usec - first_time.tv_usec)/1000, time_last.tv_sec, time_last.tv_usec*1000, flows_total);
    int i=0;
    for (auto itr = exp_flow_map.begin(); itr != exp_flow_map.end(); itr++){
        packet_packet.records[i].srcaddr = htonl(itr->second.srcaddr);
        packet_packet.records[i].dstaddr = htonl(itr->second.dstaddr);
        packet_packet.records[i].srcport = htons(itr->second.srcport);
        packet_packet.records[i].dstport = htons(itr->second.dstport);
        packet_packet.records[i].prot = itr->second.prot;
        packet_packet.records[i].First = htonl(itr->second.First/1000);
        packet_packet.records[i].dPkts = htonl(itr->second.dPkts);
        packet_packet.records[i].tcp_flags = (itr->second.tcp_flags);
        packet_packet.records[i].dOctets = htonl(itr->second.dOctets);
        packet_packet.records[i].Last = htonl(itr->second.Last/1000);
        packet_packet.records[i].tos = itr->second.tos;
        //  setting unused values to 0
        packet_packet.records[i].nexthop = 0;
        packet_packet.records[i].input = 0;
        packet_packet.records[i].output = 0;
        packet_packet.records[i].pad1 = 0;
        packet_packet.records[i].src_as = 0;
        packet_packet.records[i].dst_as = 0;
        packet_packet.records[i].src_mask = 0;
        packet_packet.records[i].dst_mask = 0;
        packet_packet.records[i].pad2 = 0;
        //
        i++;
        if(i > 29){
            exp_size_packet = (sizeof(nf_v5_header_t) + (sizeof(nf_v5_record_t) * exp_flow_map.size()));
            //export_function(packet_packet, c_ip, c_port, exp_size_packet);
            exp_flow_map.clear();
            break;
        }
    //}
    }
    return packet_packet;
}

int main(int argc, char *argv[]){
    argParse(argc, argv);
    handle = pcap_fopen_offline(filename, errbuf);
    if (handle == NULL){
                printf("Couldn't open file for reading\n");
                exit(1);
	        }
    while ((packet = pcap_next(handle,&header)) != NULL){
        n++;  
        eptr = (struct ether_header *) packet; // read the Ethernet header
        switch (ntohs(eptr->ether_type)){               // see /usr/include/net/ethernet.h for types
            case ETHERTYPE_IP: // IPv4 packet
                my_ip = (struct ip*) (packet+SIZE_ETHERNET);        // skip Ethernet header
                size_ip = my_ip->ip_hl*4;                           // length of IP header 
                src_ip = ntohl(my_ip->ip_src.s_addr);
                dst_ip = ntohl(my_ip->ip_dst.s_addr);
                time_last = header.ts;
                switch (my_ip->ip_p){
                    case 1: // ICMP protocol
                        my_icmp=(struct icmphdr *) (packet+SIZE_ETHERNET+size_ip); // pointer to the ICMP header
                        my_tos = my_ip->ip_tos;
                        src_port = 0;
                        dst_port = 0;
                        protocol = my_ip->ip_p;
                        flag = 0;
                        bytes = 56;
                        break;
                    case 6: // TCP protocol
                        my_tcp = (struct tcphdr *) (packet+SIZE_ETHERNET+size_ip); // pointer to the TCP header
                        flag = my_tcp->th_flags;
                        src_port = ntohs(my_tcp->th_sport);
                        dst_port = ntohs(my_tcp->th_dport);
                        protocol = my_ip->ip_p;
                        bytes = (ntohs(my_ip->ip_len) - size_ip); 
                        break;
                    case 17: // UDP protocol
                        my_udp = (struct udphdr *) (packet+SIZE_ETHERNET+size_ip); // pointer to the UDP header
                        src_port = ntohs(my_udp->uh_sport);
                        dst_port = ntohs(my_udp->uh_dport);
                        protocol = my_ip->ip_p;
                        flag = 0;
                        bytes = ntohs(my_udp->uh_ulen);
                        break;
                    default: 
                        break;
                    }
            default:
                break;
            } 
        key_tuple = make_tuple(src_ip, dst_ip, src_port, dst_port, protocol); // creation of tuple
        flow_create(key_tuple,flag,bytes,time_last); // creation of flow
    }
    pcap_close(handle);
    exp_size_packet = (sizeof(nf_v5_header_t) + (sizeof(nf_v5_record_t) * exp_flow_map.size()));
    for (auto itr = flow_map.begin(); itr != flow_map.end(); itr++){
        if (exp_flow_map.size() == 30){
                export_function(packet_create(&exp_flow_map), c_ip, c_port, exp_size_packet);
        }
         exp_key_tuple = make_tuple((itr->first), (int)exp_flow_map.size());
         exp_flow_map[exp_key_tuple] = flow_map[itr->first];
    }  
    exp_size_packet = (sizeof(nf_v5_header_t) + (sizeof(nf_v5_record_t) * exp_flow_map.size()));
    export_function(packet_create(&exp_flow_map), c_ip, c_port, exp_size_packet);
    cout << flow_map.size() << " Map size \n" ;
    cout << exp_flow_map.size() << " ExpMap size \n" ;
    exp_flow_map.clear();
    flow_map.clear();
    return 0;
}