#ifndef droute_h
#define droute_h

#include "rtable.h"



    /** 
     *  drouter is an service instance running on each linux instance to provide capability to find a specific file or directory by given a Unix path. 
     */
class droute {

 public:

    virtual int addfile(string path, string dest);

    virtual int deletefile(string path, int path_size);

    virtual int appenddestination(string path, int path_size, string dest, int dest_size);

    virtual int removedestination(string path, int path_size, string dest, int dest_size);

 public:
    
    /** 
     *  command_port is the UDP port which is used to get commands from other machine
     */
    int command_port;

 public:

    rtable * routetable;
};

#endif // droute_h
