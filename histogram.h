#ifndef HISTOGRAM_H_
#define HISTOGRAM_H_

#include <cstdint>
#include <limits>
#include <vector>

typedef uint64_t kHistogramDataType;

enum SortType { UNSIGNED, SIGNED, FLOAT };

class Histogram {
 public:
    Histogram() = default;

    // Extract 11 bit byte from unsigned int.
    template <typename T>
    uint16_t ExtractBit(const T value, const uint8_t bit_position);
    
    // Take the prefix sum of a calculated histogram.
    template <typename T>
    void GetPrefixSum(std::vector<T>& histogram);
     
    /*
     * Flip and Flop operations.
    * Unsigned integers are ordered from 0x00000000 to 0xFFFFFFFF from 0 - MAX.
    * Signed Integers are ordered from 0x80000000 to 0xFFFFFFFF from MIN to 0.
    * Signed Integers are ordered from 0x00000000 to 0x7FFFFFFF from 0 to MAX.
    * Floats are ordered from 0xFFFFFFFF to 0x80000000 from MIN to 0.
    * Floats are ordered from 0x00000000 to 0x7FFFFFFF from 0 to MAX.
    * Similar with ULL/LL and Doubles.
    *
    * So for the flip flop operations in order to order floats and signed integers
    * bits ordering from 0x00000000 to 0xFFFFFFFF, I flip the sign bit and all bits 
    * when necessary.  So for both types, when positive (or sign bit == 0) I flip
    * the sign bit.  For Negative integers, I flip the sign bit as well.  For 
    * negative floats, I flip all the bits to put reverse the order as well.
    * When finishing I reverse the process.
    */

    // Integer values, flip and operation.
    template <typename T>
    T FlipFlopInteger(const T value);

    // Floating point values, flip operation.
    template <typename T>
    T FlipFloatingPoint(const T value);
     
    // Floating point values, flop operation.
    template <typename T>
    T FlopFloatingPoint(const T value);
    
    // Generate histogram for uint8_t arrays.  Returns the prefix sum of the histogram.
    std::vector<kHistogramDataType> GetHistogram(uint8_t* array, const int size, const SortType type);
    
    // Generate histogram for uint16_t arrays.  Returns the prefix sum of the histogram.
    std::vector<kHistogramDataType> GetHistogram(uint16_t* array, const int size, SortType type);

    // Generate histogram for uint32_t arrays.  Returns the prefix sum of the histogram.
    std::vector<std::vector<kHistogramDataType>> GetHistogram(uint32_t* array, const int size, const SortType type);

    // Generate histogram for uint64_t arrays.  Returns the prefix sum of the histogram.
    std::vector<std::vector<kHistogramDataType>> GetHistogram(uint64_t* array, const int size, const SortType type);
};

template <typename T>
uint16_t Histogram::ExtractBit(const T value, const uint8_t bit_position) {
    // Extract 11 bit bytes out of uint value.
    return (value >> (11 * bit_position)) & 0x7FF;
}

template <typename T>
void Histogram::GetPrefixSum(std::vector<T>& histogram) {
    // Perform prefix sum on calculated histogram.
    for (int i = 1; i < histogram.size(); ++i) {
        histogram[i] += histogram[i - 1];  
    }
}

template <typename T>
T Histogram::FlipFlopInteger(const T value) {
    // Flip Flop operation for integers.
    return value ^ ((T) 1 << (std::numeric_limits<T>::digits - 1));
}

template <typename T>
T Histogram::FlipFloatingPoint(const T value) {
    // Flip operations for floating point values.
    if (value >> (std::numeric_limits<T>::digits - 1)) {
        return ~value;
    }
    return value ^ ((T) 1 << (std::numeric_limits<T>::digits - 1));
}

template <typename T>
T Histogram::FlopFloatingPoint(const T value) {
    // Flop operations for floating point values.
    if (value >> (std::numeric_limits<T>::digits - 1)) {
        return value ^ ((T) 1 << (std::numeric_limits<T>::digits - 1));
    }
    return ~value;
}

std::vector<kHistogramDataType> Histogram::GetHistogram(uint8_t* array, const int size, const SortType type) {
    // Returns an 8-bit cache efficient histogram.
    std::vector<kHistogramDataType> histogram(std::numeric_limits<uint8_t>::max() + 1, 0);
    if (size == 0) {
        return histogram;
    }
    if (type == UNSIGNED) {  // Histogram is normal if unsigned values.
        for (int i = 0; i < size; ++i) {
            ++histogram[array[i]];
        }
    } else {  // Histogram needs to be fliped if signed values.
        for (int i = 0; i < size; ++i) {
            ++histogram[FlipFlopInteger(array[i])];
        }
    }
    GetPrefixSum(histogram);
    return histogram;
}

