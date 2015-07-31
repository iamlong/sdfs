#ifndef rentry_h
#define rentry_h

#include <vector>
#include <string>
#include "../include/error.h"
#include "dest.h"
#include "../util/utils.h"

using namespace std;

class rtable;


    /** 
     *  rentry stands for an inode entry for a file or directory in the file system. It actually referencing to a network location of the filenode structure. This filenode structure include the information of  
     */
class rentry {

 public:
    rentry(string key);
	~rentry();

    static const int hash_size = DIGEST_LEN;

    bool match(const char * comphash);

    //return how many dest items are in the m_dests.
    int refreshDests(const string destsString);
    
    vector<dest *> * getDests();

    bool addDest(const string dest);

    bool removeDest(const string dest);
    
    string toString();

	void cleanDests();
	
 private:
    char m_hash[hash_size];
    unsigned int m_hash_size;
    string m_key;
    unsigned int m_path_size;
    vector< dest * > m_dests;
    


};

#endif // rentry_h
