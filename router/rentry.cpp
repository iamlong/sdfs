#include "rentry.h"
#include "../sha1/sha1.h"
#include "../include/error.h"

#include <stdlib.h>
#include <memory.h>

#define DIGEST_LEN 20

    /** 
     *  rentry stands for an inode entry for a file or directory in the file system. It actually referencing to a network location of the filenode structure. This filenode structure include the information of  
     */



RET_CODE rentry::hash(unsigned char * path, unsigned int path_size, unsigned char * hashbuff, unsigned int buff_size)
{
    CSHA1 sha1;
    if(buff_size < 20 || hashbuff == NULL)
        return ret_err;
    
    sha1.Update(path, path_size);
    sha1.Final();
	sha1.ReportHash((char*)hashbuff);
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

int rentry::replacedests(unsigned char * dests, unsigned int dests_size)
{
    //dest fornamt should be like "ip@port;ip@port"
    //or we can replace ip with hostname like "hostname@port;ip@port"
    cleandests();
    
    if(dests_size <= 0 )
        return -1;
    
    unsigned char * pt = dests;
    unsigned char * temp;
    unsigned int tempsize;
    dest * destbuff;
    unsigned int j = 0;
    for (int i = 0; i < dests_size+1; i++)
    {
        if(dests[i] != ';' && dests[i] != '\0')
            continue;
        
        if(j == i) //there is no string between ";;" and also there is no string between ";\0"
            continue;
            
        //create new dest entry for dests
        tempsize = i-j;
        temp  = (unsigned char *)malloc((tempsize+1)*sizeof(unsigned char));
        memset(temp, 0, (tempsize+1)*sizeof(unsigned char));
        memcpy(temp, pt, (tempsize)*sizeof(unsigned char));

        
        //if dest already exist, just skip  
        int destsize = m_dests.size();
        for(int l = 0; l < destsize; l ++ )
        {
            if(m_dests[l]->dest_len == tempsize)
                if(memcmp(temp, m_dests[l]->dest,tempsize*sizeof(unsigned char)))
                {
                    free(temp);
                    temp = NULL;
                    break;
                }
        }
        
        if(temp != NULL)
        {
            destbuff = new dest();
            destbuff->dest_len = tempsize;
            destbuff->dest = temp;
            m_dests.push_back(destbuff);
        }
        
        pt = &dests[i+1]; // pt go to next position
        j = i + 1;
        if(j >= dests_size)
            return m_dests.size();
    }
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
        temp = &(*m_dests[i]);
        if(temp->dest!=NULL){
            free(temp->dest);
            temp->dest = NULL;
            delete temp;
        }
    }
    m_dests.clear(); 
}

unsigned char * rentry::mergedests()
{
    int size = m_dests.size();
    if(size <= 0)
        return NULL;
    
    int destsbufflen;
    for (int i = 0; i < size; i++)
        destsbufflen = m_dests[i]->dest_len+1;
        
    unsigned char * head = (unsigned char *) malloc ((destsbufflen+1)*sizeof(unsigned char));
    memset(head, 0, (destsbufflen+1)*sizeof(unsigned char));
    
    unsigned char * temp = head;
    for(int i = 0; i < size; i++){
        memcpy(head,m_dests[i]->dest, m_dests[i]->dest_len*sizeof(unsigned char));
        temp +=m_dests[i]->dest_len*sizeof(unsigned char);
        *temp = ';';
    }
    
	return head;
        
}
int rentry::adddest(unsigned char * dest, unsigned int dest_size)
{
    return 0;
}

int rentry::removedest(unsigned char * dest, unsigned int dest_size)
{
    return 0;
}