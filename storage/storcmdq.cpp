#include "storcmdq.h"

bool storage_command_q::pushtoQ(string command, sd_uint8_t * buff, sd_uint32_t size){
	
	storage_command cmd;

	cmd.command = command;
	cmd.data_buff = buff;
	cmd.data_size = size;
	
	m_mtx.lock();
	m_commandQ.push(cmd);
	m_mtx.unlock();
	return true;
}

storage_command storage_command_q::pullfromQ(){

	storage_command ret;
	
	m_mtx.lock();
	ret = m_commandQ.front();
	m_commandQ.pop();
	m_mtx.unlock();
	
	return ret;
}

sd_uint32_t storage_command_q::QSize(){
	
	sd_uint32_t ret;
	m_mtx.lock();
	ret = m_commandQ.size();
	m_mtx.unlock();

	return ret;
	
}

