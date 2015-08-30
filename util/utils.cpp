#include "utils.h"

void utils::hash(const string path, char * hashbuff)
{
    CSHA1 sha1;
  
    sha1.Update((unsigned char *)path.data(), path.size());
    sha1.Final();
	sha1.GetHash((unsigned char *)hashbuff);
}

