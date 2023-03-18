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
        "//lib/imgui:imgui",
        "//omega/core:core",
        "//omega/gfx:gfx",
        "//omega/gfx:gl",
        "//omega/util:color",
        "//omega/util:math",
    ]
)
