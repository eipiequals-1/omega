load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library", "cc_test")
load(
    "//:copts.bzl",
    "DEFAULT_COPTS",
    "DEFAULT_LINKOPTS",
)

package(default_visibility= ["//visibility:public"])

cc_library(
    name = "globals",
    hdrs = ["globals.hpp"],
    copts = DEFAULT_COPTS,
    linkopts = DEFAULT_LINKOPTS,
    deps = [
        "//omega/gfx:sprite_batch",
        "//omega/gfx:shape_renderer",
        "//omega/scene:scene",
        "//omega/util:asset_manager",
        ":viewport",
    ]
)

cc_library(
    name = "window",
    srcs = ["window.cpp"],
    hdrs = ["window.hpp"],
    copts = DEFAULT_COPTS,
    linkopts = DEFAULT_LINKOPTS,
    deps = [
        "@SDL2//:SDL2",
        "//omega/gfx:gl",
        "//omega/util:std",
        "//omega/util:log",
        ":viewport",
        ":sdl2"
    ]
)

cc_library(
    name = "app",
    srcs = ["app.cpp"],
    hdrs = ["app.hpp"],
    copts = DEFAULT_COPTS,
    linkopts = DEFAULT_LINKOPTS,
    deps = [
        "@SDL2//:SDL2",
        "//omega/util:math",
        "//omega/util:log",
        "//omega/util:std",
        "//omega/util:time",
        ":window",
        ":globals",
        "//omega/events:events",
    ]
)

cc_library(
    name = "sdl2",
    hdrs = ["sdl2.hpp"],
    copts = DEFAULT_COPTS,
    linkopts = DEFAULT_LINKOPTS,
    deps = [
        "@SDL2//:SDL2",
    ]
)

cc_library(
    name = "viewport",
    srcs = ["viewport.cpp"],
    hdrs = ["viewport.hpp"],
    copts = DEFAULT_COPTS,
    linkopts = DEFAULT_LINKOPTS,
    deps = [
        "//omega/gfx:gl",
        "//omega/util:math"
    ]
)

cc_library(
    name = "core",
    hdrs = ["core.hpp"],
    copts = DEFAULT_COPTS,
    linkopts = DEFAULT_LINKOPTS,
    deps = [
        ":app",
        ":globals",
        ":sdl2",
        ":viewport",
        ":window",
    ]
)
