#include "siblock.h"
#include <time.h>
#include "../util/utils.h"

siblockref::siblockref(string path){
	
	init();
	set_blocksize(4096);
	
	string key = path;
	key += " timestamp(UTC): "+ time(NULL);
	set_key(key);
}

siblockref::siblockref(string path, int blocksize){
	
	init();
	set_blocksize(blocksize);
	
	string key = path;
	key += " timestamp(UTC): ";
	key += time(NULL);
	set_key(key);
}

siblockref::siblockref(){
	init();
	set_blocksize(4096);
}

void siblockref::init(){
	set_sig(SIBLKREF_START_SIG, SIBLKREF_END_SIG);
	memset(m_hash, 0, DIGEST_LEN);
	memset(m_next_block_hash, 0, DIGEST_LEN);
	memset(m_prev_block_hash, 0, DIGEST_LEN);
	m_usedsize = 0;
}

siblockref::siblockref(int blocksize){
	set_sig(SIBLKREF_START_SIG, SIBLKREF_END_SIG);
	memset(m_hash, 0, DIGEST_LEN);
	set_blocksize(blocksize);
}


void siblockref::set_key(string key){
	
	memset(m_hash, 0, DIGEST_LEN);
	int sizetohash = sizeof(m_key)<=key.size()?sizeof(m_key):key.size();
	memcpy(m_key, key.data(), sizetohash);
	key = key.substr(0, sizetohash);
	utils::hash(key, m_hash); 
	
}
bool siblockref::operator==(const siblockref& compblock){
	
	if(memcmp(m_key, compblock.m_key, sizeof(m_key))== 0&&\
		m_seqnum==compblock.m_seqnum&&\
		m_blocksize==compblock.m_blocksize&&\
		m_usedsize==compblock.m_usedsize&&\
		memcmp(m_hash, compblock.m_hash, sizeof(m_hash))==0&&\
		memcmp(m_next_block_hash, compblock.m_next_block_hash, sizeof(m_next_block_hash))==0&&\
		memcmp(m_prev_block_hash, compblock.m_prev_block_hash, sizeof(m_prev_block_hash))==0)
		return true;
	
	return false;
}

bool siblockref::operator!=(const siblockref& compblock){
	
	if(memcmp(m_key, compblock.m_key, sizeof(m_key))== 0&&\
		m_seqnum==compblock.m_seqnum&&\
		m_blocksize==compblock.m_blocksize&&\
		m_usedsize==compblock.m_usedsize&&\
		memcmp(m_hash, compblock.m_hash, sizeof(m_hash))==0&&\
		memcmp(m_next_block_hash, compblock.m_next_block_hash, sizeof(m_next_block_hash))==0&&\
		memcmp(m_prev_block_hash, compblock.m_prev_block_hash, sizeof(m_prev_block_hash))==0)
		return false;
	
	return true;
}

bool siblockref::operator<(const siblockref& compblock){
	return m_seqnum<compblock.m_seqnum;
}

char* siblockref::get_hash(){
	return m_hash;
}

void siblockref::set_next_block(char nextblockhash[DIGEST_LEN]){
	memcpy(m_next_block_hash, nextblockhash, sizeof(m_next_block_hash));
}

void siblockref::clean_next_block(){
	memset(m_next_block_hash, 0, sizeof(m_next_block_hash));
}

void siblockref::set_prev_block(char prevblockhash[DIGEST_LEN]){
	memcpy(m_prev_block_hash, prevblockhash, sizeof(m_prev_block_hash));
}

void siblockref::set_seqnum(sd_uint32_t no){
	m_seqnum = no;
}

void siblockref::set_blocksize(sd_uint32_t size){
	m_blocksize = size;
}

void siblockref::set_usedsize(sd_uint32_t size){
	m_usedsize = size;
}

int siblockref::getPersistentSizeInByte(){
	
	m_persistent_size = sizeof(m_key)+sizeof(m_seqnum)\
				+sizeof(m_blocksize)+sizeof(m_usedsize)\
				+sizeof(m_hash)+sizeof(m_next_block_hash)\
				+sizeof(m_prev_block_hash) + getISerializeSize();

	return m_persistent_size;
}

bool siblockref::Serialize(Serializer * inSerializer){
	
	if(inSerializer->getLeftSize()<getPersistentSizeInByte())
		return false;
	
	inSerializer->fillBytes((sd_uint8_t *)m_start_sig, sizeof(m_start_sig));
	
	inSerializer->fillBytes((sd_uint8_t *)&m_persistent_size, sizeof(m_persistent_size));
	
	inSerializer->fillBytes((sd_uint8_t *)&m_key, sizeof(m_key));
	
	inSerializer->fillBytes((sd_uint8_t *)&m_seqnum, sizeof(m_seqnum));
	
	inSerializer->fillBytes((sd_uint8_t *)&m_blocksize, sizeof(m_blocksize));
	
	inSerializer->fillBytes((sd_uint8_t *)&m_usedsize, sizeof(m_usedsize));
	
	inSerializer->fillBytes((sd_uint8_t *)&m_hash, sizeof(m_hash));
	
	inSerializer->fillBytes((sd_uint8_t *)m_next_block_hash, sizeof(m_next_block_hash));
	
	inSerializer->fillBytes((sd_uint8_t *)&m_prev_block_hash, sizeof(m_prev_block_hash));
	
	inSerializer->fillBytes((sd_uint8_t *)&m_end_sig, sizeof(m_end_sig));
	
	return true;
}

bool siblockref::DeSerialize(DeSerializer * inDeSerializer){
	
	//with checkbuff, the point of inDeSerializer will also go forward to the start of real data in the buffer
	if(checkBuffer(inDeSerializer)!=true)
		return false;
	
	if(inDeSerializer->pullBytes((sd_uint8_t *)&m_key, sizeof(m_key))!=sizeof(m_key))
		return false;
		
	
	if(inDeSerializer->pullBytes((sd_uint8_t *)&m_seqnum, sizeof(m_seqnum))!=sizeof(m_seqnum))
		return false;
	
	if(inDeSerializer->pullBytes((sd_uint8_t *)&m_blocksize, sizeof(m_blocksize))!=sizeof(m_blocksize))
		return false;
	
		
	if(inDeSerializer->pullBytes((sd_uint8_t *)&m_usedsize, sizeof(m_usedsize))!=sizeof(m_usedsize))
		return false;
		
	
	if(inDeSerializer->pullBytes((sd_uint8_t *)&m_hash, sizeof(m_hash))!=sizeof(m_hash))
		return false;
	
	if(inDeSerializer->pullBytes((sd_uint8_t *)&m_next_block_hash, sizeof(m_next_block_hash))!=sizeof(m_next_block_hash))
		return false;

	if(inDeSerializer->pullBytes((sd_uint8_t *)&m_prev_block_hash, sizeof(m_prev_block_hash))!=sizeof(m_prev_block_hash))
		return false;
	
	if(inDeSerializer->pullBytes((sd_uint8_t *)&m_end_sig, sizeof(m_end_sig))!=sizeof(m_end_sig))
		return false;		
	
	return true;
}
