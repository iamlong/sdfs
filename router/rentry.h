#ifndef rentry_h
#define rentry_h

#include <vector>
#include "../include/error.h"


class rtable;


    /** 
     *  rentry stands for an inode entry for a file or directory in the file system. It actually referencing to a network location of the filenode structure. This filenode structure include the information of  
     */
class rentry {

 public:
    struct dest
    {
        unsigned char * dest;
        unsigned int dest_len;
    };
 public:
    rentry(unsigned char * path, unsigned int path_size);

    static RET_CODE hash(unsigned char * path, unsigned int path_size, unsigned char * hasbuff, unsigned int buff_size);

    bool match(unsigned char * hash, unsigned int hash_size);

    //return how many dest items are in the m_dests. negative for error.
    int replacedests(unsigned char * dest, unsigned int dest_size);

    int adddest(unsigned char * dest, unsigned int dest_size);

    int removedest(unsigned char * dest, unsigned int dest_size);

 private:
    unsigned char * m_hash;
    unsigned int m_hash_size;
    unsigned char * m_path;
    unsigned int m_path_size;
    std::vector< dest * > m_dests;
    
    void cleandests();

};

#endif // rentry_h
