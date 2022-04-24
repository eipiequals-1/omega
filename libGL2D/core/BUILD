load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library", "cc_test")
load(
    "//:copts.bzl",
    "DEFAULT_COPTS",
    "DEFAULT_LINKOPTS",
)

package(default_visibility= ["//visibility:public"])


cc_library(
    name = "using",
    hdrs = ["using.h"],
    copts = DEFAULT_COPTS,
    linkopts = DEFAULT_LINKOPTS,
    deps = [
        "@SDL2//:SDL2",
    ]
)

cc_library(
    name = "window",
    srcs = ["window.cc"],
    hdrs = ["window.h"],
    copts = DEFAULT_COPTS,
    linkopts = DEFAULT_LINKOPTS,
    deps = [
        "@SDL2//:SDL2",
        "//libGL2D/core:using",
        "//libGL2D/physics:math"
    ]
)

cc_library(
    name = "application",
    srcs = ["application.cc"],
    hdrs = ["application.h"],
    copts = DEFAULT_COPTS,
    linkopts = DEFAULT_LINKOPTS,
    deps = [
        "@SDL2//:SDL2",
        "//libGL2D/core:window",
        "//libGL2D/core:using",
    ]
)

cc_library(
    name = "ortho_camera",
    srcs = ["ortho_camera.cc"],
    hdrs = ["ortho_camera.h"],
    copts = DEFAULT_COPTS,
    linkopts = DEFAULT_LINKOPTS,
    deps = [
        "//libGL2D/physics:math"
    ]
)