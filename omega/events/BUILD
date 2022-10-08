load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library", "cc_test")
load(
    "//:copts.bzl",
    "DEFAULT_COPTS",
    "DEFAULT_LINKOPTS",
)

package(default_visibility= ["//visibility:public"])

cc_library(
    name = "event",
    hdrs = ["event.h"],
    copts = DEFAULT_COPTS,
    linkopts = DEFAULT_LINKOPTS,
    deps = [
        "@SDL2//:SDL2",
    ]
)

cc_library(
    name = "input_manager",
    srcs = ["input_manager.cpp"],
    hdrs = ["input_manager.h"],
    copts = DEFAULT_COPTS,
    linkopts = DEFAULT_LINKOPTS,
    deps = [
        "@SDL2//:SDL2",
        "//omega/util:util",
        "//omega/core:window",
        ":event",
        ":key_manager",
    ]
)

cc_library(
    name = "input_processor",
    srcs = ["input_processor.cpp"],
    hdrs = ["input_processor.h"],
    copts = DEFAULT_COPTS,
    linkopts = DEFAULT_LINKOPTS,
    deps = [
        "@SDL2//:SDL2",
        "//omega/util:util",
        ":event",
        ":input_manager"
    ]
)

cc_library(
    name = "key_manager",
    srcs = ["key_manager.cpp"],
    hdrs = ["key_manager.h"],
    copts = DEFAULT_COPTS,
    linkopts = DEFAULT_LINKOPTS,
    deps = [
        "@SDL2//:SDL2",
        ":event",
    ]
)

cc_library(
    name = "events",
    hdrs = ["events.h"],
    copts = DEFAULT_COPTS,
    linkopts = DEFAULT_LINKOPTS,
    deps = [
        ":event",
        ":input_manager",
        ":input_processor",
        ":key_manager",
    ]
)
