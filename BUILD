

# TESTS

cc_test(
    name = "histogram_test",
    srcs = ["histogram_test.cc"],
    deps = ["@gtest//:main"],
    includes = [
    	"histogram.h",
    ],
)

cc_test(
    name = "radix_sort_test",
    srcs = ["radix_sort_test.cc"],
    deps = [
        "@gmock//:main",
    	"@gtest//:main"
    ],
    includes = [
    	"histogram.h",
    	"radix_sort.h"
    ],
)

# BINARIES

cc_binary(
    name = "radix_sort_main",
    srcs = ["radix_sort_main.cc"],
    deps = [],
    includes = ["radix_sort.h"],
)
