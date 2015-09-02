#include "../include/gtest/gtest.h"
#include "../util/serializer.h"
#include "../fs/blocklist.h"
#include <string.h>

using namespace std;

/*TEST (BLOCKLISTTEST, PULLOBJECT) {
	
	siblockref testblockref("/user/slib/abc.txt", 8192);
	
	//Serializer a(testblockref.getPersistentSizeInByte()); //create a buffer with 
	
	//ASSERT_EQ(8+122, a.getSize());

	siblockref testblockref_next("/user/slib/abc.txt", 8192);

	siblockref testblockref_prev("/user/slib/abc.txt", 8192);

	ASSERT_TRUE(testblockref!=testblockref_next);
	ASSERT_TRUE(testblockref!=testblockref_prev);
	ASSERT_TRUE(testblockref_next!=testblockref_prev);
	
	//testblockref.set_prev_block(testblockref_prev.get_hash());
	//testblockref.set_next_block(testblockref_next.get_hash());

	//ASSERT_TRUE(a.fillObject(&testblockref));

	//siblockref testdesref;

	//DeSerializer b(a.getFilledBuffer(), a.getSize());

	//ASSERT_TRUE(b.pullObject(&testdesref));

	//ASSERT_TRUE(testblockref==testdesref);


	
}*/

TEST (BLOCKLISTTEST, TESTLIST) {
	
	siblockref t1("/user/slib/abc.txt", 8192);
	
	siblockref t2("/user/slib/abc.txt", 8192);

	siblockref t3("/user/slib/abc.txt", 8192);

	ASSERT_TRUE(t1!=t2);
	ASSERT_TRUE(t2!=t3);
	ASSERT_TRUE(t3!=t1);
	
	siblocklist testlist;

	testlist.appendBlock(t1);
	testlist.appendBlock(t2);
	testlist.appendBlock(t3);

	ASSERT_TRUE(testlist.getBlock(0)!=testlist.getBlock(1));
	ASSERT_TRUE(testlist.getBlock(1)!=testlist.getBlock(2));
	ASSERT_TRUE(testlist.getBlock(2)!=testlist.getBlock(0));

	
}

TEST (BLOCKLISTTEST, TESTDELETELIST) {
	
	siblockref t1("/user/slib/abc.txt", 8192);
	
	siblockref t2("/user/slib/abc.txt", 8192);

	siblockref t3("/user/slib/abc.txt", 8192);

	ASSERT_TRUE(t1!=t2);
	ASSERT_TRUE(t2!=t3);
	ASSERT_TRUE(t3!=t1);
	
	siblocklist testlist;

	testlist.appendBlock(t1);
	testlist.appendBlock(t2);
	testlist.appendBlock(t3);

	ASSERT_TRUE(testlist.getBlock(0)!=testlist.getBlock(1));
	ASSERT_TRUE(testlist.getBlock(1)!=testlist.getBlock(2));
	ASSERT_TRUE(testlist.getBlock(2)!=testlist.getBlock(0));

	testlist.deletefrom(1);

	ASSERT_TRUE(testlist.getSize()==1);

	ASSERT_TRUE(testlist.getRemoveList().size()==2);

	
}


int main(int argc, char **argv) {  
  testing::InitGoogleTest(&argc, argv);  
  return RUN_ALL_TESTS();  
}
