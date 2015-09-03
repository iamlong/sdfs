#include "siblock.h"
#include <vector>
#include <string>
#include "../util/serialize.h"

using namespace std;

class siblocklist:public ISerialize{
	
	public:
		siblocklist();
		sd_uint32_t appendBlock(siblockref block);
		bool deletefrom(sd_uint32_t index);
		sd_uint32_t getSize();
		siblockref getBlock(sd_uint32_t index);
		bool emptylist();
		vector<string> getRemoveList();
		
		//Serialization and Deserialization
		sd_uint32_t getPersistentSizeInByte();
		bool Serialize(Serializer * inSerializer);
		bool DeSerialize(DeSerializer * inDeSerializer);
	
	private:
		vector<siblockref> m_blocklist;
		vector<string> m_removeblocklist;
};
	
