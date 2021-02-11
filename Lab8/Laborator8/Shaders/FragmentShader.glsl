#version 330

// TODO: get color value from vertex shader
in vec3 world_position;
in vec3 world_normal;

// Uniforms for light properties
uniform vec3 light_direction;
uniform vec3 light_position;
uniform vec3 eye_position;

uniform float material_kd;
uniform float material_ks;
uniform int material_shininess;

uniform vec3 object_color;

uniform int type_of_light;
uniform float cut_off_angle;

layout(location = 0) out vec4 out_color;

void main()
{
	// TODO: define ambient light component
	float ambient_light = 0.25;

	// TODO: compute diffuse light component
	float diffuse_light = material_kd * max(dot(normalize(world_normal), light_position - world_position), 0);

	// TODO: compute specular light component
	float specular_light = 0;

	if (diffuse_light > 0)
	{
	specular_light = material_ks * pow(max(dot(world_normal, light_position - world_position + eye_position - world_position), 0), material_shininess);
	}

	// TODO: compute light
	float light = 0;
	if (type_of_light == 1) {
		if (dot(-(light_position - world_position), light_direction) > cos(radians(cut_off_angle))) {
			light = ambient_light + dot(-(light_position - world_position), light_direction) -  cos(radians(cut_off_angle)) / (1.f -  cos(radians(cut_off_angle))) * dot(-(light_position - world_position), light_direction) -  cos(radians(cut_off_angle)) / (1.f -  cos(radians(cut_off_angle))) * (diffuse_light + specular_light);
		} else {
			light = ambient_light;
		}
	} else {
		light = ambient_light + 1.f / max(distance(light_position, world_position) * distance(light_position, world_position), 1.f) * (diffuse_light + specular_light);
	}

	// TODO: write pixel out color
	out_color = vec4(object_color * light, 1);
}