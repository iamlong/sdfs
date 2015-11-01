#ifndef storage_listener_h
#define storage_listener_h

#include "storcmdq.h"
#include <thread>
#include <iostream>
#include <string>
#include "../util/network.h"
#include <mutex>
#include <condition_variable>

using namespace std;

mutex mtx;
condition_variable cv;

class storage_listener {
	public:
		storage_listener(command_pusher pusher, command_puller puller, storage_command_q * q, string ip, int port);
		bool start();
		bool stop();
		thread * getThread();

	private:
		command_pusher m_pusher;
		command_puller m_puller;
		string m_ip;
        storage_command_q * m_q;
		int m_port;
		thread* m_listener;
		thread* m_consumer;
		static void listener(command_pusher pusher, storage_command_q* q, string ip, int port);
		static void consumer(command_puller puller, storage_command_q* q);
};
#endif
