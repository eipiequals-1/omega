load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library", "cc_test")
load(
    "//:copts.bzl",
    "DEFAULT_COPTS",
    "DEFAULT_LINKOPTS",
)

package(default_visibility= ["//visibility:public"])


cc_library(
    name = "sdl",
    hdrs = ["sdl.h"],
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
        "//omega/util:util",
        ":viewport",
        ":sdl2"
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
        "//omega/util:util",
        ":window",
        "//omega/scene:scene",
        "//omega/events:events",
    ]
)

cc_library(
    name = "sdl2",
    hdrs = ["sdl2.h"],
    copts = DEFAULT_COPTS,
    linkopts = DEFAULT_LINKOPTS,
    deps = [
        "@SDL2//:SDL2",
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
        "//omega/util:util"
    ]
)

cc_library(
    name = "core",
    hdrs = ["core.h"],
    copts = DEFAULT_COPTS,
    linkopts = DEFAULT_LINKOPTS,
    deps = [
        ":application",
        ":sdl2",
        ":viewport",
        ":window",
    ]
)
