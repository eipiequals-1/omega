load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library", "cc_test")
load(
    "//:copts.bzl",
    "DEFAULT_COPTS",
    "DEFAULT_LINKOPTS",
)

package(default_visibility= ["//visibility:public"])

cc_library(
    name = "font",
    srcs = ["font.cc"],
    hdrs = ["font.h"],
    copts = DEFAULT_COPTS,
    linkopts = DEFAULT_LINKOPTS,
    deps = [
        "@SDL2//:SDL2",
        "//libGL2D/core:using",
        "//libGL2D/physics:math",
        "//libGL2D/gfx/texture:texture",
    ]
)

cc_library(
    name = "ui_screen",
    srcs = ["ui_screen.cc"],
    hdrs = ["ui_screen.h"],
    copts = DEFAULT_COPTS,
    linkopts = DEFAULT_LINKOPTS,
    deps = [
        "//libGL2D/events:input_processor",
        "//libGL2D/physics:math",
        "//libGL2D/ui/button:button",
    ]
)
