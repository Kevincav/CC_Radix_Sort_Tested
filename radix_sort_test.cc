#include <algorithm>
#include <cstdint>
#include <limits>
#include <memory>
#include <random>
#include <vector>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "histogram.h"
#include "radix_sort.h"

int kLoadTestNumberIterations = 1000000;

namespace {
    
class HistogramMock : public Histogram {
    MOCK_METHOD3(GetHistogram, std::vector<uint64_t>(uint8_t* array, const int size, const enum SortType));
};
        
class RadixSortTest : public ::testing::Test {
 protected:
    virtual void SetUp() {
        histogram_mock_.reset(new HistogramMock);
        radix_sort_.reset(new RadixSort);
    }
    std::unique_ptr<Histogram> histogram_mock_;
    std::unique_ptr<RadixSort> radix_sort_;
};
    
// TODO: Regular unit tests for functions.
    
// Load Tests
    
TEST_F(RadixSortTest, LoadTestUnsignedChar) {
    // Load test unsigned char array sorting.
    std::random_device rd;
    std::default_random_engine engine(rd());
    std::uniform_int_distribution<unsigned char> uniform_dist(std::numeric_limits<unsigned char>::min(), std::numeric_limits<unsigned char>::max());
    std::vector<unsigned char> input, expected;
    for (int i = 0; i < kLoadTestNumberIterations; ++i) {
        const unsigned char value = uniform_dist(engine);
        input.emplace_back(value);
        expected.emplace_back(value);
    }
    std::sort(expected.begin(), expected.end());
    radix_sort_->Sort(input);
    EXPECT_EQ(input, expected);
}

TEST_F(RadixSortTest, LoadTestChar) {
    // Load test char array sorting.
    std::random_device rd;
    std::default_random_engine engine(rd());
    std::uniform_int_distribution<char> uniform_dist(std::numeric_limits<char>::min(), std::numeric_limits<char>::max());
    std::vector<char> input, expected;
    for (int i = 0; i < kLoadTestNumberIterations; ++i) {
        const char value = uniform_dist(engine);
        input.emplace_back(value);
        expected.emplace_back(value);
    }
    std::sort(expected.begin(), expected.end());
    radix_sort_->Sort(input);
    EXPECT_EQ(input, expected);
}
    
TEST_F(RadixSortTest, LoadTestUnsignedShort) {
    // Load test unsigned short array sorting.
    std::random_device rd;
    std::default_random_engine engine(rd());
    std::uniform_int_distribution<unsigned short> uniform_dist(std::numeric_limits<unsigned short>::min(), std::numeric_limits<unsigned short>::max());
    std::vector<unsigned short> input, expected;
    for (int i = 0; i < kLoadTestNumberIterations; ++i) {
        const unsigned short value = uniform_dist(engine);
        input.emplace_back(value);
        expected.emplace_back(value);
    }
    std::sort(expected.begin(), expected.end());
    radix_sort_->Sort(input);
    EXPECT_EQ(input, expected);
}

TEST_F(RadixSortTest, LoadTestShort) {
    // Load test short array sorting.
    std::random_device rd;
    std::default_random_engine engine(rd());
    std::uniform_int_distribution<short> uniform_dist(std::numeric_limits<short>::min(), std::numeric_limits<short>::max());
    std::vector<short> input, expected;
    for (int i = 0; i < kLoadTestNumberIterations; ++i) {
        const short value = uniform_dist(engine);
        input.emplace_back(value);
        expected.emplace_back(value);
    }
    std::sort(expected.begin(), expected.end());
    radix_sort_->Sort(input);
    EXPECT_EQ(input, expected);
}
    
TEST_F(RadixSortTest, LoadTestUnsignedInt) {
    // Load test unsigned integer array sorting.
    std::random_device rd;
    std::default_random_engine engine(rd());
    std::uniform_int_distribution<unsigned int> uniform_dist(std::numeric_limits<unsigned int>::min(), std::numeric_limits<unsigned int>::max());
    std::vector<unsigned int> input, expected;
    for (int i = 0; i < kLoadTestNumberIterations; ++i) {
        const unsigned int value = uniform_dist(engine);
        input.emplace_back(value);
        expected.emplace_back(value);
    }
    std::sort(expected.begin(), expected.end());
    radix_sort_->Sort(input);
    EXPECT_EQ(input, expected);
}

TEST_F(RadixSortTest, LoadTestInt) {
    // Load test integer array sorting.
    std::random_device rd;
    std::default_random_engine engine(rd());
    std::uniform_int_distribution<int> uniform_dist(std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
    std::vector<int> input, expected;
    for (int i = 0; i < kLoadTestNumberIterations; ++i) {
        const int value = uniform_dist(engine);
        input.emplace_back(value);
        expected.emplace_back(value);
    }
    std::sort(expected.begin(), expected.end());
    radix_sort_->Sort(input);
    EXPECT_EQ(input, expected);
}

TEST_F(RadixSortTest, LoadTestUnsignedLong) {
    // Load test unsigned long array sorting.
    std::random_device rd;
    std::default_random_engine engine(rd());
    std::uniform_int_distribution<unsigned long> uniform_dist(std::numeric_limits<unsigned long>::min(), std::numeric_limits<unsigned long>::max());
    std::vector<unsigned long> input, expected;
    for (int i = 0; i < kLoadTestNumberIterations; ++i) {
        const unsigned long value = uniform_dist(engine);
        input.emplace_back(value);
        expected.emplace_back(value);
    }
    std::sort(expected.begin(), expected.end());
    radix_sort_->Sort(input);
    EXPECT_EQ(input, expected);
}

TEST_F(RadixSortTest, LoadTestLong) {
    // Load test integer array sorting.
    std::random_device rd;
    std::default_random_engine engine(rd());
    std::uniform_int_distribution<long> uniform_dist(std::numeric_limits<long>::min(), std::numeric_limits<long>::max());
    std::vector<long> input, expected;
    for (int i = 0; i < kLoadTestNumberIterations; ++i) {
        const long value = uniform_dist(engine);
        input.emplace_back(value);
        expected.emplace_back(value);
    }
    std::sort(expected.begin(), expected.end());
    radix_sort_->Sort(input);
    EXPECT_EQ(input, expected);
}

TEST_F(RadixSortTest, LoadTestFloats) {
    // Load test floating point array sorting.
    std::random_device rd;
    std::default_random_engine engine(rd());
    std::uniform_real_distribution<float> uniform_dist(std::numeric_limits<float>::min(), std::numeric_limits<float>::max());
    std::vector<float> input, expected;
    for (int i = 0; i < kLoadTestNumberIterations; ++i) {
        const float value = uniform_dist(engine);
        input.emplace_back(value);
        expected.emplace_back(value);
    }
    std::sort(expected.begin(), expected.end());
    radix_sort_->Sort(input);
    EXPECT_EQ(input, expected);
}

TEST_F(RadixSortTest, LoadTestuint64_t) {
    // Load test uint64_t array sorting.
    std::random_device rd;
    std::default_random_engine engine(rd());
    std::uniform_int_distribution<uint64_t> uniform_dist(std::numeric_limits<uint64_t>::min(), std::numeric_limits<uint64_t>::max());
    std::vector<uint64_t> input, expected;
    for (int i = 0; i < kLoadTestNumberIterations; ++i) {
        const uint64_t value = uniform_dist(engine);
        input.emplace_back(value);
        expected.emplace_back(value);
    }
    std::sort(expected.begin(), expected.end());
    radix_sort_->Sort(input);
    EXPECT_EQ(input, expected);
}

TEST_F(RadixSortTest, LoadTestint64_t) {
    // Load test integer array sorting.
    std::random_device rd;
    std::default_random_engine engine(rd());
    std::uniform_int_distribution<int64_t> uniform_dist(std::numeric_limits<int64_t>::min(), std::numeric_limits<int64_t>::max());
    std::vector<int64_t> input, expected;
    for (int i = 0; i < kLoadTestNumberIterations; ++i) {
        const int64_t value = uniform_dist(engine);
        input.emplace_back(value);
        expected.emplace_back(value);
    }
    std::sort(expected.begin(), expected.end());
    radix_sort_->Sort(input);
    EXPECT_EQ(input, expected);
}

TEST_F(RadixSortTest, LoadTestDoubles) {
    // Load test doubles array sorting.
    std::random_device rd;
    std::default_random_engine engine(rd());
    std::uniform_real_distribution<double> uniform_dist(std::numeric_limits<double>::min(), std::numeric_limits<double>::max());
    std::vector<double> input, expected;
    for (int i = 0; i < kLoadTestNumberIterations; ++i) {
        const double value = uniform_dist(engine);
        input.emplace_back(value);
        expected.emplace_back(value);
    }
    std::sort(expected.begin(), expected.end());
    radix_sort_->Sort(input);
    EXPECT_EQ(input, expected);
}

}  // namespace

int main (int argc, char *argv[]) {
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
