#ifndef droute_h
#define droute_h

#include "rtable.h"



    /** 
     *  drouter is an service instance running on each linux instance to provide capability to find a specific file or directory by given a Unix path. 
     */
class droute {

 public:

    virtual int addfile(char * path, char * destination);

    virtual int deletefile(char * path);

    virtual int appenddestination(char * path, char * destination);

    virtual int removedestination(char * path, char * destination);

 public:
    
    /** 
     *  command_port is the UDP port which is used to get commands from other machine
     */
    int command_port;

 public:

    rtable * routetable;
};

#endif // droute_h
