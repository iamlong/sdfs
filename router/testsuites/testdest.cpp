#include "../dest.h"

#include <gtest/gtest.h>

TEST (DestTest, God_DestStr) {
		
	string one_dest = "1.1.1.1@30";
	dest a (one_dest);
	ASSERT_STREQ(a.toString().c_str(), one_dest.c_str());
}

int main(int argc, char **argv) {  
  testing::InitGoogleTest(&argc, argv);  
  return RUN_ALL_TESTS();  
}
