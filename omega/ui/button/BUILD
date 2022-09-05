load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library", "cc_test")
load(
    "//:copts.bzl",
    "DEFAULT_COPTS",
    "DEFAULT_LINKOPTS",
)

package(default_visibility= ["//visibility:public"])

cc_library(
    name = "button",
    srcs = ["button.cpp"],
    hdrs = ["button.h"],
    copts = DEFAULT_COPTS,
    linkopts = DEFAULT_LINKOPTS,
    deps = [
        "//omega/util:util",
        "//omega/scene:entity",
        "//omega/gfx:sprite_batch",
    ]
)

cc_library(
    name = "image_button",
    srcs = ["image_button.cpp"],
    hdrs = ["image_button.h"],
    copts = DEFAULT_COPTS,
    linkopts = DEFAULT_LINKOPTS,
    deps = [
        ":button",
        "//omega/util:util",
        "//omega/gfx/texture:texture",
    ]
)

cc_library(
    name = "text_button",
    srcs = ["text_button.cpp"],
    hdrs = ["text_button.h"],
    copts = DEFAULT_COPTS,
    linkopts = DEFAULT_LINKOPTS,
    deps = [
        ":image_button",
        "//omega/util:util",
        "//omega/gfx/texture:texture",
        "//omega/ui:font",
    ]
)
