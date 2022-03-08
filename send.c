#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netdb.h>

void main(int argc, char **argv){
	int sockfd;
	struct addrinfo hints,*res;
	char readbuf[1024];

	memset(&hints,0,sizeof(0));
	hints.ai_family=AF_INET;
	hints.ai_socktype=SOCK_DGRAM;

	int e = getaddrinfo(argv[1],argv[2],&hints,&res);
	if(e!=0) printf("getaddrinfo error:%s\n",gai_strerror(e));

	if((sockfd=socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP))==-1){
		perror("socket error");
	}
	
	int ttl=64;
	if(setsockopt(sockfd,IPPROTO_IP,IP_MULTICAST_TTL,&ttl,sizeof(ttl))==-1){
		perror("setsockopt error");
	}

	for(;;){
		fgets(readbuf,sizeof(readbuf),stdin);
		if(sendto(sockfd,readbuf,sizeof(readbuf),0,res->ai_addr,sizeof(struct sockaddr))==-1){
			perror("sendto error");
		}
	}

}
