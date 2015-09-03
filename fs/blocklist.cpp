#include "blocklist.h"

siblocklist::siblocklist(){
	set_sig(SIBLKLIST_START_SIG, SIBLKLIST_END_SIG);
}
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

sd_uint32_t siblocklist::getPersistentSizeInByte(){
	
	m_persistent_size = getISerializeSize();
	
	m_persistent_size += sizeof(sd_uint32_t); //add size of blocklist into BLOB;
	size_t blocksize = m_blocklist.size();

	for(size_t i=0; i<blocksize;i++)
		m_persistent_size += (m_blocklist[i]).getPersistentSizeInByte();
	
	size_t removesize = m_removeblocklist.size();
	
	m_persistent_size += sizeof(sd_uint32_t); //add size of removeblocklist;
	
	for(size_t i=0; i<removesize;i++)
		m_persistent_size +=calcStringSize(m_removeblocklist[i]); //saving strings 
		
	return m_persistent_size;
}


bool siblocklist::Serialize(Serializer * inSerializer){
	
	if(inSerializer->getLeftSize()<getPersistentSizeInByte())
		return false;
	
	inSerializer->fillBytes((sd_uint8_t *)m_start_sig, sizeof(m_start_sig));
	
	inSerializer->fillBytes((sd_uint8_t *)&m_persistent_size, sizeof(m_persistent_size));
	
	sd_uint32_t listsize = m_blocklist.size();
	
	inSerializer->fillBytes((sd_uint8_t *)&listsize, sizeof(listsize));
	
	for(sd_uint32_t i=0; i<listsize; i++)
		inSerializer->fillObject(&m_blocklist[i]);
	
	listsize = m_removeblocklist.size();
	inSerializer->fillBytes((sd_uint8_t *)&listsize, sizeof(listsize)); //save how many string
	for(sd_uint32_t i=0; i<listsize; i++)
		inSerializer->fillString(m_removeblocklist[i]); //fill string into BLOB;
	
	inSerializer->fillBytes((sd_uint8_t *)m_end_sig, sizeof(m_end_sig));
	
	return true;
}

bool siblocklist::DeSerialize(DeSerializer * inDeSerializer){
	
	if(checkBuffer(inDeSerializer)!=true)
		return false;
	
	sd_uint32_t listsize;
	
	inDeSerializer->pullBytes((sd_uint8_t *)&listsize, sizeof(listsize));
	
	for(sd_uint32_t i=0; i<listsize; i++){
		siblockref blk;
		if(!inDeSerializer->pullObject(&blk))
			return false;
		m_blocklist.push_back(blk);
	}
	
	inDeSerializer->pullBytes((sd_uint8_t *)&listsize, sizeof(listsize));
	
	for(sd_uint32_t i=0; i<listsize; i++){
		string str;
		if(!inDeSerializer->pullString(&str))
			return false;
		m_removeblocklist.push_back(str);
	}
	
	inDeSerializer->pullBytes((sd_uint8_t*)m_end_sig, sizeof(m_end_sig));
	return true;
}
