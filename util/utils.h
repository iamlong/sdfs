#ifndef UTILS_H
#define UTILS_H

#include "../sha1/sha1.h"
#include <string>
using namespace std;

class utils {
	public:
		static void hash(const string path, char * hashbuff);
};
#endif
