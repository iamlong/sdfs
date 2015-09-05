#ifndef siblock_h
#define siblock_h
#include <string.h>
#include "../util/serialize.h"
#include "../sha1/sha1.h"
#include "../util/sig.h"

using namespace std;

class siblockref: public ISerialize{
	
	public:

		siblockref();
		siblockref(int blocksize);
		siblockref(string path);
		siblockref(string path, int blocksize);
		
		void set_key(string key);
		void set_prev_block(sd_uint8_t prevblockhash[DIGEST_LEN]);
		void set_next_block(sd_uint8_t nextblockhash[DIGEST_LEN]);
		void set_seqnum(sd_uint32_t no);
		sd_uint32_t get_seqnum();
		void set_blocksize(sd_uint32_t size);
		void set_usedsize(sd_uint32_t size);
		void clean_next_block();
		
		bool operator==(const siblockref& compblock);
		bool operator!=(const siblockref& compblock);
		bool operator<(const siblockref& compblock);
		
		sd_uint8_t* get_hash();
		
		//Serialization and DeSerialization
		sd_uint32_t getPersistentSizeInByte();
		bool Serialize(Serializer * inSerializer);
		bool DeSerialize(DeSerializer * inDeSerializer);
		
	private:
		sd_uint8_t m_key[50];
		sd_uint32_t m_seqnum;
		sd_uint32_t m_blocksize;
		sd_uint32_t m_usedsize;
		sd_uint8_t m_hash[DIGEST_LEN];
		sd_uint8_t m_next_block_hash[DIGEST_LEN];
		sd_uint8_t m_prev_block_hash[DIGEST_LEN];
		
		
		void init();
		string gen_key(string key);

};

class siblock {
	sd_uint32_t m_seqnum;
	sd_uint32_t m_blocksize;
	sd_uint32_t m_usedsize;
	char m_hash[DIGEST_LEN];
	char m_data[]; //real data for the block;
	
};
#endif //siblock_h
