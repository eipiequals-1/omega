#ifndef OMEGA_CORE_PLATFORM_HPP
#define OMEGA_CORE_PLATFORM_HPP

#ifdef EMSCRIPTEN

#include <GLES3/gl3.h>
#include <emscripten.h>

#else

#include <glad/glad.h>

#endif

#endif // OMEGA_CORE_PLATFORM_HPP
