#include "trunk.h"
#include <stdio.h>

void trunk::trunk(string trunkname, string path, sd_uint32_t max_size){
	m_name = trunkname;
	m_max_trunk_size = max_size;
	m_path = path;
	m_buff = null;
	m_max_trunk_size = 0;
}

bool trunk::write(sd_uint8_t* buff, sd_uint32_t size){
	
	if( size>m_max_trunk_size)
	  return false;
	
	//I need to add code to form the file path
	FILE * fp = fopen(m_name, "w");

	if(fp==NULL)
	  return false;

	size_t ret = fwrite(buff, size, 1, fp);
	if(ret!=size)
		return false;

	m_trunk_size = ret;
	return true
}
