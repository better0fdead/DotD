#include <gtest/gtest.h>
#include "Server.hpp"
#include "ConnectingState.hpp"
#include "ConnectingPeople.hpp"



TEST(IP_test, IP_test1){
    string IP = "127.0.0.2:49152";
    string FriendIP = waitingPeople()
EXPECT_STREQ(IP,FriendIP);

}

TEST(resiveData_test, resiveData_test1){

}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}