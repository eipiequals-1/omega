#include "sprite_batch.hpp"

#include <GL/gl.h>

#include <algorithm>
#include <iostream>
#include <memory>

namespace omega::gfx {

SpriteBatch::SpriteBatch() : quads_rendered(0), tex_bind_slot(0) {
    // indices will never change so set them now
    uint32_t indices[index_buffer_capacity];
    uint32_t offset = 0;
    for (size_t i = 0; i < index_buffer_capacity; i += 6) {
        // triangle 1
        indices[i + 0] = 0 + offset;
        indices[i + 1] = 1 + offset;
        indices[i + 2] = 2 + offset;
        // triangle 2
        indices[i + 3] = 2 + offset;
        indices[i + 4] = 3 + offset;
        indices[i + 5] = 0 + offset;

        offset += 4;
    }
    ibo = create_uptr<IndexBuffer>(indices, index_buffer_capacity);

    const char vertex[] = R"glsl(
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
            
            return mat4(oc * axis.x * axis.x + c,           oc * axis.x * axis.y - axis.z * s,  oc * axis.z * axis.x + axis.y * s,  0.0,
                        oc * axis.x * axis.y + axis.z * s,  oc * axis.y * axis.y + c,           oc * axis.y * axis.z - axis.x * s,  0.0,
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
	)glsl";

    const char fragment[] = R"glsl(
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
	)glsl";

    sprite_shader = create_uptr<Shader>(std::string(vertex), std::string(fragment));
    vao = create_uptr<VertexArray>();
    vbo = create_uptr<VertexBuffer>(vertex_buffer_capacity * vertex_count * sizeof(float));
    VertexBufferLayout layout;
    layout.push(GL_FLOAT, 3); // world coords
    layout.push(GL_FLOAT, 4); // color
    layout.push(GL_FLOAT, 2); // tex coords
    layout.push(GL_FLOAT, 1); // tex idx
    layout.push(GL_FLOAT, 3); // rotation axis
    layout.push(GL_FLOAT, 1); // rotation angle
    layout.push(GL_FLOAT, 3); // rotation center
    vao->add_buffer(*vbo, layout);

    for (uint32_t i = 0; i < max_textures; ++i) {
        texture_binds[i] = i;
    }
    sprite_shader->bind();
    sprite_shader->set_uniform_1iv("u_Textures", (int *)texture_binds.data(), max_textures);
    sprite_shader->unbind();
}

void SpriteBatch::begin_render() {
    quads_rendered = 0;
    tex_bind_slot = 0;
    // reset previous batch texture data
    for (size_t i = 0; i < textures_to_render.size(); i++) {
        textures_to_render[i] = nullptr;
    }
}

void SpriteBatch::render_texture(const Texture *texture, const float x, const float y, const glm::vec4 &color) {
    render_texture(texture, x, y, texture->get_width(), texture->get_height(), color);
}

void SpriteBatch::render_texture(const Texture *texture, const float x, const float y, const float w, const float h, const glm::vec4 &color) {
    // set tex coords
    glm::rectf tex_coords(0.0f, 0.0f, texture->get_width(), texture->get_height());
    render_texture(texture, tex_coords, glm::rectf(x, y, w, h), color);
}

void SpriteBatch::render_texture(const Texture *texture, const glm::rectf &src, const glm::rectf &dest, const glm::vec4 &color) {
    render_texture(texture, src, dest, 0.0f, dest.center(), color);
}

void SpriteBatch::render_texture(const Texture *texture, glm::rectf src, const glm::rectf &dest, float rotation, const glm::vec2 &center, const glm::vec4 &color) {
    render_texture(texture, src, dest, glm::vec3(0.0f, 0.0f, -1.0f), rotation, glm::vec3(center, 0.0f), color);
}

void SpriteBatch::render_texture(const Texture *texture, glm::rectf src, const glm::rectf &dest, const glm::vec3 rotation_axis, float rotation, const glm::vec3 &center_of_rotation, const glm::vec4 &color) {
    if (quads_rendered == quad_capacity) {
        end_render();
        begin_render();
    }
    float tex_id = tex_bind_slot;
    // check if texture has been used in this batch
    bool in_batch = false;
    for (uint32_t i = 0; i < textures_to_render.size(); i++) {
        if (textures_to_render[i] == texture) {
            in_batch = true;
            tex_id = i;
            break;
        }
    }
    if (!in_batch) {
        if (tex_bind_slot == max_textures) {
            end_render();
            begin_render();
        }
        // add the texture to the to render vector and bind
        textures_to_render[tex_bind_slot] = texture;
        texture->bind(tex_bind_slot);
        tex_id = tex_bind_slot;
        tex_bind_slot++;
    }
    // normalize src rect
    src.x = src.x / texture->get_width();
    src.y = src.y / texture->get_height();
    src.w = src.w / texture->get_width();
    src.h = src.h / texture->get_height();
    constexpr static float z = 0.0f;

    // inverse texture to y up
    Vertex v0 = {
        {dest.x, dest.y, z},
        color,
        {src.x, src.y + src.h},
        tex_id,
        rotation_axis,
        rotation,
        center_of_rotation};
    Vertex v1 = {
        {dest.x + dest.w, dest.y, z},
        color,
        {src.x + src.w, src.y + src.h},
        tex_id,
        rotation_axis,
        rotation,
        center_of_rotation};
    Vertex v2 = {
        {dest.x + dest.w, dest.y + dest.h, z},
        color,
        {src.x + src.w, src.y},
        tex_id,
        rotation_axis,
        rotation,
        center_of_rotation};
    Vertex v3 = {
        {dest.x, dest.y + dest.h, z},
        color,
        {src.x, src.y},
        tex_id,
        rotation_axis,
        rotation,
        center_of_rotation};

    Quad q = {v0, v1, v2, v3};
    auto quad = q.data();

    vbo->bind();
    vbo->sub_data(sizeof(Quad) * quads_rendered, sizeof(Quad), quad);
    quads_rendered++;
}

void SpriteBatch::render_texture_region(const TextureRegion *texture_region, const glm::rectf &dest, const glm::vec4 &color) {
    render_texture(texture_region->get_texture(), texture_region->get_rect().convert_type<float>(), dest, color);
}

void SpriteBatch::end_render() {
    sprite_shader->bind();
    vao->bind();
    ibo->bind();
    glDrawElements(GL_TRIANGLES, quads_rendered * index_count, GL_UNSIGNED_INT, nullptr);
    VertexArray::unbind();
    IndexBuffer::unbind();
    Shader::unbind();
}

} // namespace omega::gfx
