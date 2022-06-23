load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library", "cc_test")
load(
    "//:copts.bzl",
    "DEFAULT_COPTS",
    "DEFAULT_LINKOPTS",
)

package(default_visibility= ["//visibility:public"])

cc_library(
    name = "button",
    srcs = ["button.cc"],
    hdrs = ["button.h"],
    copts = DEFAULT_COPTS,
    linkopts = DEFAULT_LINKOPTS,
    deps = [
        "//libGL2D/physics:math",
        "//libGL2D/physics:entity",
        "//libGL2D/gfx:sprite_batch",
    ]
)

cc_library(
    name = "image_button",
    srcs = ["image_button.cc"],
    hdrs = ["image_button.h"],
    copts = DEFAULT_COPTS,
    linkopts = DEFAULT_LINKOPTS,
    deps = [
        ":button",
        "//libGL2D/core:using",
        "//libGL2D/gfx/texture:texture",
    ]
)

cc_library(
    name = "text_button",
    srcs = ["text_button.cc"],
    hdrs = ["text_button.h"],
    copts = DEFAULT_COPTS,
    linkopts = DEFAULT_LINKOPTS,
    deps = [
        ":image_button",
        "//libGL2D/core:using",
        "//libGL2D/gfx/texture:texture",
        "//libGL2D/ui:font",
    ]
)
