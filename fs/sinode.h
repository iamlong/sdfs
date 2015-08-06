#ifndef sinode_h
#define sinode_h

#include "../router/dest.h"
#include "structures.h"
#include <vector>
#include <string>

using namespace std;

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
	 *			file/path change time
	 *			file/path last modified time
	 *			file/path last access time
	 *			file/path opened for read by host/host_process
	 *			file/path opened for write by host/host_process
	 *			maybe I can add more
	*/

class sinode{
		
	public:
		//get times
		time_t getCreateTime();
		time_t getModifiedTime();
		time_t getAccessTime();
		time_t getChangeTime();
		
		//Permission
		uint32_t getPermission();
		uint32_t getOwnerPermission();
		uint32_t getsetGroupPermission();
		uint32_t getOtherPermission();
		bool setPermission(unisnged int_32 p);
		bool setOwnerPermission(uint32_t p);
		bool setGroupPermission(uint32_t p);
		bool setOtherPermission(uint32_t p);
		
		//size
		unsigned int_32 getSizeInBlock();
		unsigned int_32 getSizeInByte();
		
		//remote process
		vector< rprocess * > getReadProcesses();
		vector< rprocess * > getWriteProcesses();
		bool addReadProcess(string processString);
		bool removeReadProcess(string processString);
		bool addWriteProcess(string processString);
		bool removeWriteProcess(string processString);
		
		//siBlocks
		vector < siblock *> getSiBlocks();
		bool addSiBlock(siblock *);
		bool removeSiBlock(int index);
		
		//Serialize to BLOB and Deserialize from BLOB
		memblock * toBlob();
		fromBlob(memblock *);
				
	private:
		nodeid m_id;
		uint32_t m_permission;
		uint32_t m_size_in_block;
		uint32_t m_size_in_byte;
		time_t m_create_time;
		time_t m_modified_time;
		time_t m_access_time;
		time_t m_change_time;
		vector< rprocess * > m_readrprocess;
		vector< rprocess * > m_writerprocess;
		vector< siblock * > m_siblocks;
		
		
};

#enfif //sinode_h
