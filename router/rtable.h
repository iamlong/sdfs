#ifndef rtable_h
#define rtable_h

#include <vector>

#include "rentity.h"

//#include "droute.h"

using namespace std;


class rtable {

 public:
 	
 	//rtable(droute * router);
 	rtable();
	 ~rtable();

	//find destination of given path
        
	sd_int32_t findPath(string path);
	
	//get dests by given index.
	vector <dest *> * getPathItemDests(sd_uint32_t i);
	
	rentity * getPathItem(sd_uint32_t i);
    
	//add a new path to routeitems with destinations set
    bool addPath(string path, string destinations);

	//delete a path and related destinations 
    bool deletePath(string path);

    bool refreshPath(string path, string destinations);

	bool addPathDest(string path, string destination);
	
    bool removePathDest(string path, string destination);

 private:

    /**
     * @element-type droute
     */
    //droute * m_router;

    /**
     * @element-type rentity
     */
    vector< rentity * > m_nodeitems;
    vector< rentity * > m_blockitems;
};

#endif // rtable_h
