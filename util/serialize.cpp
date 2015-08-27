#include "serialize.h"

int ISerialize::getISerializeSize(){
	return sizeof(m_start_sig) + sizeof(m_end_sig) + sizeof(m_persistent_size);
};

bool ISerialize::checkBuffer(DeSerializer * inDeSerializer){

	uint8_t sig[sizeof(m_start_sig)];

	if(inDeSerializer->pullBytes(sig, sizeof(m_start_sig))!=sizeof(m_start_sig))
		return false;

	if(memcmp(sig, m_start_sig, sizeof(m_start_sig))!=0)
		return false;

	if(inDeSerializer->pullBytes((uint8_t *)&m_persistent_size, sizeof(m_persistent_size))!=sizeof(m_persistent_size))
		return false;
		
	int processbytes = m_persistent_size - getISerializeSize();
	
	uint8_t * endsig = inDeSerializer->getFilledBuffer()+inDeSerializer->getPulledSize()+processbytes;
	
	if(memcmp(endsig, m_end_sig, sizeof(m_end_sig))!=0)
		return false;

	return true;
}
