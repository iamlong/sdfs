#ifndef dest_h
#define dest_h

#include <string>

using namespace std;

class dest {
	
	private:
		string m_deststr;
		string m_desthost;
		string m_destport;
		void parse();
	
	public:
		dest(const string str);
		string toString();
		bool operator==(const dest& compdest);
		
};
#endif
