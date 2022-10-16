load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library", "cc_test")
load(
    "//:copts.bzl",
    "DEFAULT_COPTS",
    "DEFAULT_LINKOPTS",
)

package(default_visibility= ["//visibility:public"])

filegroup(
    name = "res",
    srcs = glob([
        "*"
    ]),
)

cc_library(
    name = "editor_layer",
    srcs = ["editor_layer.cpp"],
    hdrs = ["editor_layer.h"],
    copts = DEFAULT_COPTS,
    linkopts = DEFAULT_LINKOPTS,
    deps = [
        "//omega/core:core",
        "//omega/util:util",
        "//omega/events:events",
        "//omega/scene:scene",
        "//omega/sound:sound",
        "//omega/gfx:gfx",
        "//omega/vendor/imgui:imgui"
    ]
)

cc_binary(
    name = "app",
    srcs = ["main.cpp"],
    copts = DEFAULT_COPTS,
    linkopts = DEFAULT_LINKOPTS,
    linkstatic = True,
    data = [
        ":res"
    ],
    deps = [
        ":editor_layer",
        "//omega/core:core",
        "//omega/sound:sound",
    ]
)
