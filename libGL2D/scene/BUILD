load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library", "cc_test")
load(
    "//:copts.bzl",
    "DEFAULT_COPTS",
    "DEFAULT_LINKOPTS",
)

package(default_visibility= ["//visibility:public"])

cc_library(
    name = "layer",
    srcs = ["layer.cc"],
    hdrs = ["layer.h"],
    copts = DEFAULT_COPTS,
    linkopts = DEFAULT_LINKOPTS,
    deps = [
        "//libGL2D/core:using",
    ]
)

cc_library(
    name = "layer_stack",
    srcs = ["layer_stack.cc"],
    hdrs = ["layer_stack.h"],
    copts = DEFAULT_COPTS,
    linkopts = DEFAULT_LINKOPTS,
    deps = [
        ":layer",
    ]
)
