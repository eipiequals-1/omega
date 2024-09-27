# Omega

Omega is a lightweight game & multimedia framework.
It has only been tested on Unix based platforms and browsers, but should work with few modifications on a Windows based machine.
It is a 2D framework with 3D support and a sprite, shape, deferred, and instance renderer.

Omega uses OpenGL 4.5 as a rendering backend for desktop applications, and OpenGL ES 3.0 for web applications.
Desktop applications have full geometry shader support, and web support is to be used for 2D game jams and demos.

### Dependencies

- [SDL2](https://www.libsdl.org/)
- [stb](https://github.com/nothings/stb)
- [Dear Imgui](https://github.com/ocornut/imgui)
- [glm](https://github.com/g-truc/glm)
- [box2d](https://github.com/erincatto/box2d)
- [nlohmann/json](https://github.com/nlohmann/json)
- [entt](https://github.com/skypjack/entt)
- [glad](https://github.com/Dav1dde/glad)
- [libtmx-parser](https://github.com/halsafar/libtmx-parser)

### Building

Please install SDL2 before building. Refer to [SDL Docs](https://wiki.libsdl.org/SDL2/Installation) for step by step installation instructions.

Clone the repository including all the submodules:

`git clone https://www.github.com/eipiequals-1/omega --recursive`

`cd omega/`

#### Unix

Using CMake and GNU Make

`./configure.sh && ./build.sh`

This will create a shared object in **build/**

#### Web

Install the [emscripten SDK](https://emscripten.org/docs/getting_started/downloads.html) beforehand.

Run from the **omega** project root:

`emconfigure ./configure.sh`

`cd build/ && emmake make && cd ..`

Next, see **jam/** for a project setup example and the corresponding Makefile that can be modified.

### License

Licensed under the MIT License. This means that no credit is required, but would be greatly appreciated!
