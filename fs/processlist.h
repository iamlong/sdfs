#ifndef processlist_h
#define processlist_h

#include "../util/serialize.h"
#include "structures.h"
#include <vector>
#include "../util/sig.h"

using namespace std;

class processlist:public ISerialize{
	
	public:
		processlist();
		~processlist();
		sd_uint32_t getPersistentSizeInByte();
		bool Serialize(Serializer * inSerializer);
		bool DeSerialize(DeSerializer * inDeSerializer);
		bool addProcess(string host, sd_uint32_t pnumber);
		bool removeProcess(string host, sd_uint32_t pnumber);
		int findProcessIndex(string host, sd_uint32_t pnumber);
		rprocess * getRProcess(sd_uint32_t index);
	private:
		vector<rprocess *> m_process;
		string genKey(string host, sd_uint32_t pno);
		int findProcessbyHash(char hash[DIGEST_LEN] );
};
#endif
