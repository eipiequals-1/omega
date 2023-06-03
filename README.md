# Omega
Omega is a lightweight game & multimedia framework.
It has only been tested on Unix based platforms and browsers, but should work with few modifications on a Windows based machine.
It is mainly intended to be used for 2D applications, but can be extended to 3D.

Omega uses OpenGL 4.5 as a rendering backend for desktop applications, and OpenGL ES 3.0 for web applications.

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
Clone the repository

`git clone https://www.github.com/eipiequals-1/omega --recursive`

`cd omega/`

Please install SDL2 before building. Refer to [SDL Docs](https://wiki.libsdl.org/SDL2/Installation) for step by step installation instructions.

Using CMake

`./configure.sh && ./build.sh`

This will create a shared object in __build/__

### License
Licensed under the MIT License. This means that no credit is required, but would be greatly appreciated!
