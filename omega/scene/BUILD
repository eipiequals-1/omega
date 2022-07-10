load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library", "cc_test")
load(
    "//:copts.bzl",
    "DEFAULT_COPTS",
    "DEFAULT_LINKOPTS",
)

package(default_visibility= ["//visibility:public"])

cc_library(
    name = "layer",
    srcs = ["layer.cpp"],
    hdrs = ["layer.h"],
    copts = DEFAULT_COPTS,
    linkopts = DEFAULT_LINKOPTS,
    deps = [
        "//omega/core:using",
    ]
)

cc_library(
    name = "layer_stack",
    srcs = ["layer_stack.cpp"],
    hdrs = ["layer_stack.h"],
    copts = DEFAULT_COPTS,
    linkopts = DEFAULT_LINKOPTS,
    deps = [
        ":layer",
    ]
)

cc_library(
    name = "entity",
    srcs = ["entity.cpp"],
    hdrs = ["entity.h"],
    copts = DEFAULT_COPTS,
    linkopts = DEFAULT_LINKOPTS,
    deps = [
        "//omega/gfx/texture:texture",
        "//omega/physics:math",
    ]
)