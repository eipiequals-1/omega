load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library", "cc_test")
load(
    "//:copts.bzl",
    "DEFAULT_COPTS",
    "DEFAULT_LINKOPTS",
)

package(default_visibility= ["//visibility:public"])

cc_library(
    name = "camera",
    hdrs = ["camera.hpp"],
    copts = DEFAULT_COPTS,
    linkopts = DEFAULT_LINKOPTS,
    deps = [
        "//omega/util:util",
    ]
)

cc_library(
    name = "layer",
    hdrs = ["layer.hpp"],
    copts = DEFAULT_COPTS,
    linkopts = DEFAULT_LINKOPTS,
    deps = [
    ]
)

cc_library(
    name = "layer_stack",
    srcs = ["layer_stack.cpp"],
    hdrs = ["layer_stack.hpp"],
    copts = DEFAULT_COPTS,
    linkopts = DEFAULT_LINKOPTS,
    deps = [
        ":layer",
    ]
)

cc_library(
    name = "imgui_layer",
    srcs = ["imgui_layer.cpp"],
    hdrs = ["imgui_layer.hpp"],
    copts = DEFAULT_COPTS,
    linkopts = DEFAULT_LINKOPTS,
    deps = [
        "//omega/core:window",
        "//omega/events:event",
        "//lib/imgui:imgui",
        ":layer",
    ]
)

cc_library(
    name = "imgui",
    srcs = ["imgui.cpp"],
    hdrs = ["imgui.hpp"],
    copts = DEFAULT_COPTS,
    linkopts = DEFAULT_LINKOPTS,
    deps = [
        "//lib/imgui:imgui",
    ]
)

cc_library(
    name = "entity",
    hdrs = ["entity.hpp"],
    copts = DEFAULT_COPTS,
    linkopts = DEFAULT_LINKOPTS,
    deps = [
        "//lib/entt:entt",
    ]
)

cc_library(
    name = "components",
    hdrs = ["components.hpp"],
    copts = DEFAULT_COPTS,
    linkopts = DEFAULT_LINKOPTS,
    deps = [
        "//omega/gfx/texture:texture",
        "//omega/util:math",
        "//omega/util:std",
        ":orthographic_camera",
        ":perspective_camera",
    ]
)

cc_library(
    name = "model",
    hdrs = ["model.hpp"],
    srcs = ["model.cpp"],
    copts = DEFAULT_COPTS,
    linkopts = DEFAULT_LINKOPTS,
    deps = [
        "@assimp//:assimp",
        "//omega/gfx/texture:texture",
        "//omega/gfx/texture:mesh",
        "//omega/gfx:shader",
        "//omega/util:math",
        "//omega/util:std",
    ]
)

cc_library(
    name = "orthographic_camera",
    srcs = ["orthographic_camera.cpp"],
    hdrs = ["orthographic_camera.hpp"],
    copts = DEFAULT_COPTS,
    linkopts = DEFAULT_LINKOPTS,
    deps = [
        ":camera",
        "//omega/util:math",
    ]
)

cc_library(
    name = "perspective_camera",
    srcs = ["perspective_camera.cpp"],
    hdrs = ["perspective_camera.hpp"],
    copts = DEFAULT_COPTS,
    linkopts = DEFAULT_LINKOPTS,
    deps = [
        ":camera",
        "//omega/util:math",
    ]
)

cc_library(
    name = "scene",
    hdrs = ["scene.hpp"],
    srcs = ["scene.cpp"],
    copts = DEFAULT_COPTS,
    linkopts = DEFAULT_LINKOPTS,
    deps = [
        "//lib/entt:entt",
        "//omega/core:viewport",
        "//omega/gfx:sprite_batch",
        "//omega/gfx:gl",
        "//omega/util:color",
        "//omega/util:math",
        
        ":components",
        ":entity",
    ]
)
