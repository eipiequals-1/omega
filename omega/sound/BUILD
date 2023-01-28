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
    hdrs = ["music.hpp"],
    copts = DEFAULT_COPTS,
    linkopts = DEFAULT_LINKOPTS,
    deps = [
        "@SDL2//:SDL2",
        "//omega/util:log"
    ]
)

cc_library(
    name = "sound_effect",
    srcs = ["sound_effect.cpp"],
    hdrs = ["sound_effect.hpp"],
    copts = DEFAULT_COPTS,
    linkopts = DEFAULT_LINKOPTS,
    deps = [
        "@SDL2//:SDL2",
        "//omega/util:log"
    ]
)


cc_library(
    name = "sound",
    hdrs = ["sound.hpp"],
    copts = DEFAULT_COPTS,
    linkopts = DEFAULT_LINKOPTS,
    deps = [
        ":music",
        ":sound_effect",
    ]
)
