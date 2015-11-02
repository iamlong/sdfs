#ifndef storage_command_h
#define storage_command_h
#include <memory>
#include "../util/serialize.h"
#include "stdlib.h"
#include "../util/sig.h"
#include <fstream>

class storage_command: public ISerialize{
	
	public:
		//serializer and deserializer
		sd_uint32_t getPersistentSizeInByte();
		bool Serialize(Serializer * inSerializer);
		bool DeSerialize(DeSerializer * inDeSerializer);

		void init(); //initialize Storage_Command
		storage_command(sd_uint32_t maxsize);
        //~storage_command();

		bool CreateCommand(string filename, sd_uint8_t * buff, sd_uint32_t buff_size);
		bool ReadCommand(string filename); 
		bool DeleteCommand(string filename);
		string getCommand();
        bool setBuff(sd_uint8_t* buff, sd_uint32_t size);
        bool processCommand();


	private:
		sd_uint32_t m_max_buff_size;
		string m_command;
		string m_filename;
		sd_uint32_t m_buff_size;
        shared_ptr<sd_uint8_t> m_buff;
		bool setCommand(string command, string filename, sd_uint8_t * buff, sd_uint32_t buff_size);
        bool createbuff(sd_uint32_t size);
};

#endif
