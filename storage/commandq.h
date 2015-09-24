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

class command_q{

	public:
		bool pushtoQ(string command, sd_uint8_t * buff, sd_uint32_t size);
		storage_command pullfromQ();
		sd_uint32_t QSize();

	private:
		mutex m_mtx;
		queue<storage_command> m_commandQ;
};


#endif
