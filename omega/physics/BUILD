load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library", "cc_test")
load(
    "//:copts.bzl",
    "DEFAULT_COPTS",
    "DEFAULT_LINKOPTS",
)

package(default_visibility= ["//visibility:public"])

cc_library(
    name = "world",
    srcs = ["world.cpp"],
    hdrs = ["world.h"],
    copts = DEFAULT_COPTS,
    linkopts = DEFAULT_LINKOPTS,
    deps = [
        "//omega/util:std",
        "@box2d//:box2d",
        ":body",
        ":physics_defines",
    ]
)

cc_library(
    name = "physics_defines",
    hdrs = ["physics_defines.h"],
    copts = DEFAULT_COPTS,
    linkopts = DEFAULT_LINKOPTS,
    deps = [
        "@box2d//:box2d",
    ]
)

cc_library(
    name = "body",
    srcs = ["body.cpp"],
    hdrs = ["body.h"],
    copts = DEFAULT_COPTS,
    linkopts = DEFAULT_LINKOPTS,
    deps = [
        "@box2d//:box2d",
        ":physics_defines",
        "//omega/util:math",
    ]
)

cc_library(
    name = "physics",
    hdrs = ["physics.h"],
    copts = DEFAULT_COPTS,
    linkopts = DEFAULT_LINKOPTS,
    deps = [
        ":body",
        ":world",
        ":physics_defines",
    ]
)
