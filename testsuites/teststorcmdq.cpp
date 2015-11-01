#include "../storage/storcmdq.h"
#include <gtest/gtest.h>

TEST(TESTCOMMANDQ, PUSHQSUCCESS){
	storage_command_q myq;
	sd_uint8_t a[20] = "anbcdjkwewcew";
    storage_command cmd1(1024*4);
    storage_command cmd2(1024*4);
    cmd1.CreateCommand("1.txt", a, sizeof(a));
    cmd1.DeleteCommand("1.txt");

	myq.pushtoQ(&cmd1);
	myq.pushtoQ(&cmd2);
	ASSERT_TRUE(myq.QSize()==2);

}
TEST(TESTCOMMANDQ, PULLQSUCCESS){
	storage_command_q myq;
	sd_uint8_t a[20] = "anbcdjkwewcew";
    storage_command cmd1(1024*4);
    storage_command cmd2(1024*4);
    cmd1.CreateCommand("1.txt", a, sizeof(a));
    cmd2.DeleteCommand("1.txt");

	myq.pushtoQ(&cmd1);
	myq.pushtoQ(&cmd2);
	ASSERT_TRUE(myq.QSize()==2);

	storage_command * ret;
	ret = myq.pullfromQ();
	ASSERT_STREQ(ret->getCommand().c_str(),"Create");
	ret = myq.pullfromQ();
	ASSERT_STREQ(ret->getCommand().c_str(),"Delete");
	ASSERT_EQ(myq.QSize(),0);

}


int main(int argc, char **argv) {  
  testing::InitGoogleTest(&argc, argv);  
  return RUN_ALL_TESTS();  
}
