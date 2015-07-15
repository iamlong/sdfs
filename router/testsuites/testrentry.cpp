#include "../rentry.h"
#include <string.h>

#include <gtest/gtest.h>

TEST (ReplaceDests, onedest) {
	rentry * testentry = new rentry((unsigned char *)"/abc/dce", 8);
	
	unsigned char one_dest[] = "1.1.1.1@30";
	testentry->replacedests(one_dest, (unsigned int)strlen((char *)one_dest));
	ASSERT_STREQ("1.1.1.1@30;", (const char *)testentry->printdests());
	testentry->cleandests();
	delete testentry;
}

TEST (ReplaceDests, 2dests) {
	rentry * testentry = new rentry((unsigned char *)"/abc/dce", 8);
	
	unsigned char two_dest_1[] = "1.1.1.1@30;2.2.2.2@40;";
	testentry->replacedests(two_dest_1, (unsigned int)strlen((char *)two_dest_1));
	ASSERT_STREQ("1.1.1.1@30;2.2.2.2@40;", (const char *)testentry->printdests());
	
	unsigned char two_dest_2[] = "1.1.1.1@30;2.2.2.2@40";
	testentry->replacedests(two_dest_2, (unsigned int)strlen((char *)two_dest_2));
	ASSERT_STREQ("1.1.1.1@30;2.2.2.2@40;", (const char *)testentry->printdests());
	testentry->cleandests();
	delete testentry;
}

int main(int argc, char **argv) {  
  testing::InitGoogleTest(&argc, argv);  
  return RUN_ALL_TESTS();  
}
