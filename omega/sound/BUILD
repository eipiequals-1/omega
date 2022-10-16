load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library", "cc_test")
load(
    "//:copts.bzl",
    "DEFAULT_COPTS",
    "DEFAULT_LINKOPTS",
)

package(default_visibility= ["//visibility:public"])

cc_library(
    name = "music",
    srcs = ["music.cpp"],
    hdrs = ["music.h"],
    copts = DEFAULT_COPTS,
    linkopts = DEFAULT_LINKOPTS,
    deps = [
        "@SDL2//:SDL2",
        "//omega/util:util"
    ]
)

cc_library(
    name = "sound_effect",
    srcs = ["sound_effect.cpp"],
    hdrs = ["sound_effect.h"],
    copts = DEFAULT_COPTS,
    linkopts = DEFAULT_LINKOPTS,
    deps = [
        "@SDL2//:SDL2",
        "//omega/util:util"
    ]
)

cc_library(
    name = "sound_manager",
    srcs = ["sound_manager.cpp"],
    hdrs = ["sound_manager.h"],
    copts = DEFAULT_COPTS,
    linkopts = DEFAULT_LINKOPTS,
    deps = [
        "@SDL2//:SDL2",
        "//omega/util:util",
        ":music",
        ":sound_effect",
    ]
)


cc_library(
    name = "sound",
    hdrs = ["sound.h"],
    copts = DEFAULT_COPTS,
    linkopts = DEFAULT_LINKOPTS,
    deps = [
        ":music",
        ":sound_effect",
        ":sound_manager",
    ]
)
