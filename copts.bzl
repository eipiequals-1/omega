GCC_FLAGS = [
    "-Wall",
    "-Wextra",
    "-Wcast-qual",
    "-Wconversion-null",
    "-Wformat-security",
    "-Wmissing-declarations",
    "-Woverlength-strings",
    "-Wpointer-arith",
    "-Wundef",
    "-Wunused-local-typedefs",
    "-Wunused-result",
    "-Wvarargs",
    "-Wvla",
    "-Wwrite-strings",
    "-DNOMINMAX",
    "-Werror",
    "-std=c++17",
    # Get easier to decode stack traces.
    "-fno-omit-frame-pointer ",
]

DEFAULT_COPTS = select({
    "//conditions:default": GCC_FLAGS,
})

DEFAULT_LINKOPTS = select({
    "//conditions:default": [],
})