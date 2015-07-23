#ifndef rtable_h
#define rtable_h

#include <vector>

#include "rentry.h"

//#include "droute.h"

using namespace std;


class rtable {

 public:
 	
 	//rtable(droute * router);
 	rtable();
	 ~rtable();

	//find destination of given path
    vector <dest *> * getItemDests(int i);
	int findpath(string path);

	//add a new path to routeitems with destinations set
    bool addpath(string path, string destinations);

    bool deletepath(string path);

    virtual int updatepathdestination(string path, string destination);

    virtual int removepathdestination(string path, string destination);

 private:

    /**
     * @element-type droute
     */
    //droute * m_router;

    /**
     * @element-type rentry
     */
    vector< rentry * > m_routeitems;
};

#endif // rtable_h
