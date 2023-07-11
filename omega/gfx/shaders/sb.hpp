#ifndef OMEGA_GFX_SHADERS_SB_HPP
#define OMEGA_GFX_SHADERS_SB_HPP

#include <string>

namespace omega::gfx::shaders {

// SpriteBatch vertex shader
const std::string sb_vert = std::string(R"glsl(
#version 450

layout(location=0) in vec3 a_Pos;
layout(location=1) in vec4 a_Color;
layout(location=2) in vec2 a_TexCoords;
layout(location=3) in float a_TexIdx;
layout(location=4) in vec3 a_RotationAxis;
layout(location=5) in float a_RotationAngle;
layout(location=6) in vec3 a_CenterOfRotation;

layout(location=0) out vec4 v_Color;
layout(location=1) out vec2 v_TexCoords;
layout(location=2) out float v_TexIdx;

uniform mat4 u_ViewProjMatrix;

mat4 rotationMatrix(vec3 axis, float angle) {
    axis = normalize(axis);
    float s = sin(angle);
    float c = cos(angle);
    float oc = 1.0 - c;

    return mat4(oc * axis.x * axis.x + c, oc * axis.x * axis.y - axis.z * s, oc * axis.z * axis.x + axis.y * s,  0.0,
                oc * axis.x * axis.y + axis.z * s,  oc * axis.y * axis.y + c, oc * axis.y * axis.z - axis.x * s,  0.0,
                oc * axis.z * axis.x - axis.y * s,  oc * axis.y * axis.z + axis.x * s,  oc * axis.z * axis.z + c,           0.0,
                0.0,                                0.0,                                0.0,                                1.0);
}

void main() {
    mat4 model = rotationMatrix(a_RotationAxis, a_RotationAngle * 3.14159265 / 180.0);
    vec3 position = (model * vec4(a_Pos - a_CenterOfRotation, 1.0)).xyz;
    position += a_CenterOfRotation;
    gl_Position = u_ViewProjMatrix * vec4(position, 1.0);

    v_Color = a_Color;
    v_TexCoords = a_TexCoords;
    v_TexIdx = a_TexIdx;
}
)glsl");

// SpriteBatch fragment shader
const std::string sb_frag = std::string(R"glsl(
#version 450

layout(location=0) in vec4 v_Color;
layout(location=1) in vec2 v_TexCoords;
layout(location=2) in float v_TexIdx;

uniform sampler2D u_Textures[32];
out vec4 color;

void main() {
    int idx = int(v_TexIdx);
    color = texture(u_Textures[idx], v_TexCoords) * v_Color;
}
)glsl");


// SpriteBatch wasm vertex shader

const std::string sb_vert_wasm = std::string(R"glsl(
attribute vec3 a_Pos;
attribute vec4 a_Color;
attribute vec2 a_TexCoords;
attribute float a_TexIdx;
attribute vec3 a_RotationAxis;
attribute float a_RotationAngle;
attribute vec3 a_CenterOfRotation;

varying vec4 v_Color;
varying vec2 v_TexCoords;
varying float v_TexIdx;

uniform mat4 u_ViewProjMatrix;

mat4 rotationMatrix(vec3 axis, float angle) {
    axis = normalize(axis);
    float s = sin(angle);
    float c = cos(angle);
    float oc = 1.0 - c;

    return mat4(oc * axis.x * axis.x + c, oc * axis.x * axis.y - axis.z * s, oc * axis.z * axis.x + axis.y * s,  0.0,
                oc * axis.x * axis.y + axis.z * s,  oc * axis.y * axis.y + c, oc * axis.y * axis.z - axis.x * s,  0.0,
                oc * axis.z * axis.x - axis.y * s,  oc * axis.y * axis.z + axis.x * s,  oc * axis.z * axis.z + c,           0.0,
                0.0,                                0.0,                                0.0,                                1.0);
}

void main() {
    mat4 model = rotationMatrix(a_RotationAxis, a_RotationAngle * 3.14159265 / 180.0);
    vec3 position = (model * vec4(a_Pos - a_CenterOfRotation, 1.0)).xyz;
    position += a_CenterOfRotation;
    gl_Position = u_ViewProjMatrix * vec4(position, 1.0);

    v_Color = a_Color;
    v_TexCoords = a_TexCoords;
    v_TexIdx = a_TexIdx;
}
)glsl");

// SpriteBatch wasm fragment shader
const std::string sb_frag_wasm = std::string(R"glsl(
precision mediump float;

varying vec4 v_Color;
varying vec2 v_TexCoords;
varying float v_TexIdx;

uniform sampler2D u_Textures[32];

vec4 getTextureColor(int id) {
    for (int i = 0; i < 32; i++) {
        if (i == id) {
            return texture2D(u_Textures[i], v_TexCoords);
        }
    }
}

void main() {
    int idx = int(floor(v_TexIdx));
    vec4 color = getTextureColor(idx);

    gl_FragColor = color * v_Color;
}
)glsl");


} // namespace omega::gfx::shaders

#endif // OMEGA_GFX_SHADERS_SB_HPP
