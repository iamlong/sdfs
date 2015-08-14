#ifndef serialize_h
#define serialize_h
#include "../util/stdtype.h"
#include "serializer.h"

class Serializer;

class ISerialize{
	public:
		virtual int getPersistentSizeInByte()=0;
		virtual bool Serialize(Serializer * inSerializer) = 0;
		virtual bool DeSerialize(uint8_t * buff, int buff_size)=0;
		
	protected:
		char m_start_sig[2];
		char m_end_sig[2];
		int m_persistent_size;
		int getISerializeSize(){
			return sizeof(m_start_sig) + sizeof(m_end_sig) + sizeof(m_persistent_size);
		};
};

#endif
