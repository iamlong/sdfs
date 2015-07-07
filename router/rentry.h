#ifndef rentry_h
#define rentry_h

#include <vector>


class rtable;


    /** 
     *  rentry stands for an inode entry for a file or directory in the file system. It actually referencing to a network location of the filenode structure. This filenode structure include the information of  
     */
class rentry {

 public:

    int hash(char * path, int path_size, char * hasbuff, int buff_size);

    int match(char * hash, int hash_size);

    int replacedest(char * dest, int dest_size);

    int adddest(char * dest, int dest_size);

    int removedest(char * dest, int dest_size);

 private:
    char * ehash;
    int ehash_size;
    char * path;
    int path_size;
    std::vector< char * > dest;

};

#endif // rentry_h
