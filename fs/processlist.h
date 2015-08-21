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
		int getPersistentSizeInByte();
		bool Serialize(Serializer * inSerializer);
		bool DeSerialize(DeSerializer * inDeSerializer);
		bool addProcess(string host, int pnumber);
		bool removeProcess(string host, int pnumber);
		
	private:
		vector<rprocess *> m_process;
};
#endif
