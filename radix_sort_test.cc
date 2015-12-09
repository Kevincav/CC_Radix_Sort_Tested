// Copyright 2015 Kevin Melkowski

#include "sort/radix_sort/radix_sort.h"

#include <stdint.h>

#include <memory>
#include <vector>

#include "glog/logging.h"
#include "gtest/gtest.h"

namespace {

class RadixSortTest : public ::testing::Test {
 protected:
  virtual void SetUp() { sort_.reset(new RadixSort); }
  std::unique_ptr<RadixSort> sort_;
};

TEST_F(RadixSortTest, TestUnsignedint8_tSorting) {
  std::vector<uint8_t> values({13, 255, 1, 11, 137, 113});
  std::vector<uint8_t> expected({1, 11, 13, 113, 137, 255});
  sort_->Sort(values);
  EXPECT_EQ(expected, values);
}

TEST_F(RadixSortTest, TestSignedint8_tSorting) {
  std::vector<int8_t> values({13, -123, 1, -11, 127, 113});
  std::vector<int8_t> expected({-123, -11, 1, 13, 113, 127});
  sort_->Sort(values);
  EXPECT_EQ(expected, values);
}

TEST_F(RadixSortTest, TestUnsignedint16_tSorting) {
  std::vector<uint16_t> values({13, 255, 1, 11, 137, 113});
  std::vector<uint16_t> expected({1, 11, 13, 113, 137, 255});
  sort_->Sort(values);
  EXPECT_EQ(expected, values);
}

TEST_F(RadixSortTest, TestSignedint16_tSorting) {
  std::vector<int16_t> values({13, -123, 1, -11, 127, 113});
  std::vector<int16_t> expected({-123, -11, 1, 13, 113, 127});
  sort_->Sort(values);
  EXPECT_EQ(expected, values);
}

TEST_F(RadixSortTest, TestUnsignedIntSorting) {
  std::vector<uint32_t> values({13, 255, 1, 11, 137, 113});
  std::vector<uint32_t> expected({1, 11, 13, 113, 137, 255});
  sort_->Sort(values);
  EXPECT_EQ(expected, values);
}

TEST_F(RadixSortTest, TestSignedIntSorting) {
  std::vector<int32_t> values({13, -123, 1, -11, 127, 113});
  std::vector<int32_t> expected({-123, -11, 1, 13, 113, 127});
  sort_->Sort(values);
  EXPECT_EQ(expected, values);
}

TEST_F(RadixSortTest, TestFloatSorting) {
  std::vector<float> values({13, -123, 0.00001, -11.13, 127.127, 113});
  std::vector<float> expected({-123, -11.13, 0.00001, 13, 113, 127.127});
  sort_->Sort(values);
  EXPECT_EQ(expected, values);
}

TEST_F(RadixSortTest, TestUnsignedLongLongSorting) {
  std::vector<uint64_t> values({13, 255, 1, 11, 137, 113});
  std::vector<uint64_t> expected({1, 11, 13, 113, 137, 255});
  sort_->Sort(values);
  EXPECT_EQ(expected, values);
}

TEST_F(RadixSortTest, TestLongLongSorting) {
  std::vector<int64_t> values({13, -123, 1, -11, 127, 113});
  std::vector<int64_t> expected({-123, -11, 1, 13, 113, 127});
  sort_->Sort(values);
  EXPECT_EQ(expected, values);
}

TEST_F(RadixSortTest, TestiDoubleSorting) {
  std::vector<double> values({13, -123, 0.00001, -11.13, 127.127, 113});
  std::vector<double> expected({-123, -11.13, 0.00001, 13, 113, 127.127});
  sort_->Sort(values);
  EXPECT_EQ(expected, values);
}

}  // namespace

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  google::InitGoogleLogging(argv[0]);
  google::InstallFailureSignalHandler();
  return RUN_ALL_TESTS();
}
