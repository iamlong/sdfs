#include "rentry.h"
#include "../sha1/sha1.h"
#include "../include/error.h"

#include <stdlib.h>
#include <memory.h>

    /** 
     *  rentry stands for an inode entry for a file or directory in the file system. It actually referencing to a network location of the filenode structure. This filenode structure include the information of  
     */



RET_CODE rentry::hash(unsigned char * path, unsigned int path_size, unsigned char * hashbuff, unsigned int buff_size)
{
    SHA1_CTX context;
    if(buff_size < 20 || hashbuff == NULL)
        return ret_err;
    
    SHA1Init(&context);
    SHA1Update(&context, path, path_size);
    SHA1Final(hashbuff, &context);
    return ret_ok;

}

rentry::rentry(unsigned char * path, unsigned int path_size)
{
    m_path = (unsigned char*) malloc((path_size+1)*sizeof(unsigned char));
    m_path_size = path_size;
    
    memset(m_path, 0, (m_path_size+1)*sizeof(unsigned char));
    memcpy(m_path, path, (m_path_size)*sizeof(unsigned char));
        
    m_hash = (unsigned char*) malloc(DIGEST_LEN*sizeof(unsigned char));
    m_hash_size = DIGEST_LEN;
    memset(m_hash, 0, m_hash_size*sizeof(unsigned char));
    
    hash(m_path, m_path_size, m_hash, m_hash_size);
    
}

bool rentry::match(unsigned char * hash, unsigned int hash_size)
{
    if(hash_size != m_hash_size)
        return false;
    
    if(memcmp(hash, m_hash, m_hash_size*sizeof(unsigned char))==0)
        return true;
    else
        return false;
        
}

void rentry::replacedest(unsigned char * dest, unsigned int dest_size)
{ 
}

void rentry::cleandests()
{
    int size = m_dests.size();
    if(size <= 0)
        return;
    
    dest * temp;

    for (int i = 0; i < size; i++)
    {
        temp = &(*m_dests[i]);
        if(temp->dest!=NULL){
            free(temp->dest);
            temp->dest = NULL;
            delete temp;
        }
    }
    m_dests.clear(); 
}

int rentry::adddest(unsigned char * dest, unsigned int dest_size)
{
    return 0;
}

int rentry::removedest(unsigned char * dest, unsigned int dest_size)
{
    return 0;
}