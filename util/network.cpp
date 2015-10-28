#include "network.h"

void networkhelper::getLocalips(vector<string> * ipvector ){
	
	struct ifaddrs * ifAddrStruct=NULL;
    void * tmpAddrPtr=NULL;
    char addressBuffer[INET6_ADDRSTRLEN];
	
    getifaddrs(&ifAddrStruct);

    while (ifAddrStruct!=NULL) {
        if (ifAddrStruct->ifa_addr->sa_family==AF_INET) { // check it is IP4
            // is a valid IP4 Address
            tmpAddrPtr=&((struct sockaddr_in *)ifAddrStruct->ifa_addr)->sin_addr;
            inet_ntop(AF_INET, tmpAddrPtr, addressBuffer, INET_ADDRSTRLEN);
			string addr(addressBuffer);
			ipvector->push_back(addr);

        } else if (ifAddrStruct->ifa_addr->sa_family==AF_INET6) { // check it is IP6
            // is a valid IP6 Address
            tmpAddrPtr=&((struct sockaddr_in6 *)ifAddrStruct->ifa_addr)->sin6_addr;
            inet_ntop(AF_INET6, tmpAddrPtr, addressBuffer, INET6_ADDRSTRLEN);
			string addr(addressBuffer);
			ipvector->push_back(addr);
		} 
        ifAddrStruct=ifAddrStruct->ifa_next;
    }
    
    freeifaddrs(ifAddrStruct);
}

int networkhelper::CreateUDPv4(string ip, int port){

	int sockfd;
    struct sockaddr_in servaddr, cliaddr;
    
	sockfd = socket(AF_INET, SOCK_DGRAM, 0); /* create a socket */
    /* init servaddr */
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
	if(ip.size()<=0) //if ip is not set;
		servaddr.sin_addr.s_addr = htonl(INADDR_ANY); //#define INADDR_ANY   ((unsigned long int) 0x00000000)
	else servaddr.sin_addr.s_addr = inet_addr(ip.c_str());
	
	servaddr.sin_port = htons(port);

	if(bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) == -1)
	  return -1;
	else
	  return sockfd;
}
