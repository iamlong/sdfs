#include "serializer.h"
#include <memory.h>
#include <stdlib.h>
#include <stdio.h>

Serializer::Serializer(int PersistentSize){
	
	m_buffer = new sd_uint8_t[PersistentSize];
	m_buff_size = PersistentSize;
	m_used_size = 0;
	
}

sd_uint8_t * Serializer::getFilledBuffer(){
	return m_buffer;
}

int Serializer::fillBytes(sd_uint8_t * fillin, int size){
	
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
	
	sd_uint32_t objsize = obj->getPersistentSizeInByte();
	
	if(objsize+m_used_size > m_buff_size)
		return false;
	
	obj->Serialize(this);
}

bool Serializer::fillString(string str){
	sd_uint32_t size = str.size();
	
	if(getLeftSize()<(size+sizeof(size)))
		return false;
	
	fillBytes((sd_uint8_t *)&size, sizeof(size));
	fillBytes((sd_uint8_t *)str.data(),size);
	
	return true;
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

DeSerializer::DeSerializer(sd_uint8_t * buff, int buff_size){
	m_buffer = buff;
	m_buff_size = buff_size;
	m_pulled_size = 0;
}

DeSerializer::~DeSerializer(){
	return;
}
sd_uint8_t * DeSerializer::getFilledBuffer(){
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

int DeSerializer::pullBytes(sd_uint8_t * out, int size){
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
	sd_uint32_t objsize = obj->getPersistentSizeInByte();
	
	if(getLeftSize() < objsize)
		return false;
	
	return obj->DeSerialize(this);
}

bool DeSerializer::pullString(string * str){
	
	sd_uint32_t	size;
	
	pullBytes((sd_uint8_t*)&size, sizeof(size));
	
	sd_uint8_t * buff = (sd_uint8_t *)malloc(size);
	
	if(buff==NULL)
		return false;
		
	pullBytes(buff, size);
	
	str->append((char *)buff, size);
	
	free(buff);
	
	return true;
}

