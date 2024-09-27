#ifndef OMEGA_CORE_PLATFORM_HPP
#define OMEGA_CORE_PLATFORM_HPP

#ifdef EMSCRIPTEN

#include <GLES3/gl3.h>
#include <emscripten.h>

#define OMEGA_GL_MAJOR_VERSION 3
#define OMEGA_GL_MINOR_VERSION 0

#else

#include <glad/glad.h>

#define OMEGA_GL_MAJOR_VERSION 4
#define OMEGA_GL_MINOR_VERSION 5

#endif

#endif // OMEGA_CORE_PLATFORM_HPP
