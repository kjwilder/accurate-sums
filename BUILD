load("@rules_cc//cc:defs.bzl", "cc_test")

cc_test(
    name = "cancellation_test",
    size = "small",
    srcs = [
        "sum.h",
        "tests/cancellation_test.cc",
    ],
    deps = ["@googletest//:gtest_main"],
)

cc_test(
    name = "round_off_test",
    size = "small",
    srcs = [
        "sum.h",
        "tests/round_off_test.cc",
    ],
    deps = ["@googletest//:gtest_main"],
)
