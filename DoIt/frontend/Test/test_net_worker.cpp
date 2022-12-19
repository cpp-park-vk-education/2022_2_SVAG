#include <gtest/gtest.h>

#include "net_manager.h"

TEST(NetWorkerTest, SendMessageTest) {
    NetManager netManager;
    int err = 0;
    netManager.sendMessage("some_message", err);
    EXPECT_EQ(err, 0);
}

TEST(NetWorkerTest, SendFileNotExistsTest) {
    NetManager netManager;
    int err = 0;
    netManager.sendFile("./Test/SentFiles/not_exist_file.txt");
    EXPECT_EQ(err, 1);
}

TEST(NetWorkerTest, SendFileImgTest) {
    NetManager netManager;
    int err = 0;
    netManager.sendFile("./Test/SentFiles/test_640_480.jpg");
    EXPECT_EQ(err, 0);
}

TEST(NetWorkerTest, SendFileTxtTest) {
    NetManager netManager;
    int err = 0;
    netManager.sendFile("./Test/SentFiles/text.txt");
    EXPECT_EQ(err, 0);
}
