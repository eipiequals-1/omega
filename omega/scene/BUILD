load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library", "cc_test")
load(
    "//:copts.bzl",
    "DEFAULT_COPTS",
    "DEFAULT_LINKOPTS",
)

package(default_visibility= ["//visibility:public"])

cc_library(
    name = "layer",
    srcs = ["layer.cpp"],
    hdrs = ["layer.h"],
    copts = DEFAULT_COPTS,
    linkopts = DEFAULT_LINKOPTS,
    deps = [
        "//omega/core:using",
    ]
)

cc_library(
    name = "layer_stack",
    srcs = ["layer_stack.cpp"],
    hdrs = ["layer_stack.h"],
    copts = DEFAULT_COPTS,
    linkopts = DEFAULT_LINKOPTS,
    deps = [
        ":layer",
    ]
)

cc_library(
    name = "imgui_layer",
    srcs = ["imgui_layer.cpp"],
    hdrs = ["imgui_layer.h"],
    copts = DEFAULT_COPTS,
    linkopts = DEFAULT_LINKOPTS,
    deps = [
        "//omega/core:window",
        "//omega/events:event",
        ":layer",
        "//omega/vendor/imgui:imgui",
    ]
)

cc_library(
    name = "entity",
    srcs = ["entity.cpp"],
    hdrs = ["entity.h"],
    copts = DEFAULT_COPTS,
    linkopts = DEFAULT_LINKOPTS,
    deps = [
        ":components"
    ]
)

cc_library(
    name = "components",
    srcs = ["components.cpp"],
    hdrs = ["components.h"],
    copts = DEFAULT_COPTS,
    linkopts = DEFAULT_LINKOPTS,
    deps = [
        "//omega/gfx/texture:texture",
        "//omega/gfx:sprite_batch",
        "//omega/physics:math",
    ]
)