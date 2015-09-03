#include "processlist.h"
#include "../sha1/sha1.h"


processlist::processlist(){
	
	set_sig(PLIST_START_SIG, PLIST_END_SIG);
}

sd_int32_t processlist::findProcessIndex(string host, sd_uint32_t pnumber){

	string key = genKey( host, pnumber);
	
	rprocess proc;
	
	utils::hash(key, proc.m_hash);
	
	return findProcessbyHash(proc.m_hash);
	
}

sd_int32_t processlist::findProcessbyHash(char hash[DIGEST_LEN] ){

	sd_int32_t process_list_size = m_process.size();
	
	for(sd_int32_t i;i<process_list_size; i++)
		if(memcmp(hash, m_process[i]->m_hash, DIGEST_LEN)==0)
			return i;
			
	return -1;
}

string processlist::genKey(string host, sd_uint32_t pno){
		
	string key;
	char temp[256];
	sprintf(temp, "%d", pno);
	key = temp;
	key = key + "@" + host;
	
	return key;
}
bool processlist::addProcess(string host, sd_uint32_t pnumber){

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

rprocess * processlist::getRProcess(sd_uint32_t index){
	
	if(index > m_process.size()&&index<0)
		return NULL;
	
	return m_process[index];
}
bool processlist::removeProcess(string host, sd_uint32_t pnumber){

	string key = genKey(host, pnumber);
	
	rprocess proc;
	
	utils::hash(key, proc.m_hash);
	
	sd_int32_t i = findProcessbyHash(proc.m_hash);
	
	if(i>=0){
		delete getRProcess(i);
		m_process.erase(m_process.begin()+i);
		return true;
	};
		
	return false;
}

sd_uint32_t processlist::getPersistentSizeInByte(){
	
	m_persistent_size =  m_process.size() * sizeof(rprocess)+sizeof(sd_uint16_t) + getISerializeSize();
	return m_persistent_size;
}

bool processlist::Serialize(Serializer * inSerializer){
	
	if(inSerializer->getLeftSize()<getPersistentSizeInByte())
		return false;
	
	inSerializer->fillBytes((sd_uint8_t *)m_start_sig, sizeof(m_start_sig));
	
	inSerializer->fillBytes((sd_uint8_t *)&m_persistent_size, sizeof(m_persistent_size));
	
	sd_uint16_t size = m_process.size();
	
	//fill in how many processes in the process list
	inSerializer->fillBytes((sd_uint8_t *)&size, sizeof(size));
	
	for(int i = 0; i <size; i++){
		rprocess * trp= (m_process)[i];
		if(!inSerializer->fillBytes((sd_uint8_t *)trp, sizeof(rprocess)))
			return false;
	}
	
	inSerializer->fillBytes((sd_uint8_t *)m_end_sig, sizeof(m_end_sig));
	return true;
	
}

bool processlist::DeSerialize(DeSerializer * inDeSerializer){
	
	if(checkBuffer(inDeSerializer)!=true)
		return false;
	
	sd_uint16_t processsize;
	
	if(inDeSerializer->pullBytes((sd_uint8_t *)&processsize, sizeof(processsize))!=sizeof(processsize))
		return false;
	
	for(int i = 0; i<processsize; i++){
		rprocess * temp = new rprocess();
		if(inDeSerializer->pullBytes((sd_uint8_t *)temp, sizeof(rprocess))!=sizeof(rprocess)){
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
	
	sd_uint32_t processsize = m_process.size();
	for(int i = 0; i<processsize;i++)
		delete m_process[i];
	
	m_process.clear();
}
