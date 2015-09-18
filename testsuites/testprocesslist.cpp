#include "../fs/processlist.h"

#include <gtest/gtest.h>
#include <stdio.h>

TEST (TESTPROCESSLIST,AddProcess) {

        processlist t1;
		
		t1.addProcess("host1", 1231);
		t1.addProcess("host2", 3124);
        Serializer a(t1.getPersistentSizeInByte()); //create a buffer with
		std:cout<<"Persistent Size "<<a.getSize()<<"\n";
        ASSERT_EQ(t1.getPersistentSizeInByte(), a.getSize());

        ASSERT_TRUE(t1.findProcessIndex("host1", 1231)>=0);

		ASSERT_TRUE(t1.findProcessIndex("host2", 3124)>=0);

		ASSERT_FALSE(t1.findProcessIndex("host2", 3414)>=0);


}

TEST (TESTPROCESSLIST,removeProcess) {

        processlist t1;
		
		t1.addProcess("host1", 1231);
		t1.addProcess("host2", 3124);
        Serializer a(t1.getPersistentSizeInByte()); //create a buffer with
		std:cout<<"Persistent Size "<<a.getSize()<<"\n";
        ASSERT_EQ(t1.getPersistentSizeInByte(), a.getSize());

        ASSERT_TRUE(t1.findProcessIndex("host1", 1231)>=0);

		ASSERT_TRUE(t1.findProcessIndex("host2", 3124)>=0);

		ASSERT_TRUE(t1.removeProcess("host1", 1231));

		ASSERT_FALSE(t1.findProcessIndex("host1", 1231)>=0);

		ASSERT_FALSE(t1.findProcessIndex("host2", 3414)>=0);


}

TEST (TESTPROCESSLIST,SerializeDeserialize) {

        processlist t1;
		
		t1.addProcess("host1", 1231);
		t1.addProcess("host2", 3124);
        Serializer a(t1.getPersistentSizeInByte()); //create a buffer with
		std:cout<<"Persistent Size "<<a.getSize()<<"\n";
        ASSERT_EQ(t1.getPersistentSizeInByte(), a.getSize());

        ASSERT_TRUE(t1.findProcessIndex("host1", 1231)>=0);

		ASSERT_TRUE(t1.findProcessIndex("host2", 3124)>=0);

		ASSERT_TRUE(a.fillObject(&t1));

		processlist t2;
		
		DeSerializer b (a.getFilledBuffer(), a.getSize());
		ASSERT_TRUE(b.pullObject(&t2));

        ASSERT_TRUE(t2.findProcessIndex("host1", 1231)>=0);

		ASSERT_TRUE(t2.findProcessIndex("host2", 3124)>=0);




}



int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

