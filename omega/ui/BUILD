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
    hdrs = ["font.hpp"],
    copts = DEFAULT_COPTS,
    linkopts = DEFAULT_LINKOPTS,
    deps = [
        "@SDL2//:SDL2",
        "//omega/util:std",
        "//omega/util:log",
        "//omega/util:math",
        "//omega/gfx/texture:texture",
    ]
)

cc_library(
    name = "ui_screen",
    srcs = ["ui_screen.cpp"],
    hdrs = ["ui_screen.hpp"],
    copts = DEFAULT_COPTS,
    linkopts = DEFAULT_LINKOPTS,
    deps = [
        "//omega/events:input_manager",
        "//omega/util:math",
        "//omega/ui/button:button",
    ]
)

cc_library(
    name = "ui",
    hdrs = ["ui.hpp"],
    copts = DEFAULT_COPTS,
    linkopts = DEFAULT_LINKOPTS,
    deps = [
        ":font",
        ":ui_screen",
    ]
)
