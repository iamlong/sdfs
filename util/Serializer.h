#ifndef SERIALIZER_H
#define SERIALIZER_H

#include "serialize.h"
#include "stdtype.h"

class ISerialize;

class Serializer
{
	public:
		Serializer(int PersistentSize);
		uint8_t * getFilledBuffer();
		bool fillBytes(uint8_t * fillin, int size);
		bool fillObject(ISerialize * obj);
		int getUsedSize();
		int getLeftSize();
		int getSize();
		~Serializer();
		
	private:
		int m_buff_size;
		int m_used_size;
		uint8_t * m_buffer;
};

#endif
