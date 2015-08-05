#include "../router/rtable.h"

#include <string.h>

#include <gtest/gtest.h>

TEST (TESTaddPath, Add1Path) {
	
	rtable * testRtable = new rtable();
	rentity *entity;
	int destindex;
	
	testRtable->addPath("/", "1.1.1.1@30");
	
	destindex = testRtable->findPath("/");
	entity = testRtable->getPathItem(destindex);
	ASSERT_TRUE(destindex!=-1);
	ASSERT_STREQ("1.1.1.1@30", entity->toString().c_str());
	
	delete testRtable;

}

TEST (TESTaddPath, Add2Path) {
	
	rtable * testRtable = new rtable();
	rentity *entity;
	int destindex;
	
	testRtable->addPath("/", "1.1.1.1@30");
	testRtable->addPath("/abc", "2.1.1.1@30");
	
	destindex = testRtable->findPath("/abc");
	ASSERT_TRUE(destindex!=-1);
	entity = testRtable->getPathItem(destindex);
	ASSERT_STREQ("2.1.1.1@30", entity->toString().c_str());
	
	
	destindex = testRtable->findPath("/");
	ASSERT_TRUE(destindex!=-1);
	entity = testRtable->getPathItem(destindex);
	ASSERT_STREQ("1.1.1.1@30", entity->toString().c_str());
	
	delete testRtable;

}

TEST (TESTDELETEPATH, Delete1Path) {
	
	rtable * testRtable = new rtable();
	rentity *entity;
	int destindex;
	
	testRtable->addPath("/", "1.1.1.1@30");
	testRtable->addPath("/abc", "2.1.1.1@30");
	
	destindex = testRtable->findPath("/abc");
	ASSERT_TRUE(destindex!=-1);
	entity = testRtable->getPathItem(destindex);
	ASSERT_STREQ("2.1.1.1@30", entity->toString().c_str());
	
	
	destindex = testRtable->findPath("/");
	ASSERT_TRUE(testRtable->findPath("/")!=-1);
	entity = testRtable->getPathItem(destindex);
	ASSERT_STREQ("1.1.1.1@30", entity->toString().c_str());
		
	testRtable->deletePath("/abc");
	destindex = testRtable->findPath("/abc");
	ASSERT_TRUE(destindex==-1);
	
	
	delete testRtable;
}


TEST (TESTRefreshPath, Refresh) {
	
	rtable * testRtable = new rtable();
	rentity *entity;
	int destindex;
	
	testRtable->addPath("/", "1.1.1.1@30");
	testRtable->addPath("/abc", "2.1.1.1@30");
	
	destindex = testRtable->findPath("/abc");
	ASSERT_TRUE(destindex!=-1);
	entity = testRtable->getPathItem(destindex);
	ASSERT_STREQ("2.1.1.1@30", entity->toString().c_str());
	

	
	testRtable->refreshPath("/", "1.2.3.4@32");
	destindex = testRtable->findPath("/");
	ASSERT_TRUE(destindex!=-1);
	entity = testRtable->getPathItem(destindex);
	ASSERT_STREQ("1.2.3.4@32", entity->toString().c_str());
	
	delete testRtable;
}

TEST (TESTaddPathDest, addPathDest) {
	
	rtable * testRtable = new rtable();
	rentity *entity;
	int destindex;
	
	testRtable->addPath("/", "1.1.1.1@30");
	
	destindex = testRtable->addPathDest("/", "2.0.1.1@40");
	destindex = testRtable->findPath("/");
	ASSERT_TRUE(destindex!=-1);
	entity = testRtable->getPathItem(destindex);
	ASSERT_STREQ("1.1.1.1@30;2.0.1.1@40", entity->toString().c_str());
	
	delete testRtable;
}

TEST (TESTREMOVEPathDest, RemovePathDest) {
	
	rtable * testRtable = new rtable();
	rentity *entity;
	int destindex;
	
	testRtable->addPath("/", "1.1.1.1@30;2.2.2.2@40");
	
	destindex = testRtable->removePathDest("/", "1.1.1.1@30");
	destindex = testRtable->findPath("/");
	ASSERT_TRUE(destindex!=-1);
	entity = testRtable->getPathItem(destindex);
	ASSERT_STREQ("2.2.2.2@40", entity->toString().c_str());
	
	delete testRtable;
}

int main(int argc, char **argv) {  
  testing::InitGoogleTest(&argc, argv);  
  return RUN_ALL_TESTS();  
}
