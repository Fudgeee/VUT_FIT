/**
 * ISA
 * @file dhcp-stasts.cpp
 * @authors Adrian Matusik (xmatus35)
 * @brief DHCP monitoring
 */

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <string.h>
#include <pcap.h>
#include <netinet/if_ether.h>
#include <netinet/ether.h>
#include <netinet/ip.h>
#include <netinet/udp.h>
#include <arpa/inet.h>
#include <vector>
#include <cmath>
#include <sstream>
#include <syslog.h>
#include "dhcp-stats.h"
#include <signal.h>

#define __FAVOR_BSD

#ifndef PCAP_ERRBUF_SIZE
#define PCAP_ERRBUF_SIZE (256)
#endif

// Definície DHCP konštánt
#define DHCP_SERVER_PORT 67
#define DHCP_CLIENT_PORT 68

// Definície typov DHCP správ
#define DHCP_ACK 5
#define DHCP_OPCODE 53

char errbuf[PCAP_ERRBUF_SIZE];  // konštanta definovaná v pcap.h
pcap_t *handle;

std::vector<std::string> ipPrefixes; // vektor na uchovávanie prefixov IP adries
std::vector<int> maxHosts;
std::vector<int> allocatedAddresses;
std::vector<double> utilization;

//Kontrola ci prefix obsahuje len numerické znaky alebo bodky
bool isValidPrefix(const std::string &prefix) {
    for (char c : prefix) {
        if (!std::isdigit(c) && c != '.') {
            return false; // Nie je číslica ani bodka
        }
    }
    return true;
}

// Funkcia na výpočet počtu hostiteľov z prefixu siete
unsigned int calculateMaxHosts(int prefix) {
    return static_cast<unsigned int>(pow(2, (32 - prefix))) - 2;
}

// Funkcia na získanie adresy a masky siete
void getMaxHostsAndControlPrefix(const std::string& prefix) {
    std::vector<std::string> parts;
    std::stringstream ss(prefix);
    std::string part;
    std::vector<int> octets;
    std::string octet;

    while (std::getline(ss, part, '/')) {
        parts.push_back(part);
    }
    
    if (parts.size() != 2) {
        std::cout << "Invalid prefix format: " << prefix  << std::endl;
        exit(6);
    }

    if (!isValidPrefix(const_cast<char*>(parts[1].c_str()))) {
        std::cout << "Invalid prefix format: " << prefix  << std::endl;
        exit(6);
    }

    if (parts[0].size() < 7 || parts[0].size() > 15) {
        std::cout << "Invalid prefix format: " << prefix  << std::endl;
        exit(6);
    }

    if (!isValidPrefix(const_cast<char*>(parts[0].c_str()))) {
        std::cout << "Invalid prefix format: " << prefix << std::endl;
        exit(6);
    }

    std::stringstream sss(parts[0]);

    while (std::getline(sss, octet, '.')) {
        int value = std::stoi(octet);
        octets.push_back(value);

        if (octets.size() > 4) {
            std::cout << "IP Address must always contain 4 octets! Invalid prefix format:" << prefix << std::endl;
            exit(25);
        }

        if (value < 0 || value > 255) { // Kontrola rozsahu 0-255
            std::cout << "Invalid IP address range. IP Address range must be between 0-255" << std::endl;
            exit(22);
        }
    }

    int maxHost = std::stoi(parts[1]);
    if (maxHost < 0 || maxHost > 30) {
        std::cout << "Prefix size must be between 0-30. " << std::endl;
        exit(7);
    }
    maxHosts.push_back(maxHost);
}

// Funkcia na kontrolu, či adresa patrí pod daný prefix
bool isAddressUnderPrefix(const std::string& address, const std::string& prefix) {
    std::string networkAddress;
    std::istringstream ss(prefix);
    int prefixLength;
    std::getline(ss, networkAddress, '/');
    ss >> prefixLength;

    in_addr addr;
    inet_aton(address.c_str(), &addr);

    in_addr netAddr;
    inet_aton(networkAddress.c_str(), &netAddr);

    uint32_t mask;
    // Vytvorenie bitového maskovania podsiete
    if (prefixLength == 0) {
        mask = 0x00000000;
    }
    else {
        mask = 0xFFFFFFFF << (32 - prefixLength);
    }

    // Prevedenie adries do bitového formátu
    uint32_t network = ntohl(netAddr.s_addr) & mask;
    uint32_t inputAddress = ntohl(addr.s_addr);

    return (network == (inputAddress & mask));
}

// Funkcia na inicializáciu ncurses
void initializeScreen() {
    initscr();      // Inicializácia obrazovky
    cbreak();       // Neblokovať vstup
    noecho();       // Nezobrazovať vstup na obrazovke
}

// Funkcia na zobrazenie údajov o prefixoch v ncurses
void displayIPPrefixes(const std::vector<std::string> ipPrefixes, const std::vector<int> maxHosts, const std::vector<int> allocatedAddresses) {
    printw("%-20s %-10s %-20s %s\n", "IP-Prefix", "Max-hosts", "Allocated addresses", "Utilization");
    std::string msg;

    for (int i = 0; i < ipPrefixes.size(); ++i) {
        double utilization = (static_cast<double>(allocatedAddresses[i]) / static_cast<double>(calculateMaxHosts(maxHosts[i]))) * 100.0;

        if (utilization > 50){
            msg = "prefix " + ipPrefixes[i] + " exceeded 50%% of allocations .";
            syslog(LOG_INFO, "%s", msg.c_str());
            mvprintw(i+1, 67, "%s", "prefix exceeded 50\045 of allocations");
        }

        mvprintw(i+1, 0, "%-20s %-10u %-20d %.2f%%", ipPrefixes[i].c_str(), static_cast<unsigned int>(calculateMaxHosts(maxHosts[i])), allocatedAddresses[i], utilization);
    }

    refresh(); // Aktualizácia obrazovky
}

