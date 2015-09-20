#ifndef trunk_h
#define trunk_h

#include <string>
#include "../util/stdtype.h"

using namespace std;

class trunk {
	
	public: 
		trunk(string trunkname, string path, sd_uint32_t max_size);
		bool write(sd_uint8_t * buff, sd_uint32_t size); //return write success or not
		sd_int32_t read(sd_uint8_t * buff, sd_uint32_t buff_size); //return readed data from trunk, -1 means no file exist
	
	private:
		string m_name;
		string m_path;
		sd_uint32_t m_trunk_size; //real data size in the trunk;
		sd_uint32_t m_max_trunk_size;
		sd_uint8_t * m_buff;

		string genPath(string trunkname, string path);
		size_t getFileSize(FILE *fp);
};
#endif
