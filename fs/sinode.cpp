#include "sinode.h"
#include "../util/utils.h"

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

int sinode::calcsize(){
	int size =0;
	
	size += sizeof(m_base);
	size += sizeof(rprocess)*(m_readrprocess.size() + m_writerprocess.size());
	size += m_siblocks.size()*siblock::calcsize();
	

}
