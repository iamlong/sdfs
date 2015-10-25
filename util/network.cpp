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
