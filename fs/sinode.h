#ifndef sinode_h
#define sinode_h

#include "../router/dest.h"
#include "structures.h"
#include "../util/stdtype.h"
#include "siblock.h"
#include <vector>
#include <string>
#include "../util/serialize.h"
#include "processlist.h"

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

class sinode: public ISerialize{
		
	public:
		
		sinode(string key, sinode_type nodetype);
		
		//get times
//		time_t getCreateTime();
//		time_t getModifiedTime();
//		time_t getAccessTime();
//		time_t getChangeTime();
		
		//Permission
//		uint32_t getPermission();
//		uint32_t getOwnerPermission();
//		uint32_t getsetGroupPermission();
//		uint32_t getOtherPermission();
//		bool setPermission(unisnged int_32 p);
//		bool setOwnerPermission(uint32_t p);
//		bool setGroupPermission(uint32_t p);
//		bool setOtherPermission(uint32_t p);
		
		//size
		uint32_t getSizeInBlock();
		uint32_t getSizeInByte();
		
		//remote process
//		vector< rprocess * > getReadProcesses();
//		vector< rprocess * > getWriteProcesses();
//		bool addReadProcess(string processString);
//		bool removeReadProcess(string processString);
//		bool addWriteProcess(string processString);
//		bool removeWriteProcess(string processString);
		
		//siBlocks
		uint32_t getSiBlockSize();
		siblockref * getSiBlock(int index);
		bool addSiBlock(siblockref *);
		bool removeSiBlock(int index);
		
		//Serialization and DeSerialization
		int getPersistentSizeInByte();
		bool Serialize(Serializer * inSerializer);
		bool DeSerialize(DeSerializer * inDeSerializer);
		
	private:
		nodebase m_base;
		processlist m_readrprocess;
		processlist m_writerprocess;
		vector<siblockref *> m_siblockrefs;
		
			
};

#endif //sinode_h
