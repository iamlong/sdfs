#ifndef rentry_h
#define rentry_h

#include <vector>


class rtable;


    /** 
     *  rentry stands for an inode entry for a file or directory in the file system. It actually referencing to a network location of the filenode structure. This filenode structure include the information of  
     */
class rentry {

 public:

    virtual char hash(char * path);

    virtual int match(char * hash);

    virtual int replacedestination(char * destination);

    virtual int adddestination(char * destination);

    virtual int removedestination(char * destination);

 public:
    std::vector< char > rehash;
    std::vector< char > path;
    std::vector< char > destination;

 public:

    /**
     * @element-type rtable
     */
    rtable * routeitems;
};

#endif // rentry_h
