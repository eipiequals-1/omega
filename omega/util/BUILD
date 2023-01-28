load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library", "cc_test")
load(
    "//:copts.bzl",
    "DEFAULT_COPTS",
    "DEFAULT_LINKOPTS",
)

package(default_visibility= ["//visibility:public"])

cc_library(
    name = "asset_manager",
    srcs = ["asset_manager.cpp"],
    hdrs = ["asset_manager.hpp"],
    copts = DEFAULT_COPTS,
    linkopts = DEFAULT_LINKOPTS,
    deps = [
        ":log",
        "//omega/sound:music",
        "//omega/sound:sound_effect",
        "//omega/gfx/texture:texture",
        "@SDL2//:SDL2",
    ]
)

cc_library(
    name = "color",
    hdrs = ["color.hpp"],
    copts = DEFAULT_COPTS,
    linkopts = DEFAULT_LINKOPTS,
)

cc_library(
    name = "log",
    hdrs = ["log.hpp"],
    copts = DEFAULT_COPTS,
    linkopts = DEFAULT_LINKOPTS,
)

cc_library(
    name = "math",
    srcs = ["math.cpp"],
    hdrs = ["math.hpp"],
    copts = DEFAULT_COPTS,
    linkopts = DEFAULT_LINKOPTS,
)

cc_library(
    name = "random",
    hdrs = ["random.hpp"],
    copts = DEFAULT_COPTS,
    linkopts = DEFAULT_LINKOPTS,
)

cc_library(
    name = "std",
    hdrs = ["std.hpp"],
    copts = DEFAULT_COPTS,
    linkopts = DEFAULT_LINKOPTS,
)

cc_library(
    name = "time",
    srcs = ["time.cpp"],
    hdrs = ["time.hpp"],
    copts = DEFAULT_COPTS,
    linkopts = DEFAULT_LINKOPTS,
    deps = [
        ":std",
        "@SDL2//:SDL2",
    ]
)

cc_library(
    name = "util",
    hdrs = ["util.hpp"],
    copts = DEFAULT_COPTS,
    linkopts = DEFAULT_LINKOPTS,
    deps = [
        ":color",
        ":log",
        ":math",
        ":std",
        ":random",
        ":time",
    ]
)
