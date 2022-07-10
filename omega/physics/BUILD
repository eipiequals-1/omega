load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library", "cc_test")
load(
    "//:copts.bzl",
    "DEFAULT_COPTS",
    "DEFAULT_LINKOPTS",
)

package(default_visibility= ["//visibility:public"])

cc_library(
    name = "random",
    srcs = ["random.cpp"],
    hdrs = ["random.h"],
    copts = DEFAULT_COPTS,
    linkopts = DEFAULT_LINKOPTS,
)

cc_library(
    name = "math",
    srcs = ["math.cpp"],
    hdrs = ["math.h"],
    copts = DEFAULT_COPTS,
    linkopts = DEFAULT_LINKOPTS,
)

cc_library(
    name = "world",
    srcs = ["world.cpp"],
    hdrs = ["world.h"],
    copts = DEFAULT_COPTS,
    linkopts = DEFAULT_LINKOPTS,
    deps = [
        "//omega/core:using",
        ":math",
        ":body",
        ":physics",
    ]
)

cc_library(
    name = "physics",
    srcs = ["physics.cpp"],
    hdrs = ["physics.h"],
    copts = DEFAULT_COPTS,
    linkopts = DEFAULT_LINKOPTS,
    deps = [
        "@Box2D//:Box2D",
    ]
)

cc_library(
    name = "body",
    srcs = ["body.cpp"],
    hdrs = ["body.h"],
    copts = DEFAULT_COPTS,
    linkopts = DEFAULT_LINKOPTS,
    deps = [
        "@Box2D//:Box2D",
        ":math",
        ":physics",
        "//omega/core:using",
    ]
)
