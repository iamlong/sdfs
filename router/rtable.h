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
        
	int findpath(string path);
	
	vector <dest *> * getItemDests(int i);
    
	//add a new path to routeitems with destinations set
    bool addpath(string path, string destinations);

	//delete a path and related destinations 
    bool deletepath(string path);

    bool refreshpath(string path, string destinations);

	bool addpathdest(string path, string destination);
	
    bool removepathdest(string path, string destination);

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
