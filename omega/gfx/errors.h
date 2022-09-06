#ifndef OMEGA_GFX_ERRORS_H
#define OMEGA_GFX_ERRORS_H

namespace omega::gfx {

/**
 * Basic OpenGL error handler
 * @return if there was an error
 */
bool glCheckError();

} // namespace omega::gfx

#endif // OMEGA_GFX_ERRORS_H