#include "serialize.h"


sd_uint32_t ISerialize::getISerializeSize(){
	return sizeof(m_start_sig) + sizeof(m_end_sig) + sizeof(m_persistent_size);
};

void ISerialize::set_sig(const char start_sig[], const char end_sig[]){
	//Every class inherited from ISerialize need to set it's start sig and end sig.
	memcpy(m_start_sig, start_sig, sizeof(m_start_sig));
	memcpy(m_end_sig, end_sig, sizeof(m_end_sig));
}

bool ISerialize::checkBuffer(DeSerializer * inDeSerializer){

	sd_uint8_t sig[sizeof(m_start_sig)];

	if(inDeSerializer->pullBytes(sig, sizeof(m_start_sig))!=sizeof(m_start_sig))
		return false;

	if(memcmp(sig, m_start_sig, sizeof(m_start_sig))!=0)
		return false;

	if(inDeSerializer->pullBytes((sd_uint8_t *)&m_persistent_size, sizeof(m_persistent_size))!=sizeof(m_persistent_size))
		return false;
		
	int processbytes = m_persistent_size - getISerializeSize();
	
	sd_uint8_t * endsig = inDeSerializer->getFilledBuffer()+inDeSerializer->getPulledSize()+processbytes;
	
	if(memcmp(endsig, m_end_sig, sizeof(m_end_sig))!=0)
		return false;

	return true;
}

sd_uint32_t ISerialize::calcStringSize(string eval){
	sd_uint32_t size = sizeof(sd_uint32_t); //add size of the string before data;
	size += eval.size();
	return size;
}
