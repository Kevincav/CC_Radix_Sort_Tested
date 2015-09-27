#ifndef HISTOGRAM_H_
#define HISTOGRAM_H_

#include <cstdint>
#include <vector>

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

#endif
