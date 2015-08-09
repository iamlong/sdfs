#include "processlist.h"

int processlist::getPersistentSizeInByte(){
	
	m_persistent_size =  m_process.size() * sizeof(rprocess) + getISerializeSize();
	return m_persistent_size;
}

bool processlist::Serialize(uint8_t * buffer, int buff_size){
	
	if(buff_size<m_persistent_size)
		return false;
		
	uint8_t * head = buffer;
	
	memcpy(head, m_start_sig, sizeof(m_start_sig));
	head += sizeof(m_start_sig);
	
	memcpy(head, &m_persistent_size, sizeof(m_persistent_size));
	head += sizeof(m_persistent_size);
	
	int size = m_process.size();
	
	for(int i = 0; i <size; i++){
		rprocess * trp= (m_process)[i];
		memcpy(head, trp, sizeof(rprocess));
		head +=sizeof(rprocess);
	}
	
	memcpy(head, m_start_sig, sizeof(m_end_sig));
	
	return true;
}

bool processlist::Serialize(uint8_t * buffer, int buff_size){
	
}
