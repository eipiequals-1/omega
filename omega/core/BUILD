load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library", "cc_test")
load(
    "//:copts.bzl",
    "DEFAULT_COPTS",
    "DEFAULT_LINKOPTS",
)

package(default_visibility= ["//visibility:public"])


cc_library(
    name = "using",
    hdrs = ["using.h"],
    copts = DEFAULT_COPTS,
    linkopts = DEFAULT_LINKOPTS,
    deps = [
        "@SDL2//:SDL2",
    ]
)

cc_library(
    name = "window",
    srcs = ["window.cpp"],
    hdrs = ["window.h"],
    copts = DEFAULT_COPTS,
    linkopts = DEFAULT_LINKOPTS,
    deps = [
        "@SDL2//:SDL2",
        "@GL//:GL",
        "//omega/core:using",
        "//omega/physics:math",
        ":viewport"
    ]
)

cc_library(
    name = "application",
    srcs = ["application.cpp"],
    hdrs = ["application.h"],
    copts = DEFAULT_COPTS,
    linkopts = DEFAULT_LINKOPTS,
    deps = [
        "@SDL2//:SDL2",
        ":using",
        ":window",
        "//omega/events:event",
        "//omega/events:input_manager",
    ]
)

cc_library(
    name = "orthographic_camera",
    srcs = ["orthographic_camera.cpp"],
    hdrs = ["orthographic_camera.h"],
    copts = DEFAULT_COPTS,
    linkopts = DEFAULT_LINKOPTS,
    deps = [
        "//omega/physics:math"
    ]
)

cc_library(
    name = "viewport",
    srcs = ["viewport.cpp"],
    hdrs = ["viewport.h"],
    copts = DEFAULT_COPTS,
    linkopts = DEFAULT_LINKOPTS,
    deps = [
        "@GL//:GL",
        "//omega/physics:math"
    ]
)