// Funkcia na zistenie či je daný paket platný DHCP ACK
bool isValidDHCP_ACK(const struct dhcp_packet *dhcp_p) {
    const unsigned char *options = (unsigned char *)dhcp_p->options;
    int counter = 0;
    for (int i = 0; i < sizeof(dhcp_p->options) && (dhcp_p->options[i] != 255); i += dhcp_p->options[i+1] + 2) { // Prehľadávanie pola options v DHCP pakete
        if (options[i] == DHCP_OPCODE && options[i+1] == 1 && options[i+2] == DHCP_ACK) { // Ak našlo kód 53 (DHCP ACK)
            counter++;
        }
        
        switch (options[i]) {
            case 51: // obsahuje IP address lease time
            case 54: // obsahuje Server identifier
                counter++;
                break;
            case 50: // neobsahuje Requested IP address
            case 55: // neobsahuje Parameter request list
            case 57: // neobsahuje Maximum DHCP message size
            case 61: // neobsahuje Client-identifier
                counter--;
                break;
        default:
            break;
        }
    }

    if (counter == 3) {
        return true; // Je platný
    }

    return false; // Neni platný
}

void packetHandler(unsigned char *userData, const struct pcap_pkthdr* pkthdr, const unsigned char* packet) {
    std::string yiaddr;
    eptr = (struct ether_header*) packet; // Struktura pre Ethernetový rámec

    if(ntohs(eptr->ether_type) == ETHERTYPE_IP) {  // Kontrola, ci je to IP4 paket
        my_ip = (struct ip*)(packet + sizeof(struct ether_header)); // Načitanie IP hlavičky

        if (my_ip->ip_p == IPPROTO_UDP) { // Kontrola, ci je to UDP paket
            udp_hdr = (struct udphdr*)(packet + sizeof(struct ether_header) + (my_ip->ip_hl << 2));

            if ((ntohs(udp_hdr->source) == DHCP_SERVER_PORT && ntohs(udp_hdr->dest) == DHCP_CLIENT_PORT)) { // Ak sú porty 67 (server) a 68 (klient)

                dhcp_p = (struct dhcp_packet*)(packet + ETHER_HDR_LEN + (my_ip->ip_hl << 2) + sizeof(struct udphdr));

                yiaddr = inet_ntoa(dhcp_p->yiaddr);

                if (isValidDHCP_ACK(dhcp_p)) {
                    for (int j = 0; j < ipPrefixes.size(); j++) {
                        const std::string prefix = ipPrefixes[j];

                        if (isAddressUnderPrefix(yiaddr, prefix)) {
                            allocatedAddresses[j]++;
                        } 
                    }
                }
            }
        }
    }
}

void handle_ctrlc(int signum) {
    if (signum == SIGINT) {
	    endwin(); // Ukončenie práce s ncurses
        pcap_close(handle);
        exit(0);
    }
}

int main(int argc, char *argv[]){
    bool control = false;
    std::string filename;
    char *dev;
    int i = 1;
    int c;

    if (signal(SIGINT, handle_ctrlc) == SIG_ERR) {
        std::cerr << "It is not possible to set the signal handling. " << std::endl;
        exit(50);
    }

    while((c = getopt(argc, argv, "r:i:")) != -1){
        switch (c){
        case 'r':
            if (control != false) { // Kontrola či nebol zadaný žiadny iný parameter
                std::cerr << "You can't use -r and -i argument at once. Choose only one of them " << errbuf << std::endl;
                exit(5);
            }

            filename = optarg;
            handle = pcap_open_offline(filename.c_str(), errbuf);

            if (handle == NULL){
                std::cerr << "Couldn't open PCAP file: " << errbuf << std::endl;
                exit(2);
            }

            i = i + 2;
            control = true;
            break;
        case 'i':
            if (control != false) { // Kontrola či nebol zadaný žiadny iný parameter
                std::cerr << "You can't use -r and -i argument at once. Choose only one of them. " << errbuf << std::endl;
                exit(5);
            }
            dev = optarg;         

            handle = pcap_open_live(dev, BUFSIZ, 1, 1000, errbuf);

            if (handle == NULL) {
                std::cerr << "Couldn't open interface " << dev << ": " << errbuf << std::endl;
                exit(3);
            }

            i = i + 2;
            control = true;
            break;
        default:
            std::cout << "Wrong parameter was inserted! " << std::endl;
            exit(19);
        }
    }

    if (i == 1) {
        std::cout << "Required parameter is missing! " << std::endl;
            exit(1);
    }

    if (argc < 4) {
        std::cout << "At least one IP prefix is required! " << std::endl;
            exit(11);
    }

    for (; i < argc; i++) {
        ipPrefixes.push_back(argv[i]);
        allocatedAddresses.push_back(0);
    }

    for (const auto& prefix : ipPrefixes) {
        getMaxHostsAndControlPrefix(prefix);
    }

    initializeScreen(); // Inicializácia obrazovky s ncurses

    pcap_loop(handle, 0, packetHandler, NULL);
                
    displayIPPrefixes(ipPrefixes, maxHosts, allocatedAddresses);

    getch(); // Čakanie na stlačenie klávesy od užívateľa
	endwin(); // Ukončenie práce s ncurses

    pcap_close(handle);
	return 0;
}