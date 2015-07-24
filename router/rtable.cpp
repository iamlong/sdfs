#include "rtable.h"


/*rtable::rtable(droute * router){
	m_router = router;
}
*/
rtable::rtable(){
	//m_router = router;
}

rtable::~rtable(){
	
}
int rtable::findpath(string path)
{
	char hash[rentry::hash_size]; 
	rentry::hash(path, hash);
	int i;
	int size = m_routeitems.size();
	for(i = 0; i< size;i++)
		if(m_routeitems[i]->match(hash))
			break;
	
	if(i>=size)
		i=-1;

    return i;
}

vector <dest *> * rtable::getItemDests(int i){
	return m_routeitems[i]->getDests();
}

bool rtable::addpath(string path, string destinations)
{
	if(findpath(path)!=-1)
		return false;
	rentry *newitem = new rentry(path);
	newitem->refreshdests(destinations);
	
	m_routeitems.push_back(newitem);
    return true;
}

bool rtable::deletepath(string path)
{
	int i = findpath(path);
	if(i==-1)
		return false;
		
	delete m_routeitems[i];
	m_routeitems.erase(m_routeitems.begin()+i);
	return true;	    
}

bool rtable::refreshpath(string path, string destinations)
{
	int i = findpath(path);
	if(i == -1)
		return false;
	
	rentry * ent = m_routeitems[i];
	ent->refreshdests(destinations);
		
    return true;
}

bool rtable::addpathdest(string path, string destination)
{
	int i = findpath(path);
	if(i == -1)
		return false;
	
	rentry * ent = m_routeitems[i];
	ent->adddest(destination);

    return true;
}

bool rtable::removepathdest(string path, string destination)
{
	int i = findpath(path);
	if(i == -1)
		return false;
	
	rentry * ent = m_routeitems[i];
	ent->removedest(destination);

    return true;
}

