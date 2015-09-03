#ifndef serialize_h
#define serialize_h
//#include <sys/types.h>

#include "serializer.h"
#include "../util/stdtype.h"
#include <string.h>
#include <string>

class Serializer;
class DeSerializer;

using namespace std;

class ISerialize{
	public:
		virtual sd_uint32_t getPersistentSizeInByte()=0;
		virtual bool Serialize(Serializer * inSerializer) = 0;
		virtual bool DeSerialize(DeSerializer * inDeSerializer)=0;
		
	protected:
		
		sd_uint32_t m_persistent_size;
		char m_start_sig[2];
		char m_end_sig[2];

		sd_uint32_t getISerializeSize();
		
		bool checkBuffer(DeSerializer * inDeSerializer);
		void set_sig(const char start_sig[], const char end_sig[]);
		static sd_uint32_t calcStringSize(string eval);
};

#endif
