#ifndef rentity_h
#define rentity_h

#include <vector>
#include <string>
#include "../include/error.h"
#include "dest.h"
#include "../util/utils.h"
#include "../util/stdtype.h"

using namespace std;

    /** 
     *  rentity stands for an entity in the file system. 
	 *  An entity is the basic storage unit in the file system
     *  it point to a network location of a siBlock.
     *  An entity is described by 
	 *  	a key - a string of the name of the entity. 
	 *		a hash - a hash string which is caculated based on the key
	 *		a vector of destinations - which point to the server IP/hostname and port
	 *			IP/hostname + port is point to the storage service which provide storge capability
	 *			 
     */
class rentity {

 public:
    rentity(string key);
	~rentity();

    static const sd_uint32_t hash_size = DIGEST_LEN;

    bool match(const char * comphash);

    //return how many dest items are in the m_dests.
    sd_uint32_t refreshDests(const string destsString);
    
    vector<dest *> * getDests();

    bool addDest(const string dest);

    bool removeDest(const string dest);
    
    string toString();

	void cleanDests();
	
 private:
    char m_hash[hash_size]; //m_hash is generated from m_key.
    sd_uint32_t m_hash_size; //size in byte of hash string. It's based on the hash methodology we choose; for SHA1, it sets to 20.
    string m_key; //the original key of the given entry. it is actually the string name of a given object
    sd_uint32_t m_path_size;
    vector< dest * > m_dests;
    


};

#endif // rentity_h
