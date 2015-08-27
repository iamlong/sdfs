#include "processlist.h"
#include "../sha1/sha1.h"


processlist::processlist(){
	char startsig[]=PLIST_START_SIG;
	char endsig[]=PLIST_END_SIG;
	memcpy(m_start_sig, startsig, sizeof(m_start_sig));
	memcpy(m_end_sig, startsig, sizeof(m_end_sig));
}

int processlist::findProcessIndex(string host, int pnumber){

	string key = genKey( host, pnumber);
	
	rprocess proc;
	
	utils::hash(key, proc.m_hash);
	
	return findProcessbyHash(proc.m_hash);
	
}

int processlist::findProcessbyHash(char hash[DIGEST_LEN] ){

	int process_list_size = m_process.size();
	
	for(int i;i<process_list_size; i++)
		if(memcmp(hash, m_process[i]->m_hash, DIGEST_LEN)==0)
			return i;
			
	return -1;
}

string processlist::genKey(string host, int pno){
		
	string key;
	char temp[256];
	sprintf(temp, "%d", pno);
	key = temp;
	key = key + "@" + host;
	
	return key;
}
bool processlist::addProcess(string host, int pnumber){

	string key = genKey(host, pnumber);
	
	rprocess * proc = new rprocess();
	
	utils::hash(key, proc->m_hash);

	if(findProcessbyHash(proc->m_hash)>=0){
		delete proc;
		return false;
	}
	
	
	strcpy(proc->host,host.c_str());
	proc->process = pnumber;
	m_process.push_back(proc);
	return true;
}

rprocess * processlist::getRProcess(int index){
	
	if(index > m_process.size())
		return NULL;
	
	return m_process[index];
}
bool processlist::removeProcess(string host, int pnumber){

	string key = genKey(host, pnumber);
	
	rprocess proc;
	
	utils::hash(key, proc.m_hash);
	
	int i = findProcessbyHash(proc.m_hash);
	
	if(i>=0){
		delete getRProcess(i);
		m_process.erase(m_process.begin()+i);
		return true;
	};
		
	return false;
}

int processlist::getPersistentSizeInByte(){
	
	m_persistent_size =  m_process.size() * sizeof(rprocess)+sizeof(uint16_t) + getISerializeSize();
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
	return true;
	
}

bool processlist::DeSerialize(DeSerializer * inDeSerializer){
	
	if(checkBuffer(inDeSerializer)!=true)
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

processlist::~processlist(){
	
	int processsize = m_process.size();
	for(int i = 0; i<processsize;i++)
		delete m_process[i];
	
	m_process.clear();
}
