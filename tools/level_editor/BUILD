load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library", "cc_test")
load(
    "//:copts.bzl",
    "DEFAULT_COPTS",
    "DEFAULT_LINKOPTS",
)

package(default_visibility= ["//visibility:public"])

cc_binary(
    name = "level_editor",
    srcs = ["level_editor.cpp"],
    copts = DEFAULT_COPTS,
    linkopts = DEFAULT_LINKOPTS,
    deps = [
        "//lib/entt:entt",
        "//omega/core:core",
        "//omega/gfx:gfx",
        "//omega/gfx:gl",
        "//omega/util:color",
        "//omega/util:math",
        "//omega/scene:imgui",

        ":scene"
    ]
)

cc_library(
    name = "scene",
    srcs = ["scene.cpp"],
    hdrs = ["scene.hpp"],
    copts = DEFAULT_COPTS,
    linkopts = DEFAULT_LINKOPTS,
    deps = [
        "//omega/gfx:gfx",
        "//omega/gfx:frame_buffer",
        "//omega/gfx:gl",
        "//omega/scene:orthographic_camera",
        "//omega/scene:imgui",
        "//omega/util:std"
    ]
)
