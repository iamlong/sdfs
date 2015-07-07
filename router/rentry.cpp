#include "rentry.h"


    /** 
     *  rentry stands for an inode entry for a file or directory in the file system. It actually referencing to a network location of the filenode structure. This filenode structure include the information of  
     */



int rentry::hash(char * path, int path_size, char * hasbuff, int buff_size);

int rentry::match(char * hash, int hash_size);

int rentry::replacedest(char * dest, int dest_size);

int rentry::adddest(char * dest, int dest_size);

int rentry::removedest(char * dest, int dest_size);