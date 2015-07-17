#ifndef rentry_h
#define rentry_h

#include <vector>
#include <string>
#include "../include/error.h"
#include "dest.h"

using namespace std;

class rtable;


    /** 
     *  rentry stands for an inode entry for a file or directory in the file system. It actually referencing to a network location of the filenode structure. This filenode structure include the information of  
     */
class rentry {

 public:
    rentry(string reqpath);
	~rentry();

    static string hash(const string path);

    bool operator==(const string & comphash);

    //return how many dest items are in the m_dests. negative for error.
    int replacedests(const string destsString);

    int adddest(const string dest);

    int removedest(const string dest);
    
    string toString();

	void cleandests();
	
 private:
    string m_hash;
    unsigned int m_hash_size;
    string m_path;
    unsigned int m_path_size;
    vector< dest > m_dests;
    


};

#endif // rentry_h
