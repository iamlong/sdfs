#include <stdio.h>
#include "trunk.h"


string trunk::genPath(string trunkname, string path){
	if(path[path.size()-1]!='/')
	  path = path + '/';
	return path+trunkname;
}

size_t trunk::getFileSize(FILE * fp){
	size_t pos = ftell(fp);
	fseek(fp, 1, SEEK_SET);
	fseek(fp, 0, SEEK_END);
	size_t ret = ftell(fp);
	fseek(fp, pos, SEEK_SET);
	return ret;
}

sd_int32_t trunk::write(string trunkname, string path, sd_uint8_t* buff, sd_uint32_t size){
	
	if( size>max_trunk_size)
	  return -1;
	
	string trunkpath = genPath(trunkname, path);
	FILE * fp = fopen(trunkpath.c_str(), "wb");

	if(fp==NULL)
	  return -1;

	size_t ret = fwrite(buff, 1, size, fp);
	if(ret!=size)
		return -1;

	fclose(fp);
	
	return ret;
}

sd_int32_t trunk::read(string trunkname, string path, sd_uint8_t* buff, sd_uint32_t buff_size){
	string trunkpath = genPath(trunkname, path);
	FILE * fp = fopen(trunkpath.c_str(), "r");

	if(fp==NULL)
	  return -1;
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

