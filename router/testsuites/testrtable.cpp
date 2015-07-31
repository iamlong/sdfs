#include "../rtable.h"

#include <string.h>

#include <gtest/gtest.h>

TEST (TESTADDPATH, Add1Path) {
	
	rtable * testRtable = new rtable();
	rentry *entry;
	int destindex;
	
	testRtable->addpath("/", "1.1.1.1@30");
	
	destindex = testRtable->findpath("/");
	entry = testRtable->getItem(destindex);
	ASSERT_STREQ("1.1.1.1@30", entry->toString().c_str());
	ASSERT_TRUE(testRtable->findpath("/")!=-1);
	delete testRtable;

}

TEST (TESTADDPATH, Add2Path) {
	
	rtable * testRtable = new rtable();
	rentry *entry;
	int destindex;
	
	testRtable->addpath("/", "1.1.1.1@30");
	testRtable->addpath("/abc", "2.1.1.1@30");
	
	destindex = testRtable->findpath("/abc");
	entry = testRtable->getItem(destindex);
	ASSERT_STREQ("2.1.1.1@30", entry->toString().c_str());
	ASSERT_TRUE(destindex!=-1);
	
	destindex = testRtable->findpath("/");
	entry = testRtable->getItem(destindex);
	ASSERT_STREQ("1.1.1.1@30", entry->toString().c_str());
	ASSERT_TRUE(testRtable->findpath("/")!=-1);
	delete testRtable;

}

int main(int argc, char **argv) {  
  testing::InitGoogleTest(&argc, argv);  
  return RUN_ALL_TESTS();  
}
