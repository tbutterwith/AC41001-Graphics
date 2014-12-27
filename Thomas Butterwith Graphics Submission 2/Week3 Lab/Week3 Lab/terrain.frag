// Minimal fragment shader

#version 420



in vec4 fcolour;
in vec2 ftexcoord;
in vec3 normal_f;
in vec4 position_f;
out vec4 outputColor;

uniform sampler2D tex1;
uniform sampler2D norm1;
uniform mat4 model, view, projection;

vec4 ambient = vec4(0.5, 0.5, 0.5, 1.0);
vec3 light_dir = vec3(0.0, 0.0, 10.0);


void main()
{
	//vec3 light_dir0 = vec4(light_dir, 1.0) * model;
	vec4 specular_colour = vec4(0.4,0.4,0.4,1.0);
	vec4 diffuse_colour = vec4(0.0,0.0,0,0.0);
	
	float shininess = 1.0;

	diffuse_colour = vec4(0.4, 0.4, 0.4, 1.0);

	//ambient = diffuse_colour * 0.2;

	mat4 mv_matrix = view * model;
	mat3 normalmatrix = mat3(mv_matrix);
	vec3 N = mat3(mv_matrix) * normal_f;
	N = normalize(N);
	light_dir = normalize(light_dir);

	vec3 diffuse = max(dot(N, light_dir), 0.0) * diffuse_colour.xyz;

	vec4 P = position_f * mv_matrix;
	vec3 half_vec = normalize(light_dir + P.xyz);
	vec4 specular = pow(max(dot(N, half_vec), 0.0), shininess) * specular_colour;

	if(fcolour != vec4(0.0, 0.0, 0.0, 1.0)) {
		outputColor = fcolour + diffuse + ambient + specular;
	} else {
	// Define the vertex colour
	vec4 fcolour0 = fcolour + diffuse + ambient + specular;
	vec4 texcolour = texture(tex1, ftexcoord);
	vec4 bumpColour = texture(norm1, ftexcoord);
	outputColor = fcolour0 * (texcolour * bumpColour);
	}
}