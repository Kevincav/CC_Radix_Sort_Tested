#include <algorithm>
#include <cstdint>
#include <memory>
#include <vector>

#include <gtest/gtest.h>

#include "histogram.h"

namespace {

class HistogramTest : public ::testing::Test {
 protected:
     virtual void SetUp() {
        hist_.reset(new Histogram);
     }
     std::unique_ptr<Histogram> hist_;
};

TEST_F(HistogramTest, TestExtractBit_uint32_t) {
    // Tests that ExtractBit returns valid 11 bit bytes for 32 bit value.
    const uint32_t value = 0x12345678;
    ASSERT_EQ(0x678, hist_->ExtractBit(value, 0));
    ASSERT_EQ(0x68A, hist_->ExtractBit(value, 1));
    ASSERT_EQ(0x48, hist_->ExtractBit(value, 2));
}

TEST_F(HistogramTest, TestExtractBit_uint64_t) {
    // Tests that ExtractBit returns valid 11 bit bytes for 64 bit value.
    const uint64_t value = 0x123456789ABCDEF0;
    ASSERT_EQ(0x6F0, hist_->ExtractBit(value, 0));
    ASSERT_EQ(0x79B, hist_->ExtractBit(value, 1));
    ASSERT_EQ(0x26A, hist_->ExtractBit(value, 2));
    ASSERT_EQ(0x33C, hist_->ExtractBit(value, 3));
    ASSERT_EQ(0x345, hist_->ExtractBit(value, 4));
    ASSERT_EQ(0x24, hist_->ExtractBit(value, 5));
}

TEST_F(HistogramTest, TestFlipFlopForIntegers8Bit) {
    // Tests similar to 32 Bit test but with 8 Bit values.
    const uint8_t negative = 0x8F;
    const uint8_t zero = 0;
    const uint8_t positive = 0x0F;
    const uint8_t flip_flop_negative_value = hist_->FlipFlopInteger(negative);
    const uint8_t flip_flop_zero_value = hist_->FlipFlopInteger(zero);
    const uint8_t flip_flop_positive_value = hist_->FlipFlopInteger(positive);
    EXPECT_EQ(0x0F, flip_flop_negative_value);
    EXPECT_EQ(0x80, flip_flop_zero_value);
    EXPECT_EQ(0x8F, flip_flop_positive_value);
}

TEST_F(HistogramTest, TestFlipFlopForIntegers16Bit) {
    // Tests similar to 32 Bit test but with 16 Bit values.
    const uint16_t negative = 0x80FF;
    const uint16_t zero = 0;
    const uint16_t positive = 0x00FF;
    const uint16_t flip_flop_negative_value = hist_->FlipFlopInteger(negative);
    const uint16_t flip_flop_zero_value = hist_->FlipFlopInteger(zero);
    const uint16_t flip_flop_positive_value = hist_->FlipFlopInteger(positive);
    EXPECT_EQ(0x00FF, flip_flop_negative_value);
    EXPECT_EQ(0x8000, flip_flop_zero_value);
    EXPECT_EQ(0x80FF, flip_flop_positive_value);
}

TEST_F(HistogramTest, TestFlipFlopForIntegers32Bit) {
    // Tests that negative value will be between [0.0.0.0, 127.255.255.255] when flipped.
    // Tests that zero value will be 128.0.0.0 when flipped.
    // Tests that positive value will be between [128.0.0.0, 255.255.255.255] when flipped.
    const uint32_t negative = 0x8000FFFF;
    const uint32_t zero = 0;
    const uint32_t positive = 0x0000FFFF;
    const uint32_t flip_flop_negative_value = hist_->FlipFlopInteger(negative);
    const uint32_t flip_flop_zero_value = hist_->FlipFlopInteger(zero);
    const uint32_t flip_flop_positive_value = hist_->FlipFlopInteger(positive);
    EXPECT_EQ(0x0000FFFF, flip_flop_negative_value);
    EXPECT_EQ(0x80000000, flip_flop_zero_value);
    EXPECT_EQ(0x8000FFFF, flip_flop_positive_value);
}

TEST_F(HistogramTest, TestFlipForFloatingPointValues32Bit) {
    // Tests that negative value will be between [0.0.0.0, 127.255.255.255] when flipped.
    // Tests that zero value will be 128.0.0.0 when flipped.
    // Tests that positive value will be between [128.0.0.0, 255.255.255.255] when flipped.
    const uint32_t negative = 0x8000FFFF;
    const uint32_t zero = 0;
    const uint32_t positive = 0x0000FFFF;
    const uint32_t flip_flop_negative_value = hist_->FlipFloatingPoint(negative);
    const uint32_t flip_flop_zero_value = hist_->FlipFloatingPoint(zero);
    const uint32_t flip_flop_positive_value = hist_->FlipFloatingPoint(positive);
    EXPECT_EQ(0x7FFF0000, flip_flop_negative_value);
    EXPECT_EQ(0x80000000, flip_flop_zero_value);
    EXPECT_EQ(0x8000FFFF, flip_flop_positive_value);
}

TEST_F(HistogramTest, TestFlopForFloatingPointValues32Bit) {
    // Tests that negative value will be between [0.0.0.0, 127.255.255.255] when flipped.
    // Tests that zero value will be 128.0.0.0 when flipped.
    // Tests that positive value will be between [128.0.0.0, 255.255.255.255] when flipped.
    const uint32_t negative = 0x7FFF0000;
    const uint32_t zero = 0x80000000;
    const uint32_t positive = 0x8000FFFF;
    const uint32_t flip_flop_negative_value = hist_->FlopFloatingPoint(negative);
    const uint32_t flip_flop_zero_value = hist_->FlopFloatingPoint(zero);
    const uint32_t flip_flop_positive_value = hist_->FlopFloatingPoint(positive);
    EXPECT_EQ(0x8000FFFF, flip_flop_negative_value);
    EXPECT_EQ(0, flip_flop_zero_value);
    EXPECT_EQ(0x0000FFFF, flip_flop_positive_value);
}
    
TEST_F(HistogramTest, TestFlipFlopForIntegers64Bit) {
    // Tests similar to 32 Bit test but with 64 Bit values.
    const uint64_t negative = 0x8000FFFFFFFFFFFF;
    const uint64_t zero = 0;
    const uint64_t positive = 0x0000FFFFFFFFFFFF;
    const uint64_t flip_flop_negative_value = hist_->FlipFlopInteger(negative);
    const uint64_t flip_flop_zero_value = hist_->FlipFlopInteger(zero);
    const uint64_t flip_flop_positive_value = hist_->FlipFlopInteger(positive);
    EXPECT_EQ(0x0000FFFFFFFFFFFF, flip_flop_negative_value);
    EXPECT_EQ(0x8000000000000000, flip_flop_zero_value);
    EXPECT_EQ(0x8000FFFFFFFFFFFF, flip_flop_positive_value);
}
    
TEST_F(HistogramTest, TestFlipForFloatingPointValues64Bit) {
    // Tests similar to 32 Bit test but with 64 Bit values.
    const uint64_t negative = 0x8000FFFFFFFFFFFF;
    const uint64_t zero = 0;
    const uint64_t positive = 0x0000FFFFFFFFFFFF;
    const uint64_t flip_flop_negative_value = hist_->FlipFloatingPoint(negative);
    const uint64_t flip_flop_zero_value = hist_->FlipFloatingPoint(zero);
    const uint64_t flip_flop_positive_value = hist_->FlipFloatingPoint(positive);
    EXPECT_EQ(0x7FFF000000000000, flip_flop_negative_value);
    EXPECT_EQ(0x8000000000000000, flip_flop_zero_value);
    EXPECT_EQ(0x8000FFFFFFFFFFFF, flip_flop_positive_value);
}
    
TEST_F(HistogramTest, TestFlopForFloatingPointValues64Bit) {
    // Tests similar to 32 Bit test but with 64 Bit values.
    const uint64_t negative = 0x7FFF000000000000;
    const uint64_t zero = 0x8000000000000000;
    const uint64_t positive = 0x8000FFFFFFFFFFFF;
    const uint64_t flip_flop_negative_value = hist_->FlopFloatingPoint(negative);
    const uint64_t flip_flop_zero_value = hist_->FlopFloatingPoint(zero);
    const uint64_t flip_flop_positive_value = hist_->FlopFloatingPoint(positive);
    EXPECT_EQ(0x8000FFFFFFFFFFFF, flip_flop_negative_value);
    EXPECT_EQ(0, flip_flop_zero_value);
    EXPECT_EQ(0x0000FFFFFFFFFFFF, flip_flop_positive_value);
}

TEST_F(HistogramTest, TestPrefixSumEmptyHistogram) {
    // Tests that GetPrefixSum doesn't do anything weird with empty lists.
    std::vector<uint32_t> input;
    std::vector<uint32_t> expected;
    hist_->GetPrefixSum(input);
    EXPECT_EQ(expected, input);
}

TEST_F(HistogramTest, TestPrefixSumWithHistogram) {
    // Tests that GetPrefixSum calculates a prefix sum accurately.
    std::vector<uint32_t> input({3,2,8,13,21});
    std::vector<uint32_t> expected({3,5,13, 26, 47});
    hist_->GetPrefixSum(input);
    EXPECT_EQ(expected, input);
}
    
TEST_F(HistogramTest, TestGetHistogramFor8BitArrayEmpty) {
    // Tests that sending an empty list to GetHistogram returns empty.
    std::vector<uint8_t> input;
    std::vector<uint64_t> expected(256, 0);
    std::vector<uint64_t> output = hist_->GetHistogram(&input[0], input.size(), UNSIGNED);
    EXPECT_EQ(expected, output);
}
    
TEST_F(HistogramTest, TestGetHistogramFor8BitArrayUnsigned) {
    // Tests GetHistogram with unsigned chars.
    std::vector<uint8_t> input({0, 13, 27, 123, 182, 223, 255, 123, 13});
    std::vector<uint64_t> expected(256, 0);
    for (auto& value : input) {
        ++expected[value];
    }
    hist_->GetPrefixSum(expected);
    std::vector<uint64_t> output = hist_->GetHistogram(&input[0], input.size(), UNSIGNED);
    EXPECT_EQ(expected, output);
}
    
TEST_F(HistogramTest, TestGetHistogramFor8BitArraySigned) {
    // Tests GetHistogram with signed chars.
    std::vector<char> input({-127, -43, 0, 13, 27, 123, 127, -113, -18, 123, 13, -43});
    uint8_t *input_revised = (uint8_t *) &input[0];
    std::vector<uint64_t> expected(256, 0);
    for (int i = 0; i < input.size(); ++i) {
        ++expected[hist_->FlipFlopInteger(input_revised[i])];
    }
    hist_->GetPrefixSum(expected);
    std::vector<uint64_t> output = hist_->GetHistogram(input_revised, input.size(), SIGNED);
    EXPECT_EQ(expected, output);
}
    
TEST_F(HistogramTest, TestGetHistogramFor16BitArrayEmpty) {
    // Tests that sending an empty list to GetHistogram returns empty.
    std::vector<uint16_t> input;
    std::vector<uint64_t> expected(65536, 0);
    std::vector<uint64_t> output = hist_->GetHistogram(&input[0], input.size(), UNSIGNED);
    EXPECT_EQ(expected, output);
}

TEST_F(HistogramTest, TestGetHistogramFor16BitArrayUnsigned) {
    // Tests GetHistogram with unsigned shorts.
    std::vector<uint8_t> input({0, 13, 27, 123, 182, 223, 255, 123, 13});
    std::vector<uint64_t> expected(256, 0);
    for (auto& value : input) {
        ++expected[value];
    }
    hist_->GetPrefixSum(expected);
    std::vector<uint64_t> output = hist_->GetHistogram(&input[0], input.size(), UNSIGNED);
    EXPECT_EQ(expected, output);
}

TEST_F(HistogramTest, TestGetHistogramFor16BitArraySigned) {
    // Tests GetHistogram with signed shorts.
    std::vector<short> input({-127, -43, 0, 13, 27, 12345, 127, -20003, -18, 123, 13, -43});
    uint16_t *input_revised = (uint16_t *) &input[0];
    std::vector<uint64_t> expected(65536, 0);
    for (int i = 0; i < input.size(); ++i) {
        ++expected[hist_->FlipFlopInteger(input_revised[i])];
    }
    hist_->GetPrefixSum(expected);
    std::vector<uint64_t> output = hist_->GetHistogram(input_revised, input.size(), SIGNED);
    EXPECT_EQ(expected, output);
}

TEST_F(HistogramTest, TestGetHistogramFor32BitArrayEmpty) {
    // Tests that sending an empty list to GetHistogram returns empty.
    std::vector<uint32_t> input;
    std::vector<std::vector<uint64_t>> expected(3, std::vector<uint64_t>(2048, 0));
    std::vector<std::vector<uint64_t>> output = hist_->GetHistogram(&input[0], input.size(), UNSIGNED);
    EXPECT_EQ(expected, output);
}

TEST_F(HistogramTest, TestGetHistogramFor32BitArrayUnsigned) {
    // Tests GetHistogram with unsigned ints.
    std::vector<uint32_t> input({0, 13, 27, 123, 182, 2232392824, 255, 123232452, 13});
    std::vector<std::vector<uint64_t>> expected(3, std::vector<uint64_t>(2048, 0));
    for (auto& value : input) {
        ++expected[0][hist_->ExtractBit(value, 0)];
        ++expected[1][hist_->ExtractBit(value, 1)];
        ++expected[2][hist_->ExtractBit(value, 2)];
    }
    for (int i = 0; i < expected.size(); ++i) {
        hist_->GetPrefixSum(expected[i]);
    }
    std::vector<std::vector<uint64_t>> output = hist_->GetHistogram(&input[0], input.size(), UNSIGNED);
    EXPECT_EQ(expected, output);
}

TEST_F(HistogramTest, TestGetHistogramFor32BitArraySigned) {
    // Tests GetHistogram with signed ints.
    std::vector<int> input({-1279248232, -43, 0, 13, 27242324, 12345, 127, -20003249, -18, 123, 13, -432424234});
    uint32_t *input_revised = (uint32_t *) &input[0];
    std::vector<std::vector<uint64_t>> expected(3, std::vector<uint64_t>(2048, 0));
    for (int i = 0; i < input.size(); ++i) {
        const uint32_t value = hist_->FlipFlopInteger(input_revised[i]);
        ++expected[0][hist_->ExtractBit(value, 0)];
        ++expected[1][hist_->ExtractBit(value, 1)];
        ++expected[2][hist_->ExtractBit(value, 2)];
    }
    for (int i = 0; i < expected.size(); ++i) {
        hist_->GetPrefixSum(expected[i]);
    }
    std::vector<std::vector<uint64_t>> output = hist_->GetHistogram(input_revised, input.size(), SIGNED);
    EXPECT_EQ(expected, output);
}

TEST_F(HistogramTest, TestGetHistogramFor32BitArrayFloat) {
    // Tests GetHistogram with floats.
    std::vector<float> input({-1279248232.2924, 0.0000001, 13.0242, 27282324.0, 12345.0, -20003242449.0, -18.813814, 123.0, 13.0, -4324244.0});
    uint32_t *input_revised = (uint32_t *) &input[0];
    std::vector<std::vector<uint64_t>> expected(3, std::vector<uint64_t>(2048, 0));
    for (int i = 0; i < input.size(); ++i) {
        const uint32_t value = hist_->FlipFloatingPoint(input_revised[i]);
        ++expected[0][hist_->ExtractBit(value, 0)];
        ++expected[1][hist_->ExtractBit(value, 1)];
        ++expected[2][hist_->ExtractBit(value, 2)];
    }
    for (int i = 0; i < expected.size(); ++i) {
        hist_->GetPrefixSum(expected[i]);
    }
    std::vector<std::vector<uint64_t>> output = hist_->GetHistogram(input_revised, input.size(), FLOAT);
    EXPECT_EQ(expected, output);
}
    
TEST_F(HistogramTest, TestGetHistogramFor64BitArrayEmpty) {
    // Tests that sending an empty list to GetHistogram returns empty.
    std::vector<uint64_t> input;
    std::vector<std::vector<uint64_t>> expected(6, std::vector<uint64_t>(2048, 0));
    std::vector<std::vector<uint64_t>> output = hist_->GetHistogram(&input[0], input.size(), UNSIGNED);
    EXPECT_EQ(expected, output);
}

TEST_F(HistogramTest, TestGetHistogramFor64BitArrayUnsigned) {
    // Tests GetHistogram with unsigned long longs.
    std::vector<uint64_t> input({0, 13, 272409240842082048, 123, 182, 2232392824, 255, 123232452, 13});
    std::vector<std::vector<uint64_t>> expected(6, std::vector<uint64_t>(2048, 0));
    for (auto& value : input) {
        ++expected[0][hist_->ExtractBit(value, 0)];
        ++expected[1][hist_->ExtractBit(value, 1)];
        ++expected[2][hist_->ExtractBit(value, 2)];
        ++expected[3][hist_->ExtractBit(value, 3)];
        ++expected[4][hist_->ExtractBit(value, 4)];
        ++expected[5][hist_->ExtractBit(value, 5)];
    }
    for (int i = 0; i < expected.size(); ++i) {
        hist_->GetPrefixSum(expected[i]);
    }
    std::vector<std::vector<uint64_t>> output = hist_->GetHistogram(&input[0], input.size(), UNSIGNED);
    EXPECT_EQ(expected, output);
}

TEST_F(HistogramTest, TestGetHistogramFor64BitArraySigned) {
    // Tests GetHistogram with signed long longs.
    std::vector<int64_t> input({-1279248232, -43, 0, 13, 27242324, 12345, 127, -2000324924242424, -18, 123, 13, -432424234});
    uint64_t *input_revised = (uint64_t *) &input[0];
    std::vector<std::vector<uint64_t>> expected(6, std::vector<uint64_t>(2048, 0));
    for (int i = 0; i < input.size(); ++i) {
        const uint64_t value = hist_->FlipFlopInteger(input_revised[i]);
        ++expected[0][hist_->ExtractBit(value, 0)];
        ++expected[1][hist_->ExtractBit(value, 1)];
        ++expected[2][hist_->ExtractBit(value, 2)];
        ++expected[3][hist_->ExtractBit(value, 3)];
        ++expected[4][hist_->ExtractBit(value, 4)];
        ++expected[5][hist_->ExtractBit(value, 5)];
    }
    for (int i = 0; i < expected.size(); ++i) {
        hist_->GetPrefixSum(expected[i]);
    }
    std::vector<std::vector<uint64_t>> output = hist_->GetHistogram(input_revised, input.size(), SIGNED);
    EXPECT_EQ(expected, output);
}

TEST_F(HistogramTest, TestGetHistogramFor64BitArrayFloat) {
    // Tests GetHistogram with doubles.
    std::vector<double> input({-1279248224249232.29223234, 0.0000001, 13.0242, 27282324.0, 12345.0, 123.0, 13.0, -4324244.0});
    uint64_t *input_revised = (uint64_t *) &input[0];
    std::vector<std::vector<uint64_t>> expected(6, std::vector<uint64_t>(2048, 0));
    for (int i = 0; i < input.size(); ++i) {
        const uint64_t value = hist_->FlipFloatingPoint(input_revised[i]);
        ++expected[0][hist_->ExtractBit(value, 0)];
        ++expected[1][hist_->ExtractBit(value, 1)];
        ++expected[2][hist_->ExtractBit(value, 2)];
        ++expected[3][hist_->ExtractBit(value, 3)];
        ++expected[4][hist_->ExtractBit(value, 4)];
        ++expected[5][hist_->ExtractBit(value, 5)];
    }
    for (int i = 0; i < expected.size(); ++i) {
        hist_->GetPrefixSum(expected[i]);
    }
    std::vector<std::vector<uint64_t>> output = hist_->GetHistogram(input_revised, input.size(), FLOAT);
    EXPECT_EQ(expected, output);
}

}  // namespace

int main (int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
