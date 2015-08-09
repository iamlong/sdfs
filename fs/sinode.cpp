#include "sinode.h"
#include "../util/utils.h"
#include <malloc.h>

sinode::sinode(string key, sinode_type nodetype ){
	m_base.m_path = key;
	utils::hash(key, m_base.m_hash);
	m_base.m_type = nodetype;
	
}

uint32_t sinode::getSizeInBlock(){
	return m_base.m_size_in_block;
}

uint32_t sinode::getSizeInByte(){
	return m_base.m_size_in_byte;
}

uint32_t sinode::getSiBlockSize(){
	return m_siblocks.size();
}

siblock * sinode::getSiBlock(int index){
	return m_siblocks[index];
}

bool sinode::addSiBlock(siblock * b){
	
	int size = getSiBlockSize();
	
	for (int i = 0; i<size; i++)
		if(*b==*getSiBlock(i))
			return false;
	
	m_siblocks.push_back(b);
}

bool sinode::removeSiBlock(int index){
	
	if(index > (m_siblocks.size()-1) ||index < 0)
		return false;
		
	delete m_siblocks[index];
	
	m_siblocks.erase(m_siblocks.begin()+index);
}

memblock * sinode::toBlob(){
	
	if(m_blob != NULL)
		free(m_blob);
		
	int size = calcsize();
	
	size += sizeof(memblock::size);
	
	m_blob = (memblock *)malloc(size);
	
	m_blob->size = size - sizeof(memblock::size);
	
//	nodebase * temp = m_blob->mem;
	
	memcpy(m_blob->mem, &m_base, sizeof(nodebase));
	
	//now I need to add processes into BLOB

	char * memhead = &m_blob->mem[sizeof(nodebase)];
	
	memhead = pushinprocess(memhead, &m_readrprocess);
	memhead = pushinprocess(memhead, &m_writerprocess);
	//now I need to add SiBlocks information into BLOB
	
	return m_blob;
}

char * sinode::pushinprocess(char * head, vector< rprocess * > * processes){
	
	char * memhead = head;
	
	int size = processes->size();
	memcpy(memhead, &size, sizeof(size));
	memhead += sizeof(size);
	
	for(int i = 0; i <size; i++){
		rprocess * trp= (*processes)[i];
		memcpy(memhead, trp, sizeof(rprocess));
		memhead +=sizeof(rprocess);
	}
	
	return memhead;
}

int sinode::calcsize(){
	int size =0;
	
	size += sizeof(m_base);
	size += sizeof(rprocess)*(m_readrprocess.size() + m_writerprocess.size())+2*sizeof(int);
	//size += m_siblocks.size()*siblock::calcsize();
	
}
