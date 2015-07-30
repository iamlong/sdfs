#include "rentry.h"

    /** 
     *  rentry stands for an inode entry for a file or directory in the file system. It actually referencing to a network location of the filenode structure. This filenode structure include the information of  
     */


rentry::rentry(string path)
{
    m_path = path;
    m_hash_size = hash_size;
    utils::hash(path, m_hash);
}

bool rentry::match(const char * comphash)
{
	if(memcmp(m_hash, comphash, DIGEST_LEN)==0)
        return true;
    else
        return false;
        
}

int rentry::refreshdests(const string destsString)
{
    //dest fornamt should be like "ip@port;ip@port"
    //or we can replace ip with hostname like "hostname@port;ip@port"
    cleandests();
    int commpos;
    string tempstr = destsString;
	
	commpos = tempstr.find(';');
	while(commpos!=string::npos){
		adddest(tempstr.substr(0,commpos));
		tempstr = tempstr.substr(commpos+1);
		commpos = tempstr.find(';');
	}
	if(tempstr.find("@")!=string::npos)
		adddest(tempstr);
	
    return m_dests.size();   
}

void rentry::cleandests()
{
    int size = m_dests.size();
    if(size <= 0)
        return;
    
    dest * temp;

    for (int i = 0; i < size; i++)
    {
        temp = m_dests[i];
		delete temp;
    }
    m_dests.clear(); 
}

string rentry::toString()
{
    int size = m_dests.size();
    string str;

    for (int i = 0; i < size; i++)
		if(i != size -1)
			str += m_dests[i]->toString()+';';
		else
			str += m_dests[i]->toString();
        
	return str;
        
}
bool rentry::adddest(const string deststr)
{
	dest * destbuff = new dest(deststr);
	for (int i = 0; i<m_dests.size();i++){
		if(*m_dests[i]==*destbuff){
			delete destbuff;
			return false;
		}

	}
	m_dests.push_back(destbuff);
	return true;
}

bool rentry::removedest(string deststr)
{
	dest tempdest (deststr);
	bool removed = false;
	
	for (int i=0; i<m_dests.size();i++ )
		if(*m_dests[i]==tempdest){
			delete m_dests[i];
			m_dests.erase(m_dests.begin()+i);
			removed=true;
		}
    return removed;
}

vector<dest*> * rentry::getDests(){
	return &m_dests;
}

rentry::~rentry()
{
	cleandests();
}
