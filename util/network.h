#ifndef _network_h
#define _network_h

#include <ifaddrs.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <vector>
#include <string>
#include <string.h>

using namespace std;

class networkhelper {
	public:
		static void getLocalips(vector<string> * ipvector);
		static int CreateUDPv4(string ip, int port);
};

#endif
