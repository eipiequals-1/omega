load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library", "cc_test")
load(
    "//:copts.bzl",
    "DEFAULT_COPTS",
    "DEFAULT_LINKOPTS",
)

package(default_visibility= ["//visibility:public"])

cc_library(
    name = "billiards",
    srcs = ["billiards.cc"],
    hdrs = ["billiards.h"],
    copts = DEFAULT_COPTS,
    linkopts = DEFAULT_LINKOPTS,
    data = [
        "//res/shader:shaders",
        "//res/gfx:images"
    ],
    deps = [
        "@GL//:GL",
        "@SDL2//:SDL2",
        "//src/libGL2D/core:application",
        "gamescreen",
        "game_data"
    ]
)

cc_library(
    name = "game_data",
    srcs = ["game_data.cc"],
    hdrs = ["game_data.h"],
    copts = DEFAULT_COPTS,
    linkopts = DEFAULT_LINKOPTS,
    deps = [
        "//src/libGL2D/core:using",
        "//src/libGL2D/events:input_processor",
        "//src/libGL2D/gfx:sprite_batch",
    ]
)

cc_library(
    name = "gamescreen",
    srcs = ["gamescreen.cc"],
    hdrs = ["gamescreen.h"],
    copts = DEFAULT_COPTS,
    linkopts = DEFAULT_LINKOPTS,
    data = [
        "//res/fnt:fonts"
    ],
    deps = [
        "@SDL2//:SDL2",
        "@GL//:GL",
        "//src/libGL2D/core:using",
        "//src/libGL2D/events:input_processor",
        "//src/libGL2D/physics:random",
        "//src/libGL2D/physics:math",
        "//src/libGL2D/gfx:sprite_batch",
        "//src/libGL2D/gfx:font",
        "//src/libGL2D/gfx/texture:texture",
        "//src/billiards/entity:ball",
        "//src/billiards/entity:table",
        "//src/billiards/entity:hole",
    ]
)