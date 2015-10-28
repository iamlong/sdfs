#ifndef storage_listener_h
#define storage_listener_h

#include "storcmdq.h"
#include <thread>
#include <iostream>
#include <string>
#include "../util/network.h"

using namespace std;

class storage_listener {
	public:
		storage_listener(command_pusher pusher, storage_command_q * q, string ip, int port);
		bool start();
		bool stop();
		thread * getThread();

	private:
		command_pusher m_pusher;
		string m_ip;
        storage_command_q * m_q;
		int m_port;
		thread* m_listener;
		static void listener(command_pusher pusher, storage_command_q* q, string ip, int port);
};
#endif
