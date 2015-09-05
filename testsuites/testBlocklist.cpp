#include "gtest/gtest.h"
#include "../util/serializer.h"
#include "../fs/blocklist.h"
#include <string.h>
#include <ostream>

using namespace std;


TEST (BLOCKLISTTEST, TESTSerializeDeSerialize) {
	
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
	
	Serializer a(testlist.getPersistentSizeInByte());

	ASSERT_TRUE(a.fillObject(&testlist));

	DeSerializer b(a.getFilledBuffer(), a.getSize());
	
	siblocklist testp;

	ASSERT_TRUE(b.pullObject(&testp));

	ASSERT_TRUE(testlist.getBlock(0)==testp.getBlock(0));
	ASSERT_TRUE(testlist.getBlock(1)==testp.getBlock(1));
	ASSERT_TRUE(testlist.getBlock(2)==testp.getBlock(2));

}

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

	siblockref tm = testlist.getBlock(1);

	cout<<"original seq_num:"<<tm.get_seqnum()<<"\n";

	tm.set_seqnum(34);
	
	cout<<"modified seq_num:"<<tm.get_seqnum()<<"\n";

	cout<<"In BlockList seq_num:"<<testlist.getBlock(1).get_seqnum()<<"\n";
	
	ASSERT_TRUE(tm!=testlist.getBlock(1));

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
