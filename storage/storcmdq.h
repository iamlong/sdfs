#ifndef commandq_h
#define commandq_h

#include <queue>
#include <mutex>
#include "../util/stdtype.h"
#include "storcmd.h"

using namespace std;

class storage_command_q{

	public:
		bool pushtoQ( storage_command* inCmd);
		storage_command* pullfromQ();
		sd_uint32_t QSize();
        ~storage_command_q();

	protected:
		mutex m_mtx;
		queue<storage_command*> m_commandQ;
};

typedef bool (* command_pusher)(storage_command_q* q, storage_command * inCmd);
typedef storage_command * (*command_puller)(storage_command_q* q);

bool cmd_push(storage_command_q* q, storage_command* inCmd);

storage_command * cmd_pull(storage_command_q* q);

#endif
