#include "sinode.h"
#include "../util/utils.h"
#include <malloc.h>
#include "../util/sig.h"


sinode::sinode(string key, sinode_type nodetype ){
	
	set_sig(SNODE_START_SIG, SNODE_END_SIG);

	m_base.m_path = key;
	utils::hash(key, (char *)m_base.m_hash);
	m_base.m_type = nodetype;
	
}

sd_uint32_t sinode::getSizeInBlock(){
	return m_base.m_size_in_block;
}

sd_uint32_t sinode::getSizeInByte(){
	return m_base.m_size_in_byte;
}

sd_uint32_t sinode::getSiBlockSize(){
	return m_siblockrefs.size();
}

siblockref * sinode::getSiBlock(sd_uint32_t index){
	return m_siblockrefs[index];
}

bool sinode::addSiBlock(siblockref * b){
	
	sd_uint32_t size = getSiBlockSize();
	
	if(size == 0)
		memcpy(m_base.m_start_block, b->get_hash(), sizeof(m_base.m_start_block));
	for (int i = 0; i<size; i++)
		if(*b==*getSiBlock(i))
			return false;
	
	m_siblockrefs.push_back(b);
}

bool sinode::removeSiBlock(sd_uint32_t index){
	
	if(index > (m_siblockrefs.size()-1) ||index < 0)
		return false;
		
	delete m_siblockrefs[index];
	
	m_siblockrefs.erase(m_siblockrefs.begin()+index);
}

sd_uint32_t sinode::getPersistentSizeInByte(){
	
	m_persistent_size =0;
	m_persistent_size += sizeof(m_base); //siblock membersize

	sd_uint32_t blocknum = m_siblockrefs.size();
	for (sd_uint32_t i =0; i<blocknum; i++)
		m_persistent_size +=m_siblockrefs[i]->getPersistentSizeInByte(); //all siblock membersize
	
	m_persistent_size +=getISerializeSize(); //get base size of ISerialize
	
	m_persistent_size +=sizeof(sd_uint32_t); //place to record how many siblocks
	
	return m_persistent_size;
}

//memblock * sinode::toBlob(){
//	
//	if(m_blob != NULL)
//		free(m_blob);
//		
//	int size = calcsize();
//	
//	size += sizeof(memblock::size);
//	
//	m_blob = (memblock *)malloc(size);
//	
//	m_blob->size = size - sizeof(memblock::size);
//	
////	nodebase * temp = m_blob->mem;
//	
//	memcpy(m_blob->mem, &m_base, sizeof(nodebase));
//	
//	//now I need to add processes into BLOB
//
//	char * memhead = &m_blob->mem[sizeof(nodebase)];
//	
//	memhead = pushinprocess(memhead, &m_readrprocess);
//	memhead = pushinprocess(memhead, &m_writerprocess);
//	//now I need to add SiBlocks information into BLOB
//	
//	return m_blob;
//}
//
//char * sinode::pushinprocess(char * head, vector< rprocess * > * processes){
//	
//	char * memhead = head;
//	
//	int size = processes->size();
//	memcpy(memhead, &size, sizeof(size));
//	memhead += sizeof(size);
//	
//	for(int i = 0; i <size; i++){
//		rprocess * trp= (*processes)[i];
//		memcpy(memhead, trp, sizeof(rprocess));
//		memhead +=sizeof(rprocess);
//	}
//	
//	return memhead;
//}

//int sinode::calcsize(){
//	int size =0;
//	
//	size += sizeof(m_base);
//	size += sizeof(rprocess)*(m_readrprocess.size() + m_writerprocess.size())+2*sizeof(int);
//	//size += m_siblocks.size()*siblock::calcsize();
//	
//}
