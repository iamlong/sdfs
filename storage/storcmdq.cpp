#include "storcmdq.h"

bool storage_command_q::pushtoQ(storage_command * inCmd){
	
	m_mtx.lock();
	m_commandQ.push(inCmd);
	m_mtx.unlock();
	return true;
}

storage_command * storage_command_q::pullfromQ(){

	storage_command * ret;
	
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

storage_command_q::~storage_command_q(){
//    storage_command * tq;
//    while(m_commandQ.size()>0){
//        tq = pullfromQ();
//        delete tq;
//    }
}

bool cmd_push(storage_command_q* q, storage_command* inCmd){
    q->pushtoQ(inCmd);
}

storage_command* cmd_pull(storage_command_q* q){
    return q->pullfromQ();
}
