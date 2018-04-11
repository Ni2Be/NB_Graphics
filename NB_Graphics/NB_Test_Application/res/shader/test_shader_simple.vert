#version 410 core

uniform mat4 transform;
uniform mat4 view;
uniform mat4 projection;

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 uv;
layout (location = 2) in vec3 normal;

out vec3 vertex_pos;
out vec2 vertex_uv;
out vec3 vertex_normal;

void main()
{
	vertex_uv     = uv;
	vertex_normal = mat3(transpose(inverse(transform))) * normal;
	vertex_pos    = vec3(transform * vec4(pos, 1.0f));
	gl_Position   = projection * view * transform * vec4(pos, 1.0);
}