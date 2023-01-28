load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library", "cc_test")
load(
    "//:copts.bzl",
    "DEFAULT_COPTS",
    "DEFAULT_LINKOPTS",
)

package(default_visibility= ["//visibility:public"])

cc_library(
    name = "event",
    hdrs = ["event.hpp"],
    copts = DEFAULT_COPTS,
    linkopts = DEFAULT_LINKOPTS,
    deps = [
        "@SDL2//:SDL2",
    ]
)

cc_library(
    name = "input_manager",
    srcs = ["input_manager.cpp"],
    hdrs = ["input_manager.hpp"],
    copts = DEFAULT_COPTS,
    linkopts = DEFAULT_LINKOPTS,
    deps = [
        "@SDL2//:SDL2",
        "//omega/util:std",
        "//omega/util:math",
        "//omega/core:window",
        ":event",
        ":key_manager",
    ]
)

cc_library(
    name = "key_manager",
    srcs = ["key_manager.cpp"],
    hdrs = ["key_manager.hpp"],
    copts = DEFAULT_COPTS,
    linkopts = DEFAULT_LINKOPTS,
    deps = [
        "@SDL2//:SDL2",
        ":event",
    ]
)

cc_library(
    name = "events",
    hdrs = ["events.hpp"],
    copts = DEFAULT_COPTS,
    linkopts = DEFAULT_LINKOPTS,
    deps = [
        ":event",
        ":input_manager",
        ":key_manager",
    ]
)
