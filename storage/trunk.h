#ifndef trunk_h
#define trunk_h

#include <string>
#include "../util/stdtype.h"

using namespace std;

class trunk {
	
	public: 
		static sd_int32_t write(string trunkname, string path, sd_uint8_t * buff, sd_uint32_t size); //return byte successfully written to trunk, -1 for failure
		static sd_int32_t read(string trunkname, string path, sd_uint8_t * buff, sd_uint32_t buff_size); //return readed data from trunk, -1 for failure
		static sd_uint32_t max_trunk_size;
	
	private:

		static string genPath(string trunkname, string path);
		static size_t getFileSize(FILE *fp);
};
#endif
