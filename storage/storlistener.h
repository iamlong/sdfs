#ifndef storage_listener_h
#define storage_listener_h

#include "storcmdq.h"

class storage_listener {
	public:
		storage_listenser(command_pusher pusher);
		bool start();
		bool stop();

	private:
		command_pusher m_pusher;
		void listener(command_pusher pusher, int port);
};
#endif
