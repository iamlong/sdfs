#include "processlist.h"

int processlist::getPersistentSizeInByte(){
	
	m_persistent_size =  m_process.size() * sizeof(rprocess) + getISerializeSize();
	return m_persistent_size;
}

bool processlist::Serialize(Serializer * inSerializer){
	
	inSerializer->fillBytes(m_start_sig, sizeof(m_start_sig));
	
	inSerializer->fillBytes(&m_persistent_size, sizeof(m_persistent_size));
	
	int size = m_process.size();
	
	for(int i = 0; i <size; i++){
		rprocess * trp= (m_process)[i];
		if(!inSerializer->fillBytes(trp, sizeof(rprocess)))
			return false;
	}
	
	inSerializer->fillBytes(m_end_sig, sizeof(m_end_sig));
	
}
