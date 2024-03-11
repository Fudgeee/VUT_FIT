/**
 * ISA
 * @file dhcp-stasts.h
 * @authors Adrian Matusik (xmatus35)
 * @brief DHCP monitoring
 */

#ifndef __DHCP_STATS_H__
#define __DHCP_STATS_H__

#include <netinet/in.h>

struct ether_header *eptr;
struct ip *my_ip;
struct udphdr *udp_hdr;
struct udphdr *dhcp_hdr;
struct dhcp_packet *dhcp_p;

struct dhcp_packet {
    uint8_t  op; // Operation
    uint8_t  htype; // Hardware address type
    uint8_t  hlen; // Hardware address length
    uint8_t  hops; 
    uint32_t xid; // Transaction ID
    uint16_t secs; 
    uint16_t flags; 
    in_addr ciaddr; // Client IP address
    in_addr yiaddr; // Your IP address
    in_addr siaddr; // Server IP address
    in_addr giaddr; // Gateway IP address
    char chaddr[16]; // Client hardware address
    char sname[64]; // Optional server host name
    char file[128]; // Boot file name
    char mcookie[4]; // Magic cookie
    char options[312]; // DHCP options
};

#endif