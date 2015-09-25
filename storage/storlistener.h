#ifndef storage_listener_h
#define storage_listener_h

#include "storcmdq.h"

class storage_listener {
	public:
		bool start();
		bool stop();

	private:
		void listener(storage_command_q * cmdq, int port);
};
#endif
