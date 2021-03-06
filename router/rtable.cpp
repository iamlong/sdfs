#include "rtable.h"
#include "../util/utils.h"


/*rtable::rtable(droute * router){
	m_router = router;
}
*/
rtable::rtable(){
	//m_router = router;
}

rtable::~rtable(){
	
}
sd_int32_t rtable::findPath(string path)
{
	char hash[rentity::hash_size]; 
	utils::hash(path, hash);
	int i;
	int size = m_nodeitems.size();
	for(i = 0; i< size;i++)
		if(m_nodeitems[i]->match(hash))
			break;
	
	if(i>=size)
		i=-1;

    return i;
}

vector <dest *> * rtable::getPathItemDests(sd_uint32_t i){
	return m_nodeitems[i]->getDests();
}

rentity * rtable::getPathItem(sd_uint32_t i){
	return m_nodeitems[i];
}
bool rtable::addPath(string path, string destinations)
{
	if(findPath(path)!=-1)
		return false;
	rentity *newitem = new rentity(path);
	newitem->refreshDests(destinations);
	
	m_nodeitems.push_back(newitem);
    return true;
}

bool rtable::deletePath(string path)
{
	int i = findPath(path);
	if(i==-1)
		return false;
		
	delete m_nodeitems[i];
	m_nodeitems.erase(m_nodeitems.begin()+i);
	return true;	    
}

bool rtable::refreshPath(string path, string destinations)
{
	int i = findPath(path);
	if(i == -1)
		return false;
	
	rentity * ent = m_nodeitems[i];
	ent->refreshDests(destinations);
		
    return true;
}

bool rtable::addPathDest(string path, string destination)
{
	int i = findPath(path);
	if(i == -1)
		return false;
	
	rentity * ent = m_nodeitems[i];
	ent->addDest(destination);

    return true;
}

bool rtable::removePathDest(string path, string destination)
{
	int i = findPath(path);
	if(i == -1)
		return false;
	
	rentity * ent = m_nodeitems[i];
	ent->removeDest(destination);

    return true;
}