std::vector<kHistogramDataType> Histogram::GetHistogram(uint16_t* array, const int size, SortType type) {
    // Returns a 16-bit semi-cache efficient histogram.
    // Sits in L2 Cache instead of L1 like other histograms, still fast though.
    std::vector<kHistogramDataType> histogram(std::numeric_limits<uint16_t>::max() + 1, 0);
    if (size == 0) {
        return histogram;
    }
    if (type == UNSIGNED) {  // Histogram is normal if unsigned values.
        for (int i = 0; i < size; ++i) {
            ++histogram[array[i]];
        }
    } else {
        for (int i = 0; i < size; ++i) {
            ++histogram[FlipFlopInteger(array[i])];
        }
    }
    GetPrefixSum(histogram);
    return histogram;
}

std::vector<std::vector<kHistogramDataType>> Histogram::GetHistogram(uint32_t* array, const int size, SortType type) {
    // Returns 3 11-bit cache efficient histograms.
    std::vector<std::vector<kHistogramDataType>> histogram(3, std::vector<kHistogramDataType>(2048, 0));
    if (size == 0) {
        return histogram;
    }
    if (type == UNSIGNED) {  // Histogram is normal if unsigned values.
        for (int i = 0; i < size; ++i) {
            ++histogram[0][ExtractBit(array[i], 0)];
            ++histogram[1][ExtractBit(array[i], 1)];
            ++histogram[2][ExtractBit(array[i], 2)];
        }
    } else if (type == SIGNED) {  // Histogram needs to be fliped if signed values.
        for (int i = 0; i < size; ++i) {
            const uint32_t value = FlipFlopInteger(array[i]);
            array[i] = value;
            ++histogram[0][ExtractBit(value, 0)];
            ++histogram[1][ExtractBit(value, 1)];
            ++histogram[2][ExtractBit(value, 2)];
        }
    } else {  // Histogram needs to be fliped if floating point values.
        for (int i = 0; i < size; ++i) {
            const uint32_t value = FlipFloatingPoint(array[i]);
            array[i] = value;
            ++histogram[0][ExtractBit(value, 0)];
            ++histogram[1][ExtractBit(value, 1)];
            ++histogram[2][ExtractBit(value, 2)];
        }
    }
    for (auto& hist : histogram) {
        GetPrefixSum(hist);
    }
    return histogram;
}

std::vector<std::vector<kHistogramDataType>> Histogram::GetHistogram(uint64_t* array, const int size, SortType type) {
    // Returns 6 11-bit cache efficient histograms.
    std::vector<std::vector<kHistogramDataType>> histogram(6, std::vector<kHistogramDataType>(2048, 0));
    if (size == 0) {
        return histogram;
    }
    if (type == UNSIGNED) {  // Histogram is normal if unsigned values.
        for (int i = 0; i < size; ++i) {
            ++histogram[0][ExtractBit(array[i], 0)];
            ++histogram[1][ExtractBit(array[i], 1)];
            ++histogram[2][ExtractBit(array[i], 2)];
            ++histogram[3][ExtractBit(array[i], 3)];
            ++histogram[4][ExtractBit(array[i], 4)];
            ++histogram[5][ExtractBit(array[i], 5)];
        }
    } else if (type == SIGNED) {  // Histogram needs to be fliped if signed values.
        for (int i = 0; i < size; ++i) {
            const uint64_t value = FlipFlopInteger(array[i]);
            array[i] = value;
            ++histogram[0][ExtractBit(value, 0)];
            ++histogram[1][ExtractBit(value, 1)];
            ++histogram[2][ExtractBit(value, 2)];
            ++histogram[3][ExtractBit(value, 3)];
            ++histogram[4][ExtractBit(value, 4)];
            ++histogram[5][ExtractBit(value, 5)];
        }
    } else {  // Histogram needs to be fliped if floating point values.
        for (int i = 0; i < size; ++i) {
            const uint64_t value = FlipFloatingPoint(array[i]);
            array[i] = value;
            ++histogram[0][ExtractBit(value, 0)];
            ++histogram[1][ExtractBit(value, 1)];
            ++histogram[2][ExtractBit(value, 2)];
            ++histogram[3][ExtractBit(value, 3)];
            ++histogram[4][ExtractBit(value, 4)];
            ++histogram[5][ExtractBit(value, 5)];
        }
    }
    for (auto& hist : histogram) {
        GetPrefixSum(hist);
    }
    return histogram;
}

#endif
