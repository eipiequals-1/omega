#ifndef OMEGA_GFX_SHADERS_PARTICLEDEFAULT_HPP
#define OMEGA_GFX_SHADERS_PARTICLEDEFAULT_HPP

#include <string>

namespace omega::gfx::shaders {

// ParticleEmitter default vertex shader
const std::string particle_default_vert = R"glsl(
#version 450

layout(location=0) in vec2 a_Pos;
layout(location=1) in vec2 a_Center;
layout(location=2) in float a_Radius;
layout(location=3) in vec4 a_Color;

layout(location=0) out vec2 v_Pos;
layout(location=1) out vec2 v_Center;
layout(location=2) out float v_Radius;
layout(location=3) out vec4 v_Color;

uniform mat4 u_ViewProjMatrix;

void main() {
    gl_Position = u_ViewProjMatrix * vec4(a_Pos, 0.0, 1.0);
    v_Pos = a_Pos;
    v_Radius = a_Radius;
    v_Center = a_Center;
    v_Color = a_Color;
}
)glsl";

// ParticleEmitter default fragment shader
const std::string particle_default_frag = R"glsl(
#version 450

layout(location=0) in vec2 v_Pos;
layout(location=1) in vec2 v_Center;
layout(location=2) in float v_Radius;
layout(location=3) in vec4 v_Color;

out vec4 color;

void main() {
    color = vec4(0.0);
    float dist = distance(v_Pos, v_Center);
    if (dist <= v_Radius) {
        color = v_Color;
        color.a *= 1.0 - (dist / v_Radius);
    }
}
)glsl";

} // namespace omega::gfx::shaders

#endif // OMEGA_GFX_SHADERS_PARTICLEDEFAULT_HPP
