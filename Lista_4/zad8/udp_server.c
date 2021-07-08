#include<stdio.h> 
#include<strings.h> 
#include<stdlib.h>
#include<sys/types.h> 
#include<arpa/inet.h> 
#include<sys/socket.h> 
#define MAXLINE 1024
  
int main(int argc, char* argv[])
{    
    if (argc != 2){
        printf ("usage: %s <port_number>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int port = atoi(argv[1]);
      
    int listenfd; 
    listenfd = socket(AF_INET, SOCK_DGRAM, 0);         
    
    struct sockaddr_in servaddr; 
    bzero(&servaddr, sizeof(servaddr)); 
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY); 
    servaddr.sin_port = htons(port); 
    servaddr.sin_family = AF_INET;  
   
    bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr)); 
        
    char buf[MAXLINE];
    while (1) {
        int n = recv(listenfd, buf, sizeof(buf), 0);
        buf[n] = '\0'; 
        fputs(buf, stdout);
    } 
} 