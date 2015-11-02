/*************************************************************************
	> File Name: testStorage.cpp
	> Author: 
	> Mail: 
	> Created Time: Wed, Oct 28, 2015  4:50:33 PM
 ************************************************************************/

#include<iostream>
using namespace std;

#include <gtest/gtest.h>
#include <stdio.h>
#include "../storage/storcmd.h"
#include "../util/network.h"
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>

TEST(TESTLISTENER, SENDCOMMAND){
    
    storage_command creatcmd(1024*4); //set max buff size to 4k
    Serializer inSerializer(1024*5); //create 5K buff for serialization
    sd_uint8_t bff[20]="abcdefghiiklmnopq1";
    creatcmd.CreateCommand("firsttrunk", bff, 20);
    creatcmd.Serialize(&inSerializer);

    //now start to send command to endpoint;
    int sockfd = networkhelper::CreateUDPv4("", 3333);
    
    struct sockaddr_in cliaddr;
    struct hostent * clihost=gethostbyname("127.0.0.1");
    bzero(&cliaddr, sizeof(cliaddr));
    cliaddr.sin_family=AF_INET;
    cliaddr.sin_addr=*((struct in_addr*)clihost->h_addr);
    cliaddr.sin_port=htons(1234);
    int n = sendto(sockfd, inSerializer.getFilledBuffer(), inSerializer.getUsedSize(),0, (struct sockaddr*)&cliaddr, sizeof(cliaddr) );
    cout<<"sent:"<<n<<"\n";

}

int main(int argc, char** argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
