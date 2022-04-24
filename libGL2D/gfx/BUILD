load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library", "cc_test")
load(
    "//:copts.bzl",
    "DEFAULT_COPTS",
    "DEFAULT_LINKOPTS",
)

package(default_visibility= ["//visibility:public"])

cc_library(
    name = "errors",
    srcs = ["errors.cc"],
    hdrs = ["errors.h"],
    copts = DEFAULT_COPTS,
    linkopts = DEFAULT_LINKOPTS,
    deps = [
        "@GL//:GL"
    ]
)

cc_library(
    name = "index_buffer",
    srcs = ["index_buffer.cc"],
    hdrs = ["index_buffer.h"],
    copts = DEFAULT_COPTS,
    linkopts = DEFAULT_LINKOPTS,
    deps = [
        "@GL//:GL",
    ]
)

cc_library(
    name = "shader",
    srcs = ["shader.cc"],
    hdrs = ["shader.h"],
    copts = DEFAULT_COPTS,
    linkopts = DEFAULT_LINKOPTS,
    deps = [
        "@GL//:GL",
        "//libGL2D/core:using",
        "//libGL2D/physics:math",
        "errors",
    ]
)

cc_library(
    name = "shape_renderer",
    srcs = ["shape_renderer.cc"],
    hdrs = ["shape_renderer.h"],
    copts = DEFAULT_COPTS,
    linkopts = DEFAULT_LINKOPTS,
    deps = [
        "@GL//:GL",
        ":shader",
        ":vertex_buffer",
        ":vertex_buffer_layout",
        ":vertex_array",
        "//libGL2D/core:using"
    ]
)

cc_library(
    name = "sprite_batch",
    srcs = ["sprite_batch.cc"],
    hdrs = ["sprite_batch.h"],
    copts = DEFAULT_COPTS,
    linkopts = DEFAULT_LINKOPTS,
    deps = [
        "@GL//:GL",
        ":shader",
        "//libGL2D/gfx/texture:texture",
        ":vertex_buffer",
        ":vertex_buffer_layout",
        ":vertex_array",
        ":index_buffer"
    ]
)

cc_library(
    name = "vertex_array",
    srcs = ["vertex_array.cc"],
    hdrs = ["vertex_array.h"],
    copts = DEFAULT_COPTS,
    linkopts = DEFAULT_LINKOPTS,
    deps = [
        "@GL//:GL",
        "vertex_buffer",
        "vertex_buffer_layout"
    ]
)

cc_library(
    name = "vertex_buffer",
    srcs = ["vertex_buffer.cc"],
    hdrs = ["vertex_buffer.h"],
    copts = DEFAULT_COPTS,
    linkopts = DEFAULT_LINKOPTS,
    deps = [
        "@GL//:GL",
    ]
)

cc_library(
    name = "vertex_buffer_layout",
    srcs = ["vertex_buffer_layout.cc"],
    hdrs = ["vertex_buffer_layout.h"],
    copts = DEFAULT_COPTS,
    linkopts = DEFAULT_LINKOPTS,
    deps = [
        "@GL//:GL",
    ]
)
