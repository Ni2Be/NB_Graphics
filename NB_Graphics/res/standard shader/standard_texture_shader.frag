#version 410 core

uniform sampler2D diffuse_map;
uniform sampler2D specular_map;
uniform sampler2D normal_map;
uniform sampler2D height_map;

uniform bool has_diffuse_map;
uniform bool has_specular_map;
uniform bool has_normal_map;
uniform bool has_height_map;


struct Material
{	
	vec3  direction;
	vec3  color;
	float ambient_strength;
	float shininess;
};
uniform Material material;

struct Point_Light
{
    vec3 position;
	
	float attenuation_const;
	float attenuation_lin;
	float attenuation_quad;
  
    vec3  color;
	float strength;
	float ambient_strength;
};
const int MAX_POINT_LIGHT_COUNT = 32;
uniform Point_Light point_lights[MAX_POINT_LIGHT_COUNT];
uniform int point_light_count;

struct Directional_Light
{	
	vec3  direction;
	vec3  color;
	float ambient_strength;
	float strength;
};
uniform Directional_Light dir_light;//TODO should be array

uniform vec3 camera_pos;

in VS_OUT
{
	vec3 pos;
	vec2 uv;
	vec3 normal;
	mat3 tbn;
} vs_out;

out vec4 frag_color;

vec3 calc_directional_light(Directional_Light light, vec3 vertex_pos, vec3 view_direction, vec2 vertex_uv, vec3 fragment_normal);
vec3 calc_point_light(Point_Light light, vec3 vertex_pos, vec3 view_direction, vec2 vertex_uv, vec3 fragment_normal);

void main()
{
	vec3 view_direction   = normalize(camera_pos - vs_out.pos);

	vec3 fragment_normal = vs_out.normal;
	if (has_normal_map)
	{
		fragment_normal = texture(normal_map, vs_out.uv).rgb;
		fragment_normal = normalize(fragment_normal * 2.0 - 1.0);
		fragment_normal = normalize(vs_out.tbn * fragment_normal);
	}

	vec3 light_strength = vec3(0.0f,0.0f,0.0f);
	for (int i = 0; i < point_light_count; i++)
	{
		light_strength += calc_point_light(point_lights[i], vs_out.pos, view_direction, vs_out.uv, fragment_normal);
	}
	light_strength += calc_directional_light(dir_light, vs_out.pos, view_direction, vs_out.uv, fragment_normal);

	//output   
   frag_color = vec4(light_strength, 1.0f);
   

   //DEBUG
   //frag_color = texture(diffuse_map, vertex_uv);
}

vec3 calc_directional_light(Directional_Light light, vec3 vertex_pos, vec3 view_direction, vec2 vertex_uv, vec3 fragment_normal)
{
	//Ambient + Directional
	vec3 light_sum;
	if (has_diffuse_map)
	{
		light_sum += light.ambient_strength * light.color * vec3(texture(diffuse_map, vertex_uv));
		light_sum += max(dot(fragment_normal, -light.direction), 0.0f) 
		                 * light.strength 
						 * vec3(texture(diffuse_map, vertex_uv))
						 * light.color;
	}
	if (has_specular_map)
	{
		vec3 halfway_direction  = normalize(light.direction + view_direction);
		float specular_strength = pow(max(dot(fragment_normal, halfway_direction), 0.0), material.shininess * 128);
		light_sum               += specular_strength * light.color * vec3(texture(specular_map, vertex_uv));
	}
	return light_sum;
}

vec3 calc_point_light(Point_Light light, vec3 vertex_pos, vec3 view_direction, vec2 vertex_uv, vec3 fragment_normal)
{
	vec3 light_direction = normalize(light.position - vertex_pos);

	//Ambient
	vec3 ambient_light = light.ambient_strength * light.color * vec3(texture(diffuse_map, vertex_uv));

	//Diffuse
	float diffuse_strength = max(dot(fragment_normal, light_direction), 0.0f);
	vec3 diffuse_light     = light.strength * diffuse_strength * light.color * vec3(texture(diffuse_map, vertex_uv));

	//Specular	
	vec3 specular_light    = vec3(0.0f,0.0f,0.0f);
	if (has_specular_map && (diffuse_strength > 0.0f))
	{
		vec3 halfway_direction = normalize(light_direction + view_direction);
		float specular_strength = pow(max(dot(fragment_normal, halfway_direction), 0.0), material.shininess * 128);
		specular_light          += specular_strength * light.color * vec3(texture(specular_map, vertex_uv));
	}

	//Attenuation
	float distance    = length(light.position - vertex_pos);
	float attenuation = 1.0f / (light.attenuation_const + light.attenuation_lin * distance + light.attenuation_quad * pow(distance, 2));   

	//SUM
	vec3 light_sum = ambient_light * attenuation + diffuse_light * attenuation + specular_light * attenuation;
    return light_sum;
}
