// Copyright 2020 Your Name <your_email>

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "Project.hpp"
#include <memory>

TEST(Example, EmptyTest) {
    EXPECT_TRUE(true);
}

TEST(PageContainer, Load_input_stream) {
  PageContainer page;
  StatSender stat (page);
  UsedMemory memory(page);
  std::stringstream io;
  io << "0 name 10\n1 name 3\n2 name 4\n3 name 3\n4 name 10\n5 name 7\n"
          "6 name 4\n7 name 4";
  float threshold = 5;
  EXPECT_THROW(page.Load(io, threshold), std::runtime_error);
  EXPECT_EQ(memory.used(), 0);
}

TEST(PageContainer, Load_already_seen) {
  PageContainer page;
  StatSender stat (page);
  UsedMemory memory(page);
  std::stringstream io;
  io << "0 name 10\n1 name 3\n2 name 4\n3 name 3\n4 name 10\n5 name 7\n"
        "6 name 4\n7 name 4\n8 name 4\n9 name 6\n 3 name 2";
  float threshold = 5;
  EXPECT_THROW(page.Load(io, threshold), std::runtime_error);
  EXPECT_EQ(memory.used(), 165);
}

TEST(PageContainer, Load_oops) {
  PageContainer page ;
  StatSender stat (page);
  UsedMemory memory(page);
  std::stringstream io;
  io << "0 name 10\n1 name 3\n2 name 4\n3 name 3\n4 name 10\n5 name 7\n"
        "6 name 4\n7 name 4\n8 name 4\n9 name 6\n 10 name 2";
  float threshold = 5;
  EXPECT_THROW(page.Load(io, threshold), std::runtime_error);
  EXPECT_EQ(memory.used(), 165);
}

class Mock_StatSender : public StatSender {
 public:

  Mock_StatSender(PageContainer& page) : StatSender(page){
  }
  MOCK_METHOD2(AsyncSend, void(const std::vector<Item>&,
                   std::string_view));
};

TEST(AsyncSend, Load) {
  PageContainer page;
  //StatSender stat (page);
  UsedMemory memory(page);
  std::stringstream io1, io2;
  io1 << "0 name 10\n1 name 5\n2 name 4\n3 name 7\n4 name 10\n5 name 7\n"
        "6 name 4\n7 name 4\n8 name 3\n9 name 6\n10 name 2\n11 name 5";
  float threshold = 0.1;

  Mock_StatSender _mock(page);

  EXPECT_CALL(_mock, AsyncSend).Times(2);

  page.Load(io1, threshold);
  io2 << "0 name 5\n1 name2 5\n2 name 1\n3 name 7\n4 name 10\n5 name 7\n"
         "6 name 4\n7 name 4\n8 name4 5\n9 name 6\n10 name 2\n11 name 5";
  threshold = 0.2;
  page.Load(io2, threshold);
}

TEST(AsyncSend, Skip) {
  PageContainer page;
  //StatSender stat (page);
  UsedMemory memory(page);
  std::stringstream io;
  io << "0 name 10\n1 name 5\n2 name 4\n3 name 7\n4 name 10\n5 name 7\n"
        "6 name 4\n7 name 4\n8 name 3\n9 name 6\n10 name 2\n11 name 5";
  float threshold = 2;

  Mock_StatSender _mock(page);
  EXPECT_CALL(_mock, AsyncSend).Times(5);
  page.Load(io, threshold);
  threshold = 3;
  page.Reload(threshold);
}

TEST(Memory, Use) {
  PageContainer page;
  StatSender stat (page);
  UsedMemory memory(page);

  std::stringstream io;
  io << "0 name 10\n1 name 3\n2 name 4\n3 name 3\n4 name 10\n5 name 7\n"
        "6 name 4\n7 name 4\n8 name 3\n9 name 6\n10 name 2\n11 name 5";
  float threshold = 0.1;
  page.Load(io, threshold);
  EXPECT_EQ(memory.used(), 588);
}

TEST(Histogram, Test) {
  PageContainer page;
  Histogram hist (page);
  StatSender stat (page);
  UsedMemory memory(page);

  std::stringstream io;
  io << "0 name 10\n1 name 10\n2 name 10\n3 name 10\n4 name 10\n5 name 10\n"
        "6 name 10\n7 name 10\n8 name 3\n9 name 10\n10 name 10\n11 name 10\n12 name 1";
  float threshold = 5;
  page.Load(io, threshold);
  EXPECT_EQ(hist.GetAvg(), 10);
  EXPECT_EQ(hist.GetCount(), 2);
}

/*TEST(Ifstream, Close) {
  PageContainer page;
  Histogram hist (page);
  StatSender stat (page);
  UsedMemory memory(page);

  std::string filename = "data.txt";
  std::ifstream in(filename);
  in.close();
  float threshold = 2;
  EXPECT_THROW(page.Load(in, threshold), std::runtime_error);
  EXPECT_EQ(memory.used(), 0);
}

TEST(Ifstream, Data_null) {
  PageContainer page;
  Histogram hist (page);
  StatSender stat (page);
  UsedMemory memory(page);

  std::string filename = "data_null.txt";
  std::ifstream in(filename);

  float threshold = 2;
  EXPECT_THROW(page.Load(in, threshold), std::runtime_error);
  EXPECT_EQ(memory.used(), 0);
}*/