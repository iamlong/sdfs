#ifdefine rprocess_h
#define rprocess_h

#include <string>

using namespace std;

	/**
	 *	rprocess is used to describe a remote process which is opening file for read or write
	*/
struct rprocess{
	
	public:
		string host;	//remote host ip or host name
		int process;	//process number which open the file, -1 if the process is dead
	
};

	/**
	 *	memblock is used to describe memory block which is used for serialization and deserialization
	*/
struct memblock{
	
	public:
		unsigned int size;	//remote host ip or host name
		char mem[];	
	
};

enum sinode_type{
	file = 1;
	path = 2;
	link = 3;
};

struct nodeid{
	static const int hash_size = DIGEST_LEN;
	char m_hash[DIGEST_LEN];
	string m_path;
	sinode_type m_type;
};
#endif
