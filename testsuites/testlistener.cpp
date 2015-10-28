/*************************************************************************
	> File Name: testsuites/testlistener.cpp
	> Author: 
	> Mail: 
	> Created Time: Wed, Oct 28, 2015 12:39:38 PM
 ************************************************************************/

#include<iostream>
using namespace std;


#include <gtest/gtest.h>
#include <stdio.h>
#include "../storage/storlistener.h"
#include "../storage/storcmdq.h"

TEST (TESTLISTENER,STARTSERVICE) {

    storage_command_q cmdq;
    string a = "127.0.03.1";
    storage_listener listener(cmd_push, &cmdq, a,1234);
    if(listener.start())
        listener.getThread()->join();
		
    


}




int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

