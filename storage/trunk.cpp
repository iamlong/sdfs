#include <stdio.h>
#include "trunk.h"

trunk::trunk(string trunkname, string path, sd_uint32_t max_size){
	m_name = trunkname;
	m_max_trunk_size = max_size;
	m_path = path;
	m_buff = NULL;
}

string trunk::genPath(string trunkname, string path){
	if(path[path.size()-1]!='/')
	  path = path + '/';
	return path+trunkname;
}

size_t trunk::getFileSize(FILE * fp){
	fseek(fp, 0, SEEK_END);
	size_t ret = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	return ret;
}

bool trunk::write(sd_uint8_t* buff, sd_uint32_t size){
	
	if( size>m_max_trunk_size)
	  return false;
	
	string trunkpath = genPath(m_name, m_path);
	FILE * fp = fopen(trunkpath.c_str(), "wb");

	if(fp==NULL)
	  return false;

	size_t ret = fwrite(buff, 1, size, fp);
	if(ret!=size)
		return false;

	m_trunk_size = ret;
	return true;
}

sd_int32_t trunk::read(sd_uint8_t* buff, sd_uint32_t buff_size){
	string trunkpath = genPath(m_name, m_path);
	FILE * fp = fopen(trunkpath.c_str(), "wb");

	if(fp==NULL)
	  return false;
	size_t fsize = getFileSize(fp);
	if(fsize>buff_size){
		fclose(fp);
		return -1;
	}

	size_t ret = fread(buff, 1, fsize, fp);
	if(ret!=fsize){
		fclose(fp);
		return -1;
	}

	fclose(fp);
	return ret;

}

