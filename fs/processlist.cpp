#include "processlist.h"
#include "../sha1/sha1.h"


processlist::processlist(){
	char startsig[]=PLIST_START_SIG;
	char endsig[]=PLIST_END_SIG;
	memcpy(m_start_sig, startsig, sizeof(m_start_sig));
	memcpy(m_end_sig, startsig, sizeof(m_end_sig));
}

bool processlist::addProcess(string host, int pnumber){
	string key;
	char temp[256];
	sprintf(temp, "%d", pnumber);
	key = temp;
	key = key + "@" + host;
	rprocess * proc = new rprocess();
	utils::hash(key, proc->m_hash);
	
	int process_list_size = m_process.size();
	
	for(int i;i<process_list_size; i++)
		if(memcmp(proc->m_hash, m_process[i]->m_hash, DIGEST_LEN)==0){
			delete proc;
			return false;
		};
	
	strcpy(proc->host,host.c_str());
	proc->process = pnumber;
	m_process.push_back(proc);
	return true;
}

bool processlist::removeProcess(string host, int pnumber){
	string key;
	char temp[256];
	sprintf(temp, "%d", pnumber);
	key = temp;
	key = key + "@" + host;
	rprocess * proc = new rprocess();
	utils::hash(key, proc->m_hash);
	
	int process_list_size = m_process.size();
	
	for(int i;i<process_list_size; i++)
		if(memcmp(proc->m_hash, m_process[i]->m_hash, DIGEST_LEN)==0){
			delete proc;
			delete m_process[i];
			m_process.erase(m_process.begin()+i);
			return true;
		};
		
	return false;
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
	
	uint16_t size = m_process.size();
	
	//fill in how many processes in the process list
	inSerializer->fillBytes((uint8_t *)&size, sizeof(size));
	
	for(int i = 0; i <size; i++){
		rprocess * trp= (m_process)[i];
		if(!inSerializer->fillBytes((uint8_t *)trp, sizeof(rprocess)))
			return false;
	}
	
	inSerializer->fillBytes((uint8_t *)m_end_sig, sizeof(m_end_sig));
	
}

bool processlist::DeSerialize(DeSerializer * inDeSerializer){
	
	uint8_t sig[sizeof(m_start_sig)];
	
	if(inDeSerializer->pullBytes(sig, sizeof(m_start_sig))!=sizeof(m_start_sig))
		return false;
	
	if(sig, m_start_sig, sizeof(m_start_sig)!=0)
		return false;
		
	if(inDeSerializer->pullBytes((uint8_t *)&m_persistent_size, sizeof(m_persistent_size))!=sizeof(m_persistent_size))
		return false;
	
	int processbytes = m_persistent_size - sizeof(m_persistent_size) - sizeof(m_start_sig) - sizeof(m_end_sig);
	
	uint8_t * endsig = inDeSerializer->getFilledBuffer()+inDeSerializer->getPulledSize()+processbytes;
	
	if(endsig, m_end_sig, sizeof(m_end_sig)!=0)
		return false;
	
	uint16_t processsize;
	
	if(inDeSerializer->pullBytes((uint8_t *)&processsize, sizeof(processsize))!=sizeof(processsize))
		return false;
	
	for(int i = 0; i<processsize; i++){
		rprocess * temp = new rprocess();
		if(inDeSerializer->pullBytes((uint8_t *)temp, sizeof(rprocess))!=sizeof(rprocess)){
			//if get process item fail; clean up the current created process list;
			for(int j = 0; j<i; j++){
				rprocess * trp= (m_process)[j];
				delete trp;
			}
			delete temp;
			m_process.clear();
			return false;
		};
		m_process.push_back(temp);
	}
	return true;
}
