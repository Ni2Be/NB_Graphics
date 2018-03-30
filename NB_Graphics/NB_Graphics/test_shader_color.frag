#version 330 core

struct Material 
{
	sampler2D texture;
	sampler2D specular_map;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float shininess;
};
uniform Material material;

struct Point_Light
{
    vec3  position;
	
	float attenuation_const;
	float attenuation_lin;
	float attenuation_quad;
  
    vec3  color;
	float strength;
	float ambient_strength;
};
const int LIGHT_COUNT = 12;
uniform   Point_Light point_lights[LIGHT_COUNT];

//Sun
struct Directional_Light
{	
	vec3  direction;
	vec3  color;
	float strength;
};
uniform Directional_Light dir_light;
//

uniform vec3 camera_pos;

in vec4 vertex_color;
in vec3 vertex_normal;
in vec3 vertex_position;
in vec2 vertex_texture_coo;

out vec4 color;

vec3 calc_point_light(Point_Light light, 
                      vec3        vertex_dir,
					  vec3        vertex_pos, 
					  vec3        view_dir);

vec3 calc_directional_light(Directional_Light light, 
                            vec3              vertex_dir, 
							vec3              vertex_pos, 
							vec3              view_dir);

void main()
{
	vec3 view_direction   = normalize(camera_pos - vertex_position);
	vec3 vertex_direction = normalize(vertex_normal);

	vec3 light_strength   = vec3(0.0f,0.0f,0.0f);

	//point lights
	for (int i = 0; i < LIGHT_COUNT; i++)
	{
		light_strength += calc_point_light(point_lights[i], 
		                                   vertex_direction, 
										   vertex_position, 
										   view_direction);
	}
	//directional light
	light_strength += calc_directional_light(dir_light, 
	                                         vertex_direction, 
											 vertex_position, 
											 view_direction);

	color          = vec4(light_strength, 1.0f) * vertex_color;	
}

vec3 calc_point_light(Point_Light light, 
                      vec3 vertex_dir, 
					  vec3 vertex_pos, 
					  vec3 view_dir)
{
	//Ambient
	vec3 ambient_light     = light.ambient_strength 
	                         * light.color 
							 * vec3(texture(material.texture, vertex_texture_coo));

	//Diffuse
	vec3 light_direction   = normalize(light.position - vertex_pos);
	float diffuse_strength = max(dot(vertex_dir, light_direction), 0.0f);
	vec3 diffuse_light     = light.strength 
	                         * diffuse_strength 
							 * light.color 
							 * vec3(texture(material.texture, vertex_texture_coo));

	//Specular	
	vec3 reflect_direction  = reflect(-light_direction, vertex_dir); 
	float specular_strength = pow(max(dot(view_dir, reflect_direction), 0.0), 
	                              material.shininess);
	vec3 specular_light     = light.strength 
	                          * specular_strength 
							  * light.color 
							  * vec3(texture(material.specular_map, vertex_texture_coo));

	//Attenuation
	float distance    = length(light.position - vertex_pos);
	float attenuation = 1.0f /
						(  light.attenuation_const 
						 + (light.attenuation_lin 
						    * distance)
						 + (light.attenuation_quad 
						    * pow(distance, 2) 
						);   

	//SUM
	vec3 light_sum =   ambient_light  * attenuation 
	                 + diffuse_light  * attenuation 
					 + specular_light * attenuation;
    return light_sum;
}

vec3 calc_directional_light(Directional_Light light, 
                            vec3              vertex_dir, 
							vec3              vertex_pos, 
							vec3              view_dir)
{
	return   max(dot(vertex_dir, -light.direction), 0.0f) 
	       * light.strength 
		   * vec3(texture(material.texture, vertex_texture_coo)) 
		   * light.color;
}
