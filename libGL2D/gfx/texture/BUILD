load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library", "cc_test", "cc_proto_library")

load(
    "//:copts.bzl",
    "DEFAULT_COPTS",
    "DEFAULT_LINKOPTS",
)

package(default_visibility= ["//visibility:public"])

cc_library(
    name = "texture",
    srcs = ["texture.cc"],
    hdrs = ["texture.h"],
    copts = DEFAULT_COPTS,
    linkopts = DEFAULT_LINKOPTS,
    deps = [
        "@SDL2//:SDL2",
        "@GL//:GL",
        "//libGL2D/gfx:errors",
        "//libGL2D/core:using",
    ]
)

cc_library(
    name = "texture_region",
    srcs = ["texture_region.cc"],
    hdrs = ["texture_region.h"],
    copts = DEFAULT_COPTS,
    linkopts = DEFAULT_LINKOPTS,
    deps = [
        "texture",
        "//libGL2D/physics:math",
    ]
)

cc_library(
    name = "texture_atlas",
    srcs = ["texture_atlas.cc"],
    hdrs = ["texture_atlas.h"],
    copts = DEFAULT_COPTS,
    linkopts = DEFAULT_LINKOPTS,
    deps = [
        "texture",
        "texture_region",
        "//libGL2D/core:using",
    ]
)

#cc_proto_library(
#    name = "texture_atlas_cc_proto",
#    deps = [":texture_atlas_proto"],
#)
#proto_library(
#    name = "texture_atlas_proto",
#    srcs = ["texture_atlas.proto"],
#)
