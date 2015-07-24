#ifndef rentry_h
#define rentry_h

#include <vector>
#include <string>
#include "../include/error.h"
#include "dest.h"

#define DIGEST_LEN 20

using namespace std;

class rtable;


    /** 
     *  rentry stands for an inode entry for a file or directory in the file system. It actually referencing to a network location of the filenode structure. This filenode structure include the information of  
     */
class rentry {

 public:
    rentry(string reqpath);
	~rentry();

    static void hash(const string path, char * hashbuff);
    static const int hash_size = DIGEST_LEN;

    bool match(const char * comphash);

    //return how many dest items are in the m_dests.
    int refreshdests(const string destsString);
    
    vector<dest *> * getDests();

    bool adddest(const string dest);

    bool removedest(const string dest);
    
    string toString();

	void cleandests();
	
 private:
    char m_hash[hash_size];
    unsigned int m_hash_size;
    string m_path;
    unsigned int m_path_size;
    vector< dest * > m_dests;
    


};

#endif // rentry_h
