#include "siblock.h"

siblockref::siblockref(){
	char startsig[]=SIBLKREF_START_SIG;
	char endsig[]=SIBLKREF_END_SIG;
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
	
	inSerializer->fillBytes((uint8_t *)m_start_sig, sizeof(m_start_sig));
	
	inSerializer->fillBytes((uint8_t *)&m_persistent_size, sizeof(m_persistent_size));
	
	inSerializer->fillBytes((uint8_t *)&m_key, sizeof(m_key));
	
	inSerializer->fillBytes((uint8_t *)&m_seqnum, sizeof(m_seqnum));
	
	inSerializer->fillBytes((uint8_t *)&m_blocksize, sizeof(m_blocksize));
	
	inSerializer->fillBytes((uint8_t *)&m_usedsize, sizeof(m_usedsize));
	
	inSerializer->fillBytes((uint8_t *)&m_hash, sizeof(m_hash));
	
	inSerializer->fillBytes((uint8_t *)m_next_block_hash, sizeof(m_next_block_hash));
	
	inSerializer->fillBytes((uint8_t *)&m_prev_block_hash, sizeof(m_prev_block_hash));
	
	inSerializer->fillBytes((uint8_t *)&m_end_sig, sizeof(m_end_sig));
	
	return true;
}

bool siblockref::DeSerialize(DeSerializer * inDeSerializer){
	
	//with checkbuff, the point of inDeSerializer will also go forward to the start of real data in the buffer
	if(checkBuffer(inDeSerializer)!=true)
		return false;
	
	
		
	
	return true;
}
