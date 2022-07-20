load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library", "cc_test")
load(
    "//:copts.bzl",
    "DEFAULT_COPTS",
    "DEFAULT_LINKOPTS",
)

package(default_visibility= ["//visibility:public"])

cc_library(
    name = "editor",
    srcs = ["editor.cpp"],
    hdrs = ["editor.h"],
    copts = DEFAULT_COPTS,
    linkopts = DEFAULT_LINKOPTS,
    deps = [
        "//omega/core:using",
        "//omega/core:application",
        "//omega/core:orthographic_camera",
        "//omega/events:event",
        "//omega/events:input_manager",
        "//omega/scene:imgui_layer",
        "//omega/gfx:errors",
        "//omega/gfx:shape_renderer",
        "//omega/gfx:sprite_batch",
        "//omega/gfx:frame_buffer",
    ]
)

cc_binary(
    name = "app",
    srcs = ["main.cpp"],
    copts = DEFAULT_COPTS,
    linkopts = DEFAULT_LINKOPTS,
    linkstatic = True,
    deps = [
        ":editor"
    ]
)
