#ifndef SERIALIZER_H
#define SERIALIZER_H

#include "serialize.h"
#include "stdtype.h"
#include <string>

class ISerialize;

using namespace std;

class Serializer
{
	public:
		Serializer(int PersistentSize);
		sd_uint8_t * getFilledBuffer();
		int fillBytes(sd_uint8_t * fillin, int size);
		bool fillObject(ISerialize * obj);
		bool fillString(string str);
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
		bool pullString(string * str);
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
