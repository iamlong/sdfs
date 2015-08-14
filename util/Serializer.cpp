#include "serializer.h"
#include <memory.h>

Serializer::Serializer(int PersistentSize){
	
	m_buffer = new uint8_t[PersistentSize];
	m_buff_size = PersistentSize;
	m_used_size = 0;
	
}

uint8_t * Serializer::getFilledBuffer(){
	return m_buffer;
}

bool Serializer::fillBytes(uint8_t * fillin, int size){
	
	if (size + m_used_size>m_buff_size)
		return false;
		
	memcpy(m_buffer+m_used_size, fillin, size);
	m_used_size += size;
	
	return true;
}

bool Serializer::fillObject(ISerialize * obj){
	
	int objsize = obj->getPersistentSizeInByte();
	
	if(objsize+m_used_size > m_buff_size)
		return false;
	
	obj->Serialize(this);
}

int Serializer::getUsedSize(){
	return m_used_size;
}

int Serializer::getLeftSize(){
	return m_buff_size - m_used_size;
}

int Serializer::getSize(){
	return m_buff_size;
}

Serializer::~Serializer(){
	delete m_buffer;
}
