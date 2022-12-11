#include <gtest/gtest.h>

#include "net_worker.h"

TEST(NetWorkerTest, SendMessageTest) {
    NetWorker netWorker;
    int err = netWorker.sendMessage("some_message");
    EXPECT_EQ(err, 0);
}

TEST(NetWorkerTest, SendFileNotExistsTest) {
    NetWorker netWorker;
    int err = netWorker.sendFile("./Test/SentFiles/not_exist_file.txt");
    EXPECT_EQ(err, 1);
}

TEST(NetWorkerTest, SendFileImgTest) {
    NetWorker netWorker;
    int err = netWorker.sendFile("./Test/SentFiles/test_640_480.jpg");
    EXPECT_EQ(err, 0);
}

TEST(NetWorkerTest, SendFileTxtTest) {
    NetWorker netWorker;
    int err = netWorker.sendFile("./Test/SentFiles/text.txt");
    EXPECT_EQ(err, 0);
}