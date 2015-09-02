#include "blocklist.h"

siblockref siblocklist::getBlock(sd_uint32_t index){
	
	if(index>m_blocklist.size())
		return m_blocklist[m_blocklist.size()];
	else
		return m_blocklist[index];
}

sd_uint32_t siblocklist::getSize(){
	return m_blocklist.size();
}

sd_uint32_t siblocklist::appendBlock(siblockref block){
	
	sd_int32_t size = m_blocklist.size();
	
	if(size!=0){
		block.set_prev_block(m_blocklist[size-1].get_hash());
		m_blocklist[size-1].set_next_block(block.get_hash());
	}
		
	block.set_seqnum(size);
	m_blocklist.push_back(block);
	return m_blocklist.size();
	
}

bool siblocklist::deletefrom(sd_uint32_t index){
	
	if(index > m_blocklist.size())
		return false;
		
	int size_to_delete = m_blocklist.size() - index;
	
	for( int i = size_to_delete; i>0; i--) {
		
		//add removed block into remove list so that
		//we can permenently delete them afterwards
		siblockref back = m_blocklist.back();
		string removeblock;
		removeblock.append(back.get_hash(), DIGEST_LEN);
		m_removeblocklist.push_back(removeblock);
		
		m_blocklist.pop_back();
	};
	
	m_blocklist.back().clean_next_block();
	
	return true;
}

bool siblocklist::emptylist(){
	return deletefrom(0);
}

vector<string> siblocklist::getRemoveList(){
	return m_removeblocklist;
}

