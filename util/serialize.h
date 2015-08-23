#ifndef serialize_h
#define serialize_h
//#include <sys/types.h>

#include "serializer.h"
#include "../util/stdtype.h"

class Serializer;
class DeSerializer;

class ISerialize{
	public:
		virtual int getPersistentSizeInByte()=0;
		virtual bool Serialize(Serializer * inSerializer) = 0;
		virtual bool DeSerialize(DeSerializer * inDeSerializer)=0;
		
	protected:
		
		unsigned long m_persistent_size;
		char m_start_sig[2];
		char m_end_sig[2];

		int getISerializeSize(){
			return sizeof(m_start_sig) + sizeof(m_end_sig) + sizeof(m_persistent_size);
		};
};

#endif
