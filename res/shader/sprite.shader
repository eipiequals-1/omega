#shader vertex
#version 450

layout(location=0) in vec3 a_Pos;
layout(location=1) in vec4 a_Color;
layout(location=2) in vec2 a_TexCoords;
layout(location=3) in float a_TexIdx;

layout(location=0) out vec4 v_Color;
layout(location=1) out vec2 v_TexCoords;
layout(location=2) out float v_TexIdx;

uniform mat4 u_ViewProjMatrix;

void main() {
    gl_Position = u_ViewProjMatrix * vec4(a_Pos, 1.0f);
    v_Color = a_Color;
    v_TexCoords = a_TexCoords;
    v_TexIdx = a_TexIdx;
}

#shader fragment
#version 450

layout(location=0) in vec4 v_Color;
layout(location=1) in vec2 v_TexCoords;
layout(location=2) in float v_TexIdx;

uniform sampler2D u_Textures[32];
out vec4 color;

void main() {
    int idx = int(v_TexIdx);
    if (idx < 0) {
        color = v_Color;
    } else {
        color = texture(u_Textures[idx], v_TexCoords) * v_Color;
    }
}
