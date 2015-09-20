#include "../storage/trunk.h"

#include <gtest/gtest.h>


TEST (TRUNKTEST, TestWRITE_PASS) {
	trunk wtrunk("abc", "./", 20);
	char a[]="abcdefghjklmn\n";
	ASSERT_TRUE(wtrunk.write((sd_uint8_t*)a, sizeof(a)));
}
TEST (TRUNKTEST, TestWRITE_FALSE_PATHERR) {
	trunk wtrunk("abc", "./cde", 20);
	char a[]="abcdefghjklmn\n";
	ASSERT_FALSE(wtrunk.write((sd_uint8_t*)a, sizeof(a)));
}
TEST (TRUNKTEST, TestWRITE_FALSE_TOOBIG) {
	trunk wtrunk("abc", "./cde", 20);
	char a[]="abcdefghjklmndjnciwuehhiejnfkewfewfiheufhih\n";
	ASSERT_FALSE(wtrunk.write((sd_uint8_t*)a, sizeof(a)));
}

TEST (TRUNKTEST, TestREAD_PASS) {
	trunk wtrunk("abc", "./", 20);
	char a[20];
	ASSERT_TRUE(wtrunk.read((sd_uint8_t*)a, sizeof(a)));
}
int main(int argc, char **argv) {  
  testing::InitGoogleTest(&argc, argv);  
  return RUN_ALL_TESTS();  
}
