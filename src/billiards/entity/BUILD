load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library", "cc_test")
load(
    "//:copts.bzl",
    "DEFAULT_COPTS",
    "DEFAULT_LINKOPTS",
)

package(default_visibility= ["//visibility:public"])

cc_library(
    name = "ball",
    srcs = ["ball.cc"],
    hdrs = ["ball.h"],
    copts = DEFAULT_COPTS,
    linkopts = DEFAULT_LINKOPTS,
    deps = [
        "//src/libGL2D/events:input_processor",
        "//src/libGL2D/gfx:sprite_batch",
        "//src/libGL2D/gfx/texture:texture",
        "//src/billiards:game_data",
        "sprite"
    ]
)

cc_library(
    name = "table",
    srcs = ["table.cc"],
    hdrs = ["table.h"],
    copts = DEFAULT_COPTS,
    linkopts = DEFAULT_LINKOPTS,
    deps = [
        "//src/libGL2D/gfx/texture:texture",
        "sprite"
    ]
)

cc_library(
    name = "hole",
    srcs = ["hole.cc"],
    hdrs = ["hole.h"],
    copts = DEFAULT_COPTS,
    linkopts = DEFAULT_LINKOPTS,
    deps = [
        "//src/libGL2D/physics:math"
    ]
)

cc_library(
    name = "sprite",
    srcs = ["sprite.cc"],
    hdrs = ["sprite.h"],
    copts = DEFAULT_COPTS,
    linkopts = DEFAULT_LINKOPTS,
        data = [
        "//res/shader:shaders",
    ],
    deps = [
        "//src/libGL2D/gfx/texture:texture",
        "//src/libGL2D/events:input_processor",
        "//src/libGL2D/physics:math",
        "//src/libGL2D/core:using",
        "//src/libGL2D/gfx:sprite_batch"
    ]
)