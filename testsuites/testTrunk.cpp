#include "../storage/trunk.h"

#include <gtest/gtest.h>


TEST (TRUNKTEST, TestWRITE_PASS) {
	trunk wtrunk("dummy", "./", 20);
	char a[]="abcdefghjklmn\n";
	ASSERT_TRUE(wtrunk.write((sd_uint8_t*)a, sizeof(a)));
}
TEST (TRUNKTEST, TestWRITE_FALSE_PATHERR) {
	trunk wtrunk("dummy", "./cde", 20);
	char a[]="abcdefghjklmn\n";
	ASSERT_FALSE(wtrunk.write((sd_uint8_t*)a, sizeof(a)));
}
TEST (TRUNKTEST, TestWRITE_FALSE_TOOBIG) {
	trunk wtrunk("dummy", "./cde", 20);
	char a[]="abcdefghjklmndjnciwuehhiejnfkewfewfiheufhih\n";
	ASSERT_FALSE(wtrunk.write((sd_uint8_t*)a, sizeof(a)));
}

TEST (TRUNKTEST, TestREAD_PASS) {
	trunk wtrunk("dummy", "./", 20);
	char a[]="abcdefghjklmn\n";
	ASSERT_TRUE(wtrunk.write((sd_uint8_t*)a, sizeof(a)));
	char b[20];
	memset(b,0, 20);
	trunk rtrunk("abc", "./", 20);
	ASSERT_TRUE(rtrunk.read((sd_uint8_t*)b, sizeof(b)));
	ASSERT_TRUE(strcmp(a, b)==0);
}
int main(int argc, char **argv) {  
  testing::InitGoogleTest(&argc, argv);  
  return RUN_ALL_TESTS();  
}
