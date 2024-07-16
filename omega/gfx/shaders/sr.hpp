#ifndef OMEGA_GFX_SHADERS_SR_HPP
#define OMEGA_GFX_SHADERS_SR_HPP

#include <string>

namespace omega::gfx::shaders {

// ShapeRenderer vertex shader
const std::string sr_vert = std::string(R"glsl(
#version 450

layout(location=0) in vec2 a_Coord;
layout(location=1) in vec4 a_Color;

layout(location=0) out vec4 v_Color;

uniform mat4 u_ViewProjMatrix;

void main() {
    gl_Position = u_ViewProjMatrix * vec4(a_Coord.x, a_Coord.y, 0.0, 1.0);
    v_Color = a_Color;
}
)glsl");

// ShapeRenderer fragment shader
const std::string sr_frag = std::string(R"glsl(
#version 450

layout(location=0) in vec4 v_Color;
out vec4 color;

void main() {
    color = v_Color;
}
)glsl");

// ShapeRenderer wasm vertex shader
const std::string sr_vert_wasm = std::string(R"glsl(
attribute vec2 a_Coord;
attribute vec4 a_Color;

varying vec4 v_Color;

uniform mat4 u_ViewProjMatrix;

void main() {
    gl_Position = u_ViewProjMatrix * vec4(a_Coord.x, a_Coord.y, 0.0, 1.0);
    v_Color = a_Color;
}
)glsl");

// ShapeRenderer wasm fragment shader
const std::string sr_frag_wasm = std::string(R"glsl(
precision mediump float;

varying vec4 v_Color;

void main() {
    gl_FragColor = v_Color;
}
)glsl");

} // namespace omega::gfx::shaders

#endif // OMEGA_GFX_SHADERS_SR_HPP
