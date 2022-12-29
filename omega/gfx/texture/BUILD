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
    hdrs = ["texture.h"],
    copts = DEFAULT_COPTS,
    linkopts = DEFAULT_LINKOPTS,
    deps = [
        "@SDL2//:SDL2",
        "@GL//:GL",
        "//omega/util:std",
        "//omega/util:log",
    ]
)

cc_library(
    name = "texture_region",
    hdrs = ["texture_region.h"],
    copts = DEFAULT_COPTS,
    linkopts = DEFAULT_LINKOPTS,
    deps = [
        "texture",
        "//omega/util:math",
    ]
)

cc_library(
    name = "texture_atlas",
    srcs = ["texture_atlas.cpp"],
    hdrs = ["texture_atlas.h"],
    copts = DEFAULT_COPTS,
    linkopts = DEFAULT_LINKOPTS,
    deps = [
        "@GL//:GL",
        "texture",
        "texture_region",
        "//omega/util:util",
    ]
)
