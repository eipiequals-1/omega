load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library", "cc_test")
load(
    "//:copts.bzl",
    "DEFAULT_COPTS",
    "DEFAULT_LINKOPTS",
)

package(default_visibility= ["//visibility:public"])

cc_library(
    name = "frame_buffer",
    srcs = ["frame_buffer.cpp"],
    hdrs = ["frame_buffer.h"],
    copts = DEFAULT_COPTS,
    linkopts = DEFAULT_LINKOPTS,
    deps = [
        "@GL//:GL",
        "//omega/util:util",
        "//omega/gfx/texture:texture",
        ":gl",
    ]
)

cc_library(
    name = "gl",
    hdrs = ["gl.h"],
    copts = DEFAULT_COPTS,
    linkopts = DEFAULT_LINKOPTS,
    deps = [
        "@GL//:GL",
        "//omega/util:math",
    ]
)

cc_library(
    name = "index_buffer",
    srcs = ["index_buffer.cpp"],
    hdrs = ["index_buffer.h"],
    copts = DEFAULT_COPTS,
    linkopts = DEFAULT_LINKOPTS,
    deps = [
        "@GL//:GL",
        "//omega/util:util"
    ]
)

cc_library(
    name = "shader",
    srcs = ["shader.cpp"],
    hdrs = ["shader.h"],
    copts = DEFAULT_COPTS,
    linkopts = DEFAULT_LINKOPTS,
    deps = [
        "@GL//:GL",
        "//omega/util:util",
    ]
)

cc_library(
    name = "shape_renderer",
    srcs = ["shape_renderer.cpp"],
    hdrs = ["shape_renderer.h"],
    copts = DEFAULT_COPTS,
    linkopts = DEFAULT_LINKOPTS,
    deps = [
        "@GL//:GL",
        ":shader",
        ":vertex_buffer",
        ":vertex_buffer_layout",
        ":vertex_array",
        "//omega/util:util",
    ]
)

cc_library(
    name = "sprite_batch",
    srcs = ["sprite_batch.cpp"],
    hdrs = ["sprite_batch.h"],
    copts = DEFAULT_COPTS,
    linkopts = DEFAULT_LINKOPTS,
    deps = [
        "@GL//:GL",
        ":shader",
        "//omega/gfx/texture:texture",
        "//omega/gfx/texture:texture_region",
        ":vertex_buffer",
        ":vertex_buffer_layout",
        ":vertex_array",
        ":index_buffer",
    ]
)

cc_library(
    name = "vertex_array",
    srcs = ["vertex_array.cpp"],
    hdrs = ["vertex_array.h"],
    copts = DEFAULT_COPTS,
    linkopts = DEFAULT_LINKOPTS,
    deps = [
        "@GL//:GL",
        "vertex_buffer",
        "vertex_buffer_layout",
        "//omega/util:util",
    ]
)

cc_library(
    name = "vertex_buffer",
    srcs = ["vertex_buffer.cpp"],
    hdrs = ["vertex_buffer.h"],
    copts = DEFAULT_COPTS,
    linkopts = DEFAULT_LINKOPTS,
    deps = [
        "@GL//:GL",
        "//omega/util:util",
    ]
)

cc_library(
    name = "vertex_buffer_layout",
    srcs = ["vertex_buffer_layout.cpp"],
    hdrs = ["vertex_buffer_layout.h"],
    copts = DEFAULT_COPTS,
    linkopts = DEFAULT_LINKOPTS,
    deps = [
        "@GL//:GL",
        "//omega/util:util"
    ]
)

cc_library(
    name = "gfx",
    hdrs = ["gfx.h"],
    copts = DEFAULT_COPTS,
    linkopts = DEFAULT_LINKOPTS,
    deps = [
        ":frame_buffer",
        ":gl",
        ":index_buffer",
        ":shader",
        ":shape_renderer",
        ":sprite_batch",
        ":vertex_array",
        ":vertex_buffer",
        ":vertex_buffer_layout",
    ]
)
