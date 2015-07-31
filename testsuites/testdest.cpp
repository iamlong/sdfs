#include "../router/dest.h"

#include <gtest/gtest.h>


TEST (DestTest, TestEqual) {
	string one_dest = "1.1.1.1@30";
	string two_dest = "1.2.1.1@40";
	dest a(one_dest);
	dest b(one_dest);
	dest c(two_dest);
	ASSERT_TRUE(a==b);
	ASSERT_FALSE(b==c);
}
TEST (DestTest, God_DestStr) {
		
	string one_dest = "1.1.1.1@30";
	dest a (one_dest);
	ASSERT_STREQ(a.toString().c_str(), one_dest.c_str());
}

int main(int argc, char **argv) {  
  testing::InitGoogleTest(&argc, argv);  
  return RUN_ALL_TESTS();  
}
