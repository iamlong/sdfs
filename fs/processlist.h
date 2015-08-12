#ifndef processlist_h
#define processlist_h

#include "../util/serialize.h"
#include "structures.h"
#include <vector>

using namespace std;

class processlist:public ISerialize{
	
	public:
		int getPersistentSizeInByte();
		bool Serialize(Serializer * inSerializer);
		bool DeSerialize(uint8_t * buff, int buff_size);
	private:
		vector<rprocess *> m_process;
};
#endif
