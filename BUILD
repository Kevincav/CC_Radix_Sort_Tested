#LIBRARIES

cc_library(
    name = "radix_sort",
    hdrs = ["radix_sort.h"],
    includes = ["histogram.h"],
    visibility = ["//visibility:public"],
)

#TESTS

cc_test(
    name = "histogram_test",
    srcs = ["histogram_test.cc"],
    deps = [
        "//third_party/glog",
        "//third_party/gtest",
    ],
    includes = ["histogram.h"],
)

cc_test(
    name = "radix_sort_test",
    srcs = ["radix_sort_test.cc"],
    deps = [
        "//third_party/glog",
        "//third_party/gtest",
    ],
    includes = ["radix_sort.h"],
)

#BINARIES
