#ifndef SERIALIZER_H
#define SERIALIZER_H

#include "serialize.h"
#include "stdtype.h"

class ISerialize;

class Serializer
{
	public:
		Serializer(int PersistentSize);
		sd_uint8_t * getFilledBuffer();
		int fillBytes(sd_uint8_t * fillin, int size);
		bool fillObject(ISerialize * obj);
		int getUsedSize();
		int getLeftSize();
		int getSize();
		~Serializer();
		
	private:
		int m_buff_size;
		int m_used_size;
		sd_uint8_t * m_buffer;
};

class DeSerializer
{
	public:
		DeSerializer(sd_uint8_t * buff, int buff_size);
		sd_uint8_t * getFilledBuffer();
		int pullBytes(sd_uint8_t * out, int size);
		bool pullObject(ISerialize * obj);
		int getPulledSize();
		int getLeftSize();
		int getTotalSize();
		~DeSerializer();
		
	private:
		int m_buff_size;
		int m_pulled_size;
		sd_uint8_t * m_buffer;
};

#endif
