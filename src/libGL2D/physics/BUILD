load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library", "cc_test")
load(
    "//:copts.bzl",
    "DEFAULT_COPTS",
    "DEFAULT_LINKOPTS",
)

package(default_visibility= ["//visibility:public"])

cc_library(
    name = "random",
    srcs = ["random.cc"],
    hdrs = ["random.h"],
    copts = DEFAULT_COPTS,
    linkopts = DEFAULT_LINKOPTS,
)

cc_library(
    name = "math",
    srcs = ["math.cc"],
    hdrs = ["math.h"],
    copts = DEFAULT_COPTS,
    linkopts = DEFAULT_LINKOPTS,
)

cc_library(
    name = "entity",
    srcs = ["entity.cc"],
    hdrs = ["entity.h"],
    copts = DEFAULT_COPTS,
    linkopts = DEFAULT_LINKOPTS,
    deps = [
        "//src/libGL2D/gfx:sprite_batch",
        "//src/libGL2D/gfx/texture:texture",
        "//src/libGL2D/events:input_processor",
    ]
)
