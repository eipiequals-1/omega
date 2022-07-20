load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library", "cc_test")
load(
    "//:copts.bzl",
    "DEFAULT_COPTS",
    "DEFAULT_LINKOPTS",
)

package(default_visibility= ["//visibility:public"])

cc_library(
    name = "imgui",
    srcs = glob([
        "*.cpp",
    ]),
    hdrs = glob([
        "*.h",
    ]),
    linkopts = [
        "-lGL",
        "-lGLU",
        "-lSDL2",
        "-lSDL2_image",
        "-ldl"
    ],
    copts = [
        "-I/usr/include/SDL2/"
    ],
    visibility = ["//visibility:public"],
)
