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

int Serializer::fillBytes(uint8_t * fillin, int size){
	
	int size_to_fill;
	
	if (size + m_used_size>m_buff_size)
		size_to_fill = m_buff_size - m_used_size;
	else
		size_to_fill = size;
		
	memcpy(m_buffer+m_used_size, fillin, size_to_fill);
	m_used_size += size_to_fill;
	
	return size_to_fill;
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

DeSerializer::DeSerializer(uint8_t * buff, int buff_size){
	m_buffer = buff;
	m_buff_size = buff_size;
	m_pulled_size = 0;
}

DeSerializer::~DeSerializer(){
	return;
}
uint8_t * DeSerializer::getFilledBuffer(){
	return m_buffer;
}

int DeSerializer::getLeftSize(){
	return m_buff_size - m_pulled_size;
}

int DeSerializer::getPulledSize(){
	return m_pulled_size;
}

int DeSerializer::getTotalSize(){
	return m_buff_size;
}

int DeSerializer::pullBytes(uint8_t * out, int size){
	int size_to_pull;
	
	if(size > getLeftSize())
		size_to_pull = getLeftSize();
	else
		size_to_pull = size;
	
	memcpy(out, m_buffer+m_pulled_size, size_to_pull);
	
	m_pulled_size += size_to_pull;
	
	return size_to_pull;
}

bool DeSerializer::pullObject(ISerialize * obj){
	int objsize = obj->getPersistentSizeInByte();
	
	if(getLeftSize() < objsize)
		return false;
	
	return obj->DeSerialize(this);
}
