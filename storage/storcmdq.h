#ifndef commandq_h
#define commandq_h

#include <queue>
#include <mutex>
#include "../util/stdtype.h"

using namespace std;

struct storage_command{
	string command;
	sd_uint8_t * data_buff;
	sd_uint32_t data_size;
};

typedef bool (* command_pusher)(string command, sd_uint8_t * cmd_buff, sd_uint32_t buff_size);

class storage_command_q{

	public:
		bool pushtoQ(string command, sd_uint8_t * cmd_buff, sd_uint32_t size);
		storage_command pullfromQ();
		sd_uint32_t QSize();

	private:
		mutex m_mtx;
		queue<storage_command> m_commandQ;
};


#endif
