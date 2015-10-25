#include "../util/network.h"

#include <gtest/gtest.h>
#include <stdio.h>

TEST (TESTNETWORK,GetLocalIPs) {

	vector<string> ips;
	networkhelper::getLocalips(&ips);
	
	for(int i=0; i<ips.size(); i++){
		printf("ip %d---- %s \n",i,ips[i].c_str());
	}
		
}



int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
