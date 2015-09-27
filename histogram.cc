#include "histogram.h"

#include <limits>

/*
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
    return value ^ (1 << std::numeric_limits<T>::digits);
}

template <typename T>
T Histogram::FlipFloatingPoint(const T value) {
    // Flip operations for floating point values.
    if (value >> std::numeric_limits<T>::digits) {
        return value ^ std::numeric_limits<T>::max();
    }
    return value ^ (1 << std::numeric_limits<T>::digits);
}

template <typename T>
T Histogram::FlopFloatingPoint(const T value) {
    // Flop operations for floating point values.
    if (value >> std::numeric_limits<T>::digits) {
        return value ^ (1 << std::numeric_limits<T>::digits);
    }
    return value ^ std::numeric_limits<T>::max();
}
*/
