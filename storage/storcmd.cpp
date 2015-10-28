#include "storcmd.h"

void storage_command::init(){

	set_sig(STORCMD_START_SIG, STORCMD_END_SIG);
}

storage_command::storage_command(sd_uint32_t maxsize){
	m_max_buff_size = maxsize;
	init();
}

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

	inSerializer->fillString(m_command);

	inSerializer->fillString(m_filename);
	
	inSerializer->fillBytes((sd_uint8_t*)&m_buff_size, sizeof(m_buff_size));
	
    if(m_buff_size>0)
        inSerializer->fillBytes((sd_uint8_t*)m_buff, m_buff_size);
	

	inSerializer->fillBytes((sd_uint8_t*)m_end_sig, sizeof(m_end_sig));

	return true;
	
}

bool storage_command::DeSerialize(DeSerializer * inDeSerializer){

	if(checkBuffer(inDeSerializer)!=true)
	  return false;

	inDeSerializer->pullString(&m_command);
	inDeSerializer->pullString(&m_filename);

	if(inDeSerializer->pullBytes((sd_uint8_t *)&m_buff_size, sizeof(m_buff_size))!=sizeof(m_buff_size))
	  return false;
	
	if(m_buff_size>m_max_buff_size)
		return false;

	if(m_buff!=NULL)
	  free(m_buff);

	if(m_buff_size>0){
		m_buff = (sd_uint8_t *)malloc(m_buff_size);

		if(inDeSerializer->pullBytes(m_buff, m_buff_size)!=m_buff_size)
			return false;
	}

	if(inDeSerializer->pullBytes((sd_uint8_t *)m_end_sig, sizeof(m_end_sig))!=sizeof(m_end_sig))
	  return false;

}

bool storage_command::setCommand(string command, string filename, sd_uint8_t * buff, sd_uint32_t buff_size){
	
	if(buff_size>m_max_buff_size)
	  return false;

	m_command = command;
	m_filename = filename;
	m_buff = buff;
	m_buff_size = buff_size;
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
