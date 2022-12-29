load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library", "cc_test")
load(
    "//:copts.bzl",
    "DEFAULT_COPTS",
    "DEFAULT_LINKOPTS",
)

package(default_visibility= ["//visibility:public"])

cc_library(
    name = "scene_hierarchy",
    srcs = ["scene_hierarchy.cpp"],
    hdrs = ["scene_hierarchy.h"],
    copts = DEFAULT_COPTS,
    linkopts = DEFAULT_LINKOPTS,
    deps = [
        "//omega/util:util",
        "//omega/scene:scene",
        "//omega/scene:entity",
        "//omega/scene:components",
        "//omega/vendor/imgui:imgui",
    ]
)

cc_library(
    name = "resource_panel",
    srcs = ["resource_panel.cpp"],
    hdrs = ["resource_panel.h"],
    copts = DEFAULT_COPTS,
    linkopts = DEFAULT_LINKOPTS,
    data = [
        "//editor/res/ui:ui"
    ],
    deps = [
        "//omega/util:util",
        "//omega/scene:scene",
        "//omega/vendor/imgui:imgui",
        "//omega/gfx:gfx",
        "//omega/gfx/texture:texture",
    ]
)
