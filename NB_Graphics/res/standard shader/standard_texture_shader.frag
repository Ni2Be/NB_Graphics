#version 410 core

uniform sampler2D diffuse_map;
uniform sampler2D specular_map;
uniform sampler2D normal_map;
uniform sampler2D height_map;

struct Material
{	
	vec3  direction;
	vec3  color;
	float ambient_strength;
	float strength;
};
uniform Material material;

struct Directional_Light
{	
	vec3  direction;
	vec3  color;
	float ambient_strength;
	float strength;
};
uniform Directional_Light dir_light;

in vec3 vertex_pos;
in vec2 vertex_uv;
in vec3 vertex_normal;

out vec4 frag_color;

vec3 calc_directional_light(Directional_Light light, vec3 vertex_dir, vec3 vertex_pos);

void main()
{
	vec3 vertex_direction = normalize(vertex_normal);
	
	vec3 light_strength = vec3(0.0f,0.0f,0.0f);
	
	light_strength += calc_directional_light(dir_light, vertex_direction, vertex_pos);

	//output   
   frag_color = vec4(light_strength, 1.0f);
}

vec3 calc_directional_light(Directional_Light light, vec3 vertex_dir, vec3 vertex_pos)
{
	//Ambient
	vec3 ambient_light = light.ambient_strength * light.color * vec3(texture(diffuse_map, vertex_uv));

	return ambient_light + max(dot(vertex_dir, -light.direction), 0.0f) * light.strength * vec3(texture(diffuse_map, vertex_uv)) / vec3(texture(specular_map, vertex_uv))* light.color;
}
