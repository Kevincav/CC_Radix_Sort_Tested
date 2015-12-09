// Copyright 2015 Kevin Melkowski

#ifndef RADIX_SORT_H_
#define RADIX_SORT_H_

#include <cstdint>
#include <limits>
#include <memory>
#include <vector>

#include "sort/radix_sort/histogram.h"

class RadixSort {
 public:
  RadixSort();

  // Perform Radix Sort for unsigned chars and shorts.
  template <typename T>
  void SortType(T* array, const int size, const enum SortType type);

  // Perform Radix Sort for unsigned ints.
  void SortType(uint32_t* array, const int size, const enum SortType type);

  // Perform Radix Sort for unsigned long longs.
  void SortType(uint64_t* array, const int size, const enum SortType type);

  // Sort the array with any standard data type, expects vectors for now.
  template <typename T>
  void Sort(std::vector<T>& array);  // NOLINT

 private:
  std::unique_ptr<Histogram> histogram_;
};

RadixSort::RadixSort() { histogram_.reset(new Histogram); }

template <typename T>
void RadixSort::SortType(T* array, const int size, const enum SortType type) {
  // Sort all 8 and 16-bit data types based on uint8/16_t bit structure.
  if (size == 0 || type == FLOAT) {
    return;
  }
  std::vector<kHistogramDataType> T_hist =
      histogram_->GetHistogram(array, size, type);
  std::vector<T> placeholder_array(size);
  for (int i = size - 1; i >= 0; --i) {
    placeholder_array[--T_hist[array[i]]] = array[i];
  }
  if (type == UNSIGNED) {  // No Flip Flop.
    for (int i = 0; i < placeholder_array.size(); ++i) {
      array[i] = placeholder_array[i];
    }
  } else {  // Use FlipFlopInteger.
    for (int i = 0; i < placeholder_array.size(); ++i) {
      array[i] = histogram_->FlipFlopInteger(placeholder_array[i]);
    }
  }
}

void RadixSort::SortType(uint32_t* array, const int size,
                         const enum SortType type) {
  // Sort all 32-bit data types based on uint32_t bit structure.
  if (size == 0) {
    return;
  }
  std::vector<std::vector<kHistogramDataType>> int_hist =
      histogram_->GetHistogram(array, size, type);
  std::vector<uint32_t> placeholder_array(size);
  for (int i = size - 1; i >= 0; --i) {
    placeholder_array[--int_hist[0][histogram_->ExtractBit(array[i], 0)]] =
        array[i];
  }
  for (int i = size - 1; i >= 0; --i) {
    array[--int_hist[1][histogram_->ExtractBit(placeholder_array[i], 1)]] =
        placeholder_array[i];
  }
  for (int i = size - 1; i >= 0; --i) {
    placeholder_array[--int_hist[2][histogram_->ExtractBit(array[i], 2)]] =
        array[i];
  }

  if (type == UNSIGNED) {  // No Flip Flop.
    for (int i = 0; i < placeholder_array.size(); ++i) {
      array[i] = placeholder_array[i];
    }
  } else if (type == SIGNED) {  // Use FlipFlopInteger.
    for (int i = 0; i < placeholder_array.size(); ++i) {
      array[i] = histogram_->FlipFlopInteger(placeholder_array[i]);
    }
  } else {  // Use FlopFloatingPoint.
    for (int i = 0; i < placeholder_array.size(); ++i) {
      array[i] = histogram_->FlopFloatingPoint(placeholder_array[i]);
    }
  }
}

void RadixSort::SortType(uint64_t* array, const int size,
                         const enum SortType type) {
  // Sort all 64-bit data types based on uint64_t bit structure.
  if (size == 0) {
    return;
  }
  std::vector<std::vector<kHistogramDataType>> ULL_hist =
      histogram_->GetHistogram(array, size, type);
  std::vector<uint64_t> placeholder_array(size);
  for (int i = size - 1; i >= 0; --i) {
    placeholder_array[--ULL_hist[0][histogram_->ExtractBit(array[i], 0)]] =
        array[i];
  }
  for (int i = size - 1; i >= 0; --i) {
    array[--ULL_hist[1][histogram_->ExtractBit(placeholder_array[i], 1)]] =
        placeholder_array[i];
  }
  for (int i = size - 1; i >= 0; --i) {
    placeholder_array[--ULL_hist[2][histogram_->ExtractBit(array[i], 2)]] =
        array[i];
  }
  for (int i = size - 1; i >= 0; --i) {
    array[--ULL_hist[3][histogram_->ExtractBit(placeholder_array[i], 3)]] =
        placeholder_array[i];
  }
  for (int i = size - 1; i >= 0; --i) {
    placeholder_array[--ULL_hist[4][histogram_->ExtractBit(array[i], 4)]] =
        array[i];
  }
  if (type == UNSIGNED) {  // No Flip Flop.
    for (int i = size - 1; i >= 0; --i) {
      array[--ULL_hist[5][histogram_->ExtractBit(placeholder_array[i], 5)]] =
          placeholder_array[i];
    }
  } else if (type == SIGNED) {  // Use FlipFlopInteger.
    for (int i = size - 1; i >= 0; --i) {
      array[--ULL_hist[5][histogram_->ExtractBit(placeholder_array[i], 5)]] =
          histogram_->FlipFlopInteger(placeholder_array[i]);
    }
  } else {  // Use FlopFloatingPoint.
    for (int i = size - 1; i >= 0; --i) {
      array[--ULL_hist[5][histogram_->ExtractBit(placeholder_array[i], 5)]] =
          histogram_->FlopFloatingPoint(placeholder_array[i]);
    }
  }
}

template <typename T>
void RadixSort::Sort(std::vector<T>& array) {
  // Sort the array.  Expected types all but bool and long double.
  // Detect if type is unsigned, signed or float for sorting.
  const bool is_signed = std::numeric_limits<T>::is_signed;
  const bool is_integer = std::numeric_limits<T>::is_integer;
  enum SortType type;
  if (is_signed && is_integer) {  // This is an integer type.
    type = SIGNED;
  } else if (is_signed && !is_integer) {  // This is a floating point type.
    type = FLOAT;
  } else if (!is_signed && is_integer) {  // This is an unsigned type.
    type = UNSIGNED;
  } else {  // Not sure if this will ever be called, but it can't sort this
            // type.
    return;
  }
  switch (sizeof(T)) {
    case 1:  // All 8 bit types.
      SortType(reinterpret_cast<uint8_t*>(&array[0]), array.size(), type);
      break;

    case 2:  // All 16 bit types.
      SortType(reinterpret_cast<uint16_t*>(&array[0]), array.size(), type);
      break;

    case 4:  // All 32 bit types.
      SortType(reinterpret_cast<uint32_t*>(&array[0]), array.size(), type);
      break;

    case 8:  // All 64 bit types.
      SortType(reinterpret_cast<uint64_t*>(&array[0]), array.size(), type);
      break;

    default:  // Can't handle this case.
      return;
  }
}

#endif  // RADIX_SORT_H_
