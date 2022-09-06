#include "errors.h"

#include <GL/gl.h>
#include <GL/glu.h>

#include <iostream>

namespace omega::gfx {

bool glCheckError() {
    int count = 0;
    GLenum error = glGetError();
    while (error != GL_NO_ERROR) {
        std::cout << "[OpenGL Error] (" << error << ": " << gluErrorString(error) << ")" << std::endl;
        error = glGetError();
        count++;
    }
    return count > 0;
}

} // namespace omega::gfx
