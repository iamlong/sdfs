#ifndef sinode_h
#define sinode_h

#include "../router/dest.h"
	/**
	 *	sinode is represent an inode in the file system for a file or a path.
	 *	it includes below information in a sinode
	 *		a hash which is used to uniquely name a sinode
	 *		a key which is used to name a file or path in a readable string name. it can be in the format of path.
	 *			In the distributed file system, same key or hash actually stand for a identical file or path in the file system.
	 *		several file information fields which may include but not limited to below information
	 *			file/path permission.
	 *			file/path size in block and size in byte
	 *			file/path created time
	 *			file/path last modified time
	 *			file/path last access time
	 *			file/path opened for read by host/host_process
	 *			file/path opened for write by host/host_process
	 *			maybe I can add more
	*/

class sinode{
	public:
		static const int hash_size = DIGEST_LEN;
	private:
		char m_hash[hash_size];
		unsigned int_32 m_permission;
		unsigned int_32 m_size_in_block;
		unsigned int_32 m_size_in_byte;
		time_t m_create_time;
		time_t m_modified_time;
		time_t m_access_time;
		vector< dest * > m_dests;
		
		
};

#enfif //sinode_h
