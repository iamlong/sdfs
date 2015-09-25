#include "../storage/storcmdq.h"
#include <gtest/gtest.h>

TEST(TESTCOMMANDQ, PUSHQSUCCESS){
	storage_command_q myq;
	sd_uint8_t a[20] = "anbcdjkwewcew";
	myq.pushtoQ("add", NULL, sizeof(a));
	myq.pushtoQ("delete", NULL, 0);
	ASSERT_TRUE(myq.QSize()==2);

}
TEST(TESTCOMMANDQ, PULLQSUCCESS){
	storage_command_q myq;
	sd_uint8_t a[20] = "anbcdjkwewcew";
	myq.pushtoQ("add", NULL, sizeof(a));
	myq.pushtoQ("delete", NULL, 0);
	ASSERT_TRUE(myq.QSize()==2);

	storage_command ret;
	ret = myq.pullfromQ();
	ASSERT_STREQ(ret.command.c_str(),"add");
	ret = myq.pullfromQ();
	ASSERT_STREQ(ret.command.c_str(),"delete");
	ASSERT_EQ(myq.QSize(),0);

}


int main(int argc, char **argv) {  
  testing::InitGoogleTest(&argc, argv);  
  return RUN_ALL_TESTS();  
}
