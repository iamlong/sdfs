#include "rentry.h"
#include "../sha1/sha1.h"
#include "../include/error.h"

#include <stdlib.h>
#include <memory.h>

#define DIGEST_LEN 20

    /** 
     *  rentry stands for an inode entry for a file or directory in the file system. It actually referencing to a network location of the filenode structure. This filenode structure include the information of  
     */



string rentry::hash(const string path)
{
    CSHA1 sha1;
    char hashbuff[DIGEST_LEN];
    
    sha1.Update((unsigned char *)path.c_str(), path.size());
    sha1.Final();
	sha1.ReportHash(hashbuff);
    return hashbuff;

}

rentry::rentry(string path)
{
    m_path = path;
        
    m_hash = hash(path);
    
}

bool rentry::operator==(const string & comphash)
{
	if(m_hash == comphash)
        return true;
    else
        return false;
        
}

int rentry::replacedests(const string dests)
{
    //dest fornamt should be like "ip@port;ip@port"
    //or we can replace ip with hostname like "hostname@port;ip@port"
    cleandests();
    int commpos;
    string tempstr = dests;
	
	commpos = tempstr.find(';');
	while(commpos!=string::npos){
		adddest(tempstr.substr(0,commpos));
		tempstr = tempstr.substr(commpos+1);
		commpos = tempstr.find(';');
	}
	adddest(tempstr);
	
    return m_dests.size();   
}

void rentry::cleandests()
{
    int size = m_dests.size();
    if(size <= 0)
        return;
    
    dest * temp;

    for (int i = 0; i < size; i++)
    {
        temp = &m_dests[i];
		delete temp;
    }
    m_dests.clear(); 
}

string rentry::toString()
{
    int size = m_dests.size();
    string str = NULL;

    for (int i = 0; i < size; i++)
        str += m_dests[i].toString();
        
	return str;
        
}
int rentry::adddest(const string deststr)
{
	dest destbuff = new dest(deststr);
	for (int i = 0; i<m_dests.size();i++){
		if(m_dests[i]==destbuff)
			return 0;
	}
	m_dests.push_back(destbuff);
	return 1;
}

int rentry::removedest(unsigned char * dest, unsigned int dest_size)
{
    return 0;
}

rentry::~rentry()
{
	//cleandests();
}
