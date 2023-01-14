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
    "-std=c++20",
    # Get easier to decode stack traces.
    "-fno-omit-frame-pointer ",
    "-pg",
    "-g",
    "-I."
]

DEFAULT_COPTS = select({
    "//conditions:default": GCC_FLAGS,
})

DEFAULT_LINKOPTS = select({
    "//conditions:default": ["-pg", "-g"],
})
