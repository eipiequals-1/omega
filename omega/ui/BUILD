load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library", "cc_test")
load(
    "//:copts.bzl",
    "DEFAULT_COPTS",
    "DEFAULT_LINKOPTS",
)

package(default_visibility= ["//visibility:public"])

cc_library(
    name = "font",
    srcs = ["font.cpp"],
    hdrs = ["font.h"],
    copts = DEFAULT_COPTS,
    linkopts = DEFAULT_LINKOPTS,
    deps = [
        "@SDL2//:SDL2",
        "//omega/util:util",
        "//omega/gfx/texture:texture",
    ]
)

cc_library(
    name = "ui_screen",
    srcs = ["ui_screen.cpp"],
    hdrs = ["ui_screen.h"],
    copts = DEFAULT_COPTS,
    linkopts = DEFAULT_LINKOPTS,
    deps = [
        "//omega/events:input_processor",
        "//omega/util:util",
        "//omega/ui/button:button",
    ]
)

cc_library(
    name = "ui",
    hdrs = ["ui.h"],
    copts = DEFAULT_COPTS,
    linkopts = DEFAULT_LINKOPTS,
    deps = [
        ":font",
        ":ui_screen",
    ]
)
