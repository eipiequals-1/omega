load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library", "cc_test")
load(
    "//:copts.bzl",
    "DEFAULT_COPTS",
    "DEFAULT_LINKOPTS",
)
package(default_visibility= ["//visibility:public"])

cc_library(
    name = "base64",
    srcs = ["base64.cpp"],
    hdrs = ["base64.h"],
    copts = DEFAULT_COPTS,
    linkopts = DEFAULT_LINKOPTS,
)

cc_library(
    name = "tmxparser",
    srcs = ["tmxparser.cpp"],
    hdrs = ["tmxparser.h"],
    deps = ["base64"],
    linkopts = [
        "-ltinyxml2"
    ],
)

cc_library(
    name = "tiled",
    srcs = ["tiled.cpp"],
    hdrs = ["tiled.h"],
    copts = DEFAULT_COPTS,
    linkopts = DEFAULT_LINKOPTS,
    deps = [
        "@GL//:GL",
        "@SDL2//:SDL2",
        "//libGL2D/core:using",
        "//libGL2D/gfx:sprite_batch",
        "//libGL2D/physics:math",
        ":tmxparser",
    ]
)

cc_library(
    name = "map_renderer",
    srcs = ["map_renderer.cpp"],
    hdrs = ["map_renderer.h"],
    copts = DEFAULT_COPTS,
    linkopts = DEFAULT_LINKOPTS,
    deps = [
        "//libGL2D/core:using",
        "//libGL2D/gfx:sprite_batch",
        "//libGL2D/gfx/texture:texture",
        ":tiled",
    ]
)
