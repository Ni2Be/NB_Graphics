#version 410 core

uniform mat4 transform;
uniform mat4 view;
uniform mat4 projection;

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 uv;
layout (location = 2) in vec3 normal;
layout (location = 3) in vec3 tangent;
layout (location = 4) in vec3 bi_tangent;

out VS_OUT
{
	vec3 pos;
	vec2 uv;
	vec3 normal;
	mat3 tbn;
} vs_out;

void main()
{
	vs_out.uv     = uv;
	vs_out.pos    = vec3(transform * vec4(pos, 1.0f));
	vs_out.normal = vec3(transform * vec4(normal, 0.0f));
	vec3 t = normalize(vec3(transform * vec4(tangent, 0.0f)));
	vec3 b = normalize(vec3(transform * vec4(bi_tangent, 0.0f)));
	vec3 n = normalize(vec3(transform * vec4(normal, 0.0f)));
	vs_out.tbn = mat3(t, b, n);

	gl_Position   = projection * view * transform * vec4(pos, 1.0);
}