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
        "//libGL2D/core:using",
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
        "//libGL2D/gfx/texture:texture",
        "//libGL2D/physics:math",
    ]
)