#include "Serializer.h"

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
		
	memcpy(m_buffer, fillin, size);
	m_used_size += size;
	
	return true;
}

bool Serializer::fillObject(ISerialize * obj){
	
	int objsize = obj->getPersistentSizeInByte();
	
	if(objsize+m_used_size > m_buff_size)
		return false;
	
	obj->Serialize(this);
}
