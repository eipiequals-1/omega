load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library", "cc_test", "cc_proto_library")

load(
    "//:copts.bzl",
    "DEFAULT_COPTS",
    "DEFAULT_LINKOPTS",
)

package(default_visibility= ["//visibility:public"])


cc_library(
    name = "texture",
    srcs = ["texture.cpp"],
    hdrs = ["texture.hpp"],
    copts = DEFAULT_COPTS,
    linkopts = DEFAULT_LINKOPTS,
    deps = [
        "@SDL2//:SDL2",
        "//omega/gfx:gl",
        "//omega/util:std",
        "//omega/util:log",
        "//lib/stb:stb_image"
    ]
)

cc_library(
    name = "texture_region",
    hdrs = ["texture_region.hpp"],
    copts = DEFAULT_COPTS,
    linkopts = DEFAULT_LINKOPTS,
    deps = [
        ":texture",
        "//omega/util:math",
    ]
)

cc_library(
    name = "texture_atlas",
    srcs = ["texture_atlas.cpp"],
    hdrs = ["texture_atlas.hpp"],
    copts = DEFAULT_COPTS,
    linkopts = DEFAULT_LINKOPTS,
    deps = [
        ":texture",
        ":texture_region",
        "//omega/util:util",
    ]
)
