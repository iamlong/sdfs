#ifndef SERIALIZER_H
#define SERIALIZER_H

#include "serialize.h"
#include "stdtype.h"
class Serializer
{
	public:
		Serializer(int PersistentSize);
		uint8_t * getFilledBuffer();
		bool fillBytes(uint8_t * fillin, int size);
		bool fillObject(ISerialize * obj);
		~Serializer();
		
	private:
		int m_buff_size;
		int m_used_size;
		uint8_t * m_buffer;
};

#endif
