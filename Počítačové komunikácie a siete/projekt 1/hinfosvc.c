/*
 * IPK project1
 *
 * Adrián Matušík (xmatus35@stud.fit.vutbr.cz)
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

char buff1[1024];
char* Hostname(void){
    memset(buff1, 0, sizeof(buff1));
    FILE* hfile = fopen("/proc/sys/kernel/hostname", "r");
    if(hfile == NULL){
        fprintf(stderr, "ERROR: hostname not found!\n");
        exit(1);
    }
    fgets(buff1, 1024, hfile);
    fclose(hfile);
    return buff1;
}

char buff2[1024];
char* CPUname(){
    memset(buff2, 0, sizeof(buff2));
    FILE* nfile = popen("cat /proc/cpuinfo | grep \"model name\" | head -n 1 | cut -d' ' -f3-","r");
    if(nfile == NULL){
        fprintf(stderr, "ERROR: CPU-name not found!\n");
        exit(1);
    }
    fgets(buff2, 1024, nfile);
    pclose(nfile);
    return buff2;
}


float CPUload(){
    char buff3[1024];
    memset(buff3, 0, sizeof(buff3));
    long long user1, nice1, system1, idle1, iowait1, irq1, softirq1, steal1, guest1, guest_nice1;
    FILE* lfile = popen("cat /proc/stat | grep \"cpu\" | head -n 1 | cut -d' ' -f2-","r");
    if(lfile == NULL){
        fprintf(stderr, "ERROR: CPU-load not found!\n");
        exit(1);
    }
    fread(buff3, sizeof(buff3)-1, 10, lfile);
    sscanf(buff3,"%lld %lld %lld %lld %lld %lld %lld %lld %lld %lld", &user1, &nice1, &system1, &idle1, &iowait1, &irq1, &softirq1, &steal1, &guest1, &guest_nice1);
    pclose(lfile);
    sleep(1); 
    char buff4[1024];
    memset(buff4, 0, sizeof(buff4));
    long long user2, nice2, system2, idle2, iowait2, irq2, softirq2, steal2, guest2, guest_nice2;
    FILE* lfile1 = popen("cat /proc/stat | grep \"cpu\" | head -n 1 | cut -d' ' -f2-","r");
    if(lfile1 == NULL){
        fprintf(stderr, "ERROR: CPU-load not found!\n");
        exit(1);
    }
    fread(buff4, sizeof(buff4)-1, 10, lfile1);
    sscanf(buff4,"%lld %lld %lld %lld %lld %lld %lld %lld %lld %lld", &user2, &nice2, &system2, &idle2, &iowait2, &irq2, &softirq2, &steal2, &guest2, &guest_nice2);
    pclose(lfile1);
    long long PrevIdle = idle1 + iowait1;
    long long Idle = idle2 + iowait2;
    long long PrevNonIdle = user1 + nice1 + system1 + irq1 + softirq1 + steal1;
    long long NonIdle = user2 + nice2 + system2 + irq2 + softirq2 + steal2;
    long long PrevTotal = PrevIdle + PrevNonIdle;
    long long Total = Idle + NonIdle;
    long long totald = Total - PrevTotal;
    long long idled = Idle - PrevIdle;
    float CPU_Usage = (float)((long long)(totald - idled)) / totald * 100;
    return CPU_Usage;
}

int main (int argc, const char* argv[]){
    int welcome_socket;
    struct sockaddr_in sa;
    struct sockaddr_in sa_client;
    int port_number;
    if (argc != 2){
       fprintf(stderr,"usage: %s <port>\n", argv[0]);
       exit(1);
    }
    port_number = atoi(argv[1]);
    if(port_number < 0 || port_number > 65535){
        fprintf(stderr,"ERROR: Port does not exist!\n");
        exit(1);
    }
    socklen_t sa_client_len=sizeof(sa_client);
    if ((welcome_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0){
        fprintf(stderr,"ERROR: socket\n");
        exit(1);
    }
    int enable = 1;
    if (setsockopt(welcome_socket, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(enable)) < 0){
        fprintf(stderr,"setsockopt(SO_REUSEADDR) FAILED");
    }
    #ifdef SO_REUSEPORT
        if (setsockopt(welcome_socket, SOL_SOCKET, SO_REUSEPORT, &enable, sizeof(enable)) < 0)
            fprintf(stderr,"setsockopt(SO_REUSEPORT) FAILED");
    #endif
    memset(&sa,0,sizeof(sa));
    sa.sin_family = AF_INET;
    sa.sin_addr.s_addr = htonl(INADDR_ANY);
    sa.sin_port = htons(port_number);    
    if ((bind(welcome_socket, (struct sockaddr*)&sa, sizeof(sa))) < 0){
        fprintf(stderr,"ERROR: Binding error!");
        exit(1);        
    }
    if ((listen(welcome_socket, 1)) < 0){
        fprintf(stderr,"ERROR: Listening error!");
        exit(1);                
    }
    while(1){
        int comm_socket = accept(welcome_socket, (struct sockaddr*)&sa_client, &sa_client_len);        
        if (comm_socket > 0){
            char buff[1024];
            int res = recv(comm_socket, buff, 1024,0);
                if (res <= 0){             
                    perror("Receiving error!");
                    exit(EXIT_FAILURE);
                }
            char* call = strtok(buff, " ");
            if(strcmp(call, "GET")){
                memset(buff, 0, 1024);
                sprintf(buff, "HTTP/1.1 400 Bad Request\r\n\r\nError 400 Bad Request\n");
            }
            else{
                call = strtok(NULL, " ");
                if(strcmp(call, "/hostname") == 0){
                    memset(buff, 0, 1024);
                    sprintf(buff, "HTTP/1.1 200 OK\r\nContent-Type: text/plain;\r\n\r\n%s",Hostname());
                }
                else if(strcmp(call, "/cpu-name") == 0){
                    memset(buff, 0, 1024);
                    sprintf(buff, "HTTP/1.1 200 OK\r\nContent-Type: text/plain;\r\n\r\n%s",CPUname());
                }
                else if(strcmp(call, "/load") == 0){
                    memset(buff, 0, 1024);
                    sprintf(buff, "HTTP/1.1 200 OK\r\nContent-Type: text/plain;\r\n\r\n%.2f%%\n",CPUload());
                }
                else{
                    memset(buff, 0, 1024);
                    sprintf(buff, "HTTP/1.1 400 Bad Request\r\n\r\nError 400 Bad Request\n");
                }
            }
            send(comm_socket, buff, strlen(buff), 0);
        }
        close(comm_socket);
    }
}