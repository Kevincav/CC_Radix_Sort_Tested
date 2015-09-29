cc_library(
    name = "main",
    srcs = glob(
        ["gmock-1.7.0/src/*.cc"],
        exclude = ["gmock-1.7.0/src/gmock-all.cc"]
    ),
    hdrs = glob(["gmock-1.7.0/include/**/*.h"]),
    includes = [
        "gmock-1.7.0",
        "gmock-1.7.0/include"
    ],
    linkopts = [],
    visibility = ["//visibility:public"],
)
