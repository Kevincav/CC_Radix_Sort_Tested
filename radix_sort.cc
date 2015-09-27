#include "radix_sort.h"

RadixSort();

uint8_t RadixSort::FlipFlopInteger(const uint8_t value) {
    return value ^ 0x80;
}

uint16_t RadixSort::FlipFlopInteger(const uint16_t value) {
    return value ^ 0x8000;
}

uint32_t RadixSort::FlipFlopInteger(const uint32_t value) {
    return value ^ 0x80000000;
}

uint64_t RadixSort::FlipFlopInteger(const uint64_t value) {
    return value ^ 0x8000000000000000;
}

uint32_t FlipFloatingPoint(const uint32_t value) {
    if (value >> 31) {
        return value ^ 0xFFFFFFFF;
    }
    return value ^ 0x80000000;
}

uint32_t RadixSort::FlopFloatingPoint(const uint32_t value) {
    if (value >> 31) {
        return value ^ 0x80000000;
    }
    return value ^ 0xFFFFFFFF;
}

uint64_t FlipFloatingPoint(const uint64_t value) {
    if (value >> 31) {
        return value ^ 0xFFFFFFFFFFFFFFFF;
    }
    return value ^ 0x8000000000000000;
}

uint64_t RadixSort::FlopFloatingPoint(const uint64_t value) {
    if (value >> 31) {
        return value ^ 0x8000000000000000;
    }
    return value ^ 0xFFFFFFFFFFFFFFFF;
}

