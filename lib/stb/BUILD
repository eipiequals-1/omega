load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library", "cc_test")
load(
    "//:copts.bzl",
    "DEFAULT_COPTS",
    "DEFAULT_LINKOPTS",
)

package(default_visibility= ["//visibility:public"])

cc_library(
    name = "stb_image",
    srcs = ["stb_image.cpp"],
    hdrs = ["stb_image.h"],
    copts = ["-std=c++20", "-Werror"],
    linkopts = DEFAULT_LINKOPTS
)
