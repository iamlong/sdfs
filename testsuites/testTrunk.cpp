#include "../storage/trunk.h"

#include <gtest/gtest.h>


TEST (TRUNKTEST, TestWRITE_PASS) {
	char a[]="abcdefghjklmn\n";
	trunk::max_trunk_size=50;
	ASSERT_TRUE(trunk::write("dummy", "./", (sd_uint8_t*)a, sizeof(a))>0);
}
TEST (TRUNKTEST, TestWRITE_FALSE_PATHERR) {
	char a[]="abcdefghjklmn\n";
	trunk::max_trunk_size=500;
	ASSERT_FALSE(trunk::write("dummy", "./abcdewr", (sd_uint8_t*)a, sizeof(a))>0);
}
TEST (TRUNKTEST, TestWRITE_FALSE_TOOBIG) {
	char a[]="abcdefghjklmndjnciwuehhiejnfkewfewfiheufhih\n";
	trunk::max_trunk_size=10;
	ASSERT_FALSE(trunk::write("dummy", "./", (sd_uint8_t*)a, sizeof(a))>0);
}

TEST (TRUNKTEST, TestREAD_PASS) {
	char a[]="abcdefghjklmn\n";
	trunk::max_trunk_size=20;
	ASSERT_TRUE(trunk::write("dummy", "./", (sd_uint8_t*)a, sizeof(a))>0);
	char b[20];
	memset(b,0, 20);
	ASSERT_TRUE(trunk::read("dummy", "./", (sd_uint8_t*)b, sizeof(b))>0);
	ASSERT_TRUE(strcmp(a, b)==0);
}
int main(int argc, char **argv) {  
  testing::InitGoogleTest(&argc, argv);  
  return RUN_ALL_TESTS();  
}
