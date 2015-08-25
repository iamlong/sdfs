#ifndef siblock_h
#define siblock_h

class siblockref: public ISerialize{
	
	public:
		siblockref();
		
		bool operator==(const siblockref& compblock);
		
		//Serialization and DeSerialization
		int getPersistentSizeInByte();
		bool Serialize(Serializer * inSerializer);
		bool DeSerialize(DeSerializer * inDeSerializer);
		
	private:
		string m_key;
		uint32_t m_seqnum;
		uint32_t m_blocksize;
		uint32_t m_usedsize;
		char m_hash[DIGEST_LEN];
		char m_next_block_hash[DIGEST_LEN];
		char m_prev_block_hash[DIGEST_LEN];

};

class siblock {
	uint32_t m_seqnum;
	uint32_t m_blocksize;
	uint32_t m_usedsize;
	char m_hash[DIGSET_LEN];
	char m_data[]; //real data for the block;
	
};
#endif //siblock_h
