#ifndef _network_h
#define _network_h

#include <ifaddrs.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <vector>
#include <string>

using namespace std;

class networkhelper {
	public:
		static void getLocalips(vector<string> * ipvector);
};

#endif
