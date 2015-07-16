#ifndef rtable_h
#define rtable_h

#include <vector>

#include "rentry.h"

class droute;

class rtable {

 public:

    virtual string findpath(string path);

    virtual int addpath(string path, string destination);

    virtual int deletepath(string path);

    virtual int updatepathdestination(string path, string destination);

    virtual int removepathdestination(string path, string destination);

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
