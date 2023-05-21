#ifndef OMEGA_CORE_PLATFORM_HPP
#define OMEGA_CORE_PLATFORM_HPP

#ifdef EMSCRIPTEN

#include <emscripten.h>
#include <GLES3/gl3.h>

#else

#include "lib/glad/include/glad/glad.h"

#endif

#endif // OMEGA_CORE_PLATFORM_HPP
