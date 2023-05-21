load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library", "cc_test")
load(
    "//:copts.bzl",
    "DEFAULT_COPTS",
    "DEFAULT_LINKOPTS",
)

package(default_visibility= ["//visibility:public"])

cc_library(
    name = "glm",
    hdrs = glob([
        "*.hpp",
        "*.h",
        "**/*.hpp",
        "**/*.h",
    ]),
    textual_hdrs = glob([
        "**/*.inl"
    ]),
    visibility = ["//visibility:public"],
)
