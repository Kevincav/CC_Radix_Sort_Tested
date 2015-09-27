#ifndef RADIX_SORT_H_
#define RADIX_SORT_H_

#include <memory>
#include <vector>

#include "histogram.h"

class RadixSort {
 public:
     RadixSort();
     
 private:
     std::unique_ptr<Histogram> histogram_;
};

#endif
