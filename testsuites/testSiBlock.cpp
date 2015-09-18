#include "gtest/gtest.h"
#include "../util/serializer.h"
#include "../fs/siblock.h"
#include <string.h>

using namespace std;

TEST (SIBLOCKTEST, PULLOBJECT) {
	
	siblockref testblockref("/user/slib/abc.txt", 8192);
	
	Serializer a(testblockref.getPersistentSizeInByte()); //create a buffer with 
	
	ASSERT_EQ(8+122, a.getSize());

	siblockref testblockref_next("/user/slib/abc.txt", 8192);

	siblockref testblockref_prev("/user/slib/abc.txt", 8192);

	ASSERT_TRUE(testblockref!=testblockref_next);
	ASSERT_TRUE(testblockref!=testblockref_prev);
	ASSERT_TRUE(testblockref_next!=testblockref_prev);
	
	testblockref.set_prev_block(testblockref_prev.get_hash());
	testblockref.set_next_block(testblockref_next.get_hash());

	ASSERT_TRUE(a.fillObject(&testblockref));

	siblockref testdesref;

	DeSerializer b(a.getFilledBuffer(), a.getSize());

	ASSERT_TRUE(b.pullObject(&testdesref));

	ASSERT_TRUE(testblockref==testdesref);


	
}

int main(int argc, char **argv) {  
  testing::InitGoogleTest(&argc, argv);  
  return RUN_ALL_TESTS();  
}
