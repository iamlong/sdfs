#include "../rtable.h"

#include <string.h>

#include <gtest/gtest.h>

TEST (TESTADDPATH, Add1Path) {
	
	rtable * testRtable = new rtable();
	
	testRtable->addpath("/", "1.1.1.1@30");
	ASSERT_TRUE(testRtable->findpath("/")!=-1);
	delete testRtable;

}
int main(int argc, char **argv) {  
  testing::InitGoogleTest(&argc, argv);  
  return RUN_ALL_TESTS();  
}
