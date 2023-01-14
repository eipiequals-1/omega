load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library", "cc_test")
load(
    "//:copts.bzl",
    "DEFAULT_COPTS",
    "DEFAULT_LINKOPTS",
)
package(default_visibility= ["//visibility:public"])

cc_library(
    name = "base64",
    srcs = ["base64.cpp"],
    hdrs = ["base64.h"],
    copts = DEFAULT_COPTS,
    linkopts = DEFAULT_LINKOPTS,
)

cc_library(
    name = "tmxparser",
    srcs = ["tmxparser.cpp"],
    hdrs = ["tmxparser.h"],
    deps = ["base64"],
    linkopts = [
        "-ltinyxml2"
    ],
)

