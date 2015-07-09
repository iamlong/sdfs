#include "../rentry.h"
#include <string.h>

#include <gtest/gtest.h>

TEST (ReplaceDests, onedest) {
	rentry * testentry = new rentry((unsigned char *)"/abc/dce", 8);
	
	unsigned char one_dest[] = "1.1.1.1@30";
	testentry->replacedests(one_dest, (unsigned int)strlen((char *)one_dest));
	ASSERT_STREQ("1.1.1.1@30;", (const char *)testentry->mergedests());
}

int main(int argc, char **argv) {  
  testing::InitGoogleTest(&argc, argv);  
  return RUN_ALL_TESTS();  
}
