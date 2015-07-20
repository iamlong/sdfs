#include "dest.h"

dest::dest(const string str){
	m_deststr = str;
	parse();
}

void dest::parse(){

	int pos = m_deststr.find('@');
	m_desthost = m_deststr.substr(0, pos);
	m_destport = m_deststr.substr(pos+1);
}

string dest::toString(){
	string a = m_desthost+"@"+m_destport;
	return a;
}

bool dest::operator==(const dest & compdest){
	if((m_desthost == compdest.m_desthost)&&(m_desthost==compdest.m_desthost))
		return true;
	else
		return false;
}
