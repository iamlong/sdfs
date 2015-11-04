#include "storcmd.h"

void storage_command::init(){

	set_sig(STORCMD_START_SIG, STORCMD_END_SIG);
}

storage_command::storage_command(sd_uint32_t maxsize){
	m_max_buff_size = maxsize;
    m_buff_size = 0;
	init();
}

/*bool storage_command::setBuff(sd_uint8_t* buff, sd_uint32_t size){
    if(size>m_max_buff_size)
        return false;
    m_buff=buff;
    m_buff_size = size;
    //m_buff_guard = NULL;
    return true;
}*/

sd_uint32_t storage_command::getPersistentSizeInByte(){
	m_persistent_size = sizeof(m_max_buff_size)\
						+calcStringSize(m_command)\
						+calcStringSize(m_filename)\
						+sizeof(m_buff_size)\
						+m_buff_size\
						+getISerializeSize();
	return m_persistent_size;
}

bool storage_command::Serialize(Serializer * inSerializer){

	if(inSerializer->getLeftSize()<getPersistentSizeInByte())
	  return false;

	inSerializer->fillBytes((sd_uint8_t *)m_start_sig, sizeof(m_start_sig));

	inSerializer->fillBytes((sd_uint8_t*)&m_persistent_size, sizeof(m_persistent_size));

	inSerializer->fillBytes((sd_uint8_t*)&m_max_buff_size, sizeof(m_max_buff_size));
	
	inSerializer->fillString(m_command);

	inSerializer->fillString(m_filename);
	
	inSerializer->fillBytes((sd_uint8_t*)&m_buff_size, sizeof(m_buff_size));
	
    if(m_buff_size>0)
        inSerializer->fillBytes(m_buff.get(), m_buff_size);
	

	inSerializer->fillBytes((sd_uint8_t*)m_end_sig, sizeof(m_end_sig));

	return true;
	
}

bool storage_command::DeSerialize(DeSerializer * inDeSerializer){

	if(checkBuffer(inDeSerializer)!=true)
	  return false;
	
	inDeSerializer->pullBytes((sd_uint8_t*)&m_max_buff_size, sizeof(m_max_buff_size	));
	inDeSerializer->pullString(&m_command);
	inDeSerializer->pullString(&m_filename);

	if(inDeSerializer->pullBytes((sd_uint8_t *)&m_buff_size, sizeof(m_buff_size))!=sizeof(m_buff_size))
	  return false;
	
	if(m_buff_size>m_max_buff_size)
		return false;

	if(m_buff_size>0){
		m_buff.reset(new sd_uint8_t[m_buff_size]);
		if(inDeSerializer->pullBytes(m_buff.get(), m_buff_size)!=m_buff_size)
			return false;
	}

	if(inDeSerializer->pullBytes((sd_uint8_t *)m_end_sig, sizeof(m_end_sig))!=sizeof(m_end_sig))
	  return false;
	  
	 return true;

}

bool storage_command::setCommand(string command, string filename, sd_uint8_t * buff, sd_uint32_t buff_size){
	
	if(buff_size>m_max_buff_size)
	  return false;

	m_command = command;
	m_filename = filename;
	m_buff_size = buff_size;
	m_buff.reset(new sd_uint8_t[m_buff_size]);
	memcpy(m_buff.get(), buff, m_buff_size);

	return true;
}

bool storage_command::CreateCommand(string filename, sd_uint8_t * buff, sd_uint32_t buff_size){
	
	return setCommand("Create", filename, buff, buff_size);
}

bool storage_command::ReadCommand(string filename){
	
	return setCommand("Read", filename, NULL, 0);
}

bool storage_command::DeleteCommand(string filename){

	return setCommand("Delete", filename, NULL,0);
}

string storage_command::getCommand(){
	return m_command;
}

bool storage_command::processCommand(){
    
    if(m_command=="Create")
        return processCreate();
    if(m_command=="Delete")
        return processDelete();
}

bool storage_command::processCreate(){
    
    bool ret = false;

    fstream fs;
    fs.open(m_filename, fstream::out|fstream::trunc|fstream::binary);
    if(!fs.fail()){
        fs.write((char*)m_buff.get(), m_buff_size);
        if(!fs.fail()) ret=true;
    fs.close();
    return ret;
   
}

bool storage_command::processDelete(){
    if(remove(m_filename.c_str())!=0)
        return false;
    return true;
}

bool storage_command::processRead(){
     
    bool ret = false;
    
    fstream fs;
    fs.open(m_filename, fstream::in|fstream::binary);
    if(!fs.fail()){
        fs.read(char*)m_buff.get(), m_buff_size);
        if(!fs.fail()) ret=true;
    fs.close();
    return ret;
      
}
