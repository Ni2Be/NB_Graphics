#version 330 core

uniform vec3 camera_pos;

in vec4 vertex_color;
in vec3 vertex_normal;
in vec3 vertex_position;
in vec2 vertex_texture_coo;

out vec4 color;


void main()
{
	vec3 view_direction   = normalize(camera_pos - vertex_position);
	vec3 vertex_direction = normalize(vertex_normal);

	vec3 light_strength   = vec3(1.0f,1.0f,1.0f);


	color          = vec4(light_strength, 1.0f) * vertex_color;
}
