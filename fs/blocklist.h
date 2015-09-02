#include "siblock.h"
#include <vector>
#include <string>
#include "../util/serialize.h"

using namespace std;

class siblocklist:ISerialize{
	
	public:
		sd_uint32_t appendBlock(siblockref block);
		bool deletefrom(sd_uint32_t index);
		sd_uint32_t getSize();
		siblockref getBlock(sd_uint32_t index);
		bool emptylist();
		vector<string> getRemoveList();
		
		//Serialization and Deserialization
		int getPersistentSizeInByte(){return 0;};
		bool Serialize(Serializer * inSerializer){return true;};
		bool DeSerialize(DeSerializer * inDeSerializer){return true;};
	
	private:
		vector<siblockref> m_blocklist;
		vector<string> m_removeblocklist;
};
	
