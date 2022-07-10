load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library", "cc_test")
load(
    "//:copts.bzl",
    "DEFAULT_COPTS",
    "DEFAULT_LINKOPTS",
)

package(default_visibility= ["//visibility:public"])

cc_library(
    name = "particle",
    srcs = ["particle.cpp"],
    hdrs = ["particle.h"],
    copts = DEFAULT_COPTS,
    linkopts = DEFAULT_LINKOPTS,
    deps = [
        "//libGL2D/physics:random",
        "//libGL2D/physics:math",
        "//libGL2D/core:using",
    ]
)

cc_library(
    name = "particle_emitter",
    srcs = ["particle_emitter.cpp"],
    hdrs = ["particle_emitter.h"],
    copts = DEFAULT_COPTS,
    linkopts = DEFAULT_LINKOPTS,
    deps = [
        "//libGL2D/gfx:shader",
        "//libGL2D/gfx/texture:texture",
        "//libGL2D/gfx:index_buffer",
        "//libGL2D/gfx:vertex_buffer",
        "//libGL2D/gfx:sprite_batch",
        "//libGL2D/gfx:vertex_array",
        "//libGL2D/gfx:vertex_buffer_layout",
        "//libGL2D/core:using",
        "//libGL2D/physics:random",
        "//libGL2D/physics:math",
        ":particle"
    ]
)
