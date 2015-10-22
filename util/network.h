#ifndef _network_h
#define _network_h

#include <ifaddrs.h>
#include <netinet/in.h>
#include <arpa/inet.h>

class networkhelper {
	public:
		static array<string> getLocalips();
}

#endif
