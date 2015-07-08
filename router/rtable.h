#ifndef rtable_h
#define rtable_h

#include <vector>

#include "rentry.h"

class droute;

class rtable {

 public:

    virtual char findpath(char * path);

    virtual int addpath(char * path, char destination);

    virtual int deletepath(char * path);

    virtual int updatepathdestination(char * path, char * destination);

    virtual int removepathdestination(char * path, char * destination);

 public:

    /**
     * @element-type droute
     */
    droute * router;

    /**
     * @element-type rentry
     */
    std::vector< rentry > routeitems;
};

#endif // rtable_h
