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
    hdrs = ["particle.hpp"],
    copts = DEFAULT_COPTS,
    linkopts = DEFAULT_LINKOPTS,
    deps = [
        "//omega/util:math",
        "//omega/util:random",
    ]
)

cc_library(
    name = "particle_emitter",
    srcs = ["particle_emitter.cpp"],
    hdrs = ["particle_emitter.hpp"],
    copts = DEFAULT_COPTS,
    linkopts = DEFAULT_LINKOPTS,
    deps = [
        "//omega/gfx:shader",
        "//omega/gfx/texture:texture",
        "//omega/gfx:index_buffer",
        "//omega/gfx:vertex_buffer",
        "//omega/gfx:sprite_batch",
        "//omega/gfx:vertex_array",
        "//omega/gfx:vertex_buffer_layout",
        "//omega/util:math",
        "//omega/util:std",
        ":particle"
    ]
)
