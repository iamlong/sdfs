#include "processlist.h"


processlist::processlist(){
	char startsig[]=PLIST_START_SIG;
	char endsig[]=PLIST_END_SIG;
	memcpy(m_start_sig, startsig, sizeof(m_start_sig));
	memcpy(m_end_sig, startsig, sizeof(m_end_sig));
}

int processlist::getPersistentSizeInByte(){
	
	m_persistent_size =  m_process.size() * sizeof(rprocess) + getISerializeSize();
	return m_persistent_size;
}

bool processlist::Serialize(Serializer * inSerializer){
	
	if(inSerializer->getLeftSize()<getPersistentSizeInByte())
		return false;
	
	inSerializer->fillBytes((uint8_t *)m_start_sig, sizeof(m_start_sig));
	
	inSerializer->fillBytes((uint8_t *)&m_persistent_size, sizeof(m_persistent_size));
	
	int size = m_process.size();
	
	for(int i = 0; i <size; i++){
		rprocess * trp= (m_process)[i];
		if(!inSerializer->fillBytes((uint8_t *)trp, sizeof(rprocess)))
			return false;
	}
	
	inSerializer->fillBytes((uint8_t *)m_end_sig, sizeof(m_end_sig));
	
}

bool processlist::DeSerialize(DeSerializer * inDeSerializer){
	uint8_t sig[sizeof(m_start_sig)];
	
	inDeSerializer->pullBytes(sig, sizeof(m_start_sig));
	
	if(sig, m_start_sig, sizeof(m_start_sig)!=0)
		return false;
		
	inDeSerializer->pullBytes(m_persistent_size, sizeof(m_persistent_size));
	
	int processbytes = m_persistent_size - sizeof(m_persistent_size) - sizeof(m_start_sig) - sizeof(m_end_sig);
	
	uint8_t * endsig = inDeSerializer->getFilledBuffer()+inDeSerializer->getPulledSize()+processbytes;
	
	if(endsig, m_end_sig, sizeof(m_end_sig)!=0)
		return false;
	
	return true;
}
