#ifndef siblock_h
#define siblock_h

class siblockref: public ISerialize{
	
	public:
		bool operator==(const siblockref& compblock);
		
		//Serialization and DeSerialization
		int getPersistentSizeInByte();
		bool Serialize(Serializer * inSerializer);
		bool DeSerialize(DeSerializer * inDeSerializer);
		
	private:
		char m_hash[DIGEST_LEN];
		char m_next_block_hash[DIGEST_LEN];
		char m_prev_block_hash[DIGEST_LEN];
		
};
#endif //siblock_h
