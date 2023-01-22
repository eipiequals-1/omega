load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library", "cc_test")
load(
    "//:copts.bzl",
    "DEFAULT_COPTS",
    "DEFAULT_LINKOPTS",
)
package(default_visibility= ["//visibility:public"])


cc_library(
    name = "map",
    srcs = ["map.cpp"],
    hdrs = ["map.hpp"],
    copts = DEFAULT_COPTS,
    linkopts = DEFAULT_LINKOPTS,
    deps = [
        "@GL//:GL",
        "@SDL2//:SDL2",
        "//omega/util:util",
        "//omega/gfx:sprite_batch",
        "//lib/map:tmxparser",
    ]
)

cc_library(
    name = "map_renderer",
    srcs = ["map_renderer.cpp"],
    hdrs = ["map_renderer.hpp"],
    copts = DEFAULT_COPTS,
    linkopts = DEFAULT_LINKOPTS,
    deps = [
        "//omega/util:util",
        "//omega/gfx:sprite_batch",
        "//omega/gfx/texture:texture",
        ":map",
    ]
)
