#include "../router/rentry.h"
#include <string.h>

#include <gtest/gtest.h>

TEST (addDests, AddOneDest) {
	string path = "/abc/dce";
	rentry testentry(path);
	
	string one_dest = "1.1.1.1@30";
	testentry.addDest(one_dest);
	ASSERT_STREQ("1.1.1.1@30", testentry.toString().c_str());

}

TEST (addDests, Add10Dest) {
	string path = "/abc/dce";
	rentry testentry(path);
	
	string dests[10] = {"1.1.1.1@30", \
	"2.2.2.2@30", \
	"3.3.3.3@30", \
	"4.4.4.4@30", \
	"5.5.5.5@30", \
	"6.6.6.6@30", \
	"7.7.7.7@30", \
	"8.8.8.8@30", \
	"9.9.9.9@30", \
	"10.10.10.10@30"};

	string fulldests;
		
	for(int i = 0; i<10; i++){
		testentry.addDest(dests[i]);
		fulldests += dests[i];
		if( i<9 )
			fulldests +=';';
	}
	ASSERT_STREQ(fulldests.c_str(), testentry.toString().c_str());
}

TEST (Refreshdests, onedest) {
	string path = "/abc/dce";
	rentry testentry(path);
	
	string one_dest = "1.1.1.1@30";
	int i = testentry.refreshDests(one_dest);
	ASSERT_STREQ("1.1.1.1@30", testentry.toString().c_str());
	ASSERT_EQ(i, 1);
}

TEST (refreshDests, Twodests) {
	string path = "/abc/dce";
	rentry testentry(path);
	
	string two_dest_1 = "1.1.1.1@30;2.2.2.2@40;";
	int i = testentry.refreshDests(two_dest_1);
	ASSERT_STREQ("1.1.1.1@30;2.2.2.2@40", testentry.toString().c_str());
	ASSERT_EQ(i, 2);
	
	string two_dest_2 = "1.1.1.1@30;2.2.2.2@40";
	i = testentry.refreshDests(two_dest_2);
	ASSERT_STREQ("1.1.1.1@30;2.2.2.2@40", testentry.toString().c_str());
	ASSERT_EQ(i, 2);
}

TEST (RemoveDest, RemoveOneDest) {
	string path = "/abc/dce";
	rentry testentry(path);
	
	string two_dest_1 = "1.1.1.1@30;2.2.2.2@40;";
	testentry.refreshDests(two_dest_1);
	ASSERT_STREQ("1.1.1.1@30;2.2.2.2@40", testentry.toString().c_str());
	ASSERT_TRUE(testentry.removeDest("2.2.2.2@40"));
	ASSERT_STREQ("1.1.1.1@30", testentry.toString().c_str());
}

TEST (removeDest, Remove2Dest) {
	string path = "/abc/dce";
	rentry testentry(path);
	
	string dests[10] = {"1.1.1.1@30", \
		"2.2.2.2@30", \
		"3.3.3.3@30", \
		"4.4.4.4@30", \
		"5.5.5.5@30", \
		"6.6.6.6@30", \
		"7.7.7.7@30", \
		"8.8.8.8@30", \
		"9.9.9.9@30", \
	"10.10.10.10@30"};
	
	string fulldests;
	
	for(int i = 0; i<10; i++){
		testentry.addDest(dests[i]);
		if(i!=4&&i!=7)
			fulldests += dests[i];
		if( i<9&&(i!=4&&i!=7))
			fulldests +=';';
	}
	ASSERT_TRUE(testentry.removeDest(dests[4]));
	ASSERT_TRUE(testentry.removeDest(dests[7]));
		
	ASSERT_STREQ(fulldests.c_str(), testentry.toString().c_str());

}
int main(int argc, char **argv) {  
  testing::InitGoogleTest(&argc, argv);  
  return RUN_ALL_TESTS();  
}
