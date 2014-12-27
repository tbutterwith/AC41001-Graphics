// Vertex shader with a model transformation uniform

#version 400
layout(location = 0) in vec4 position;
layout(location = 1) in vec4 colour;
layout(location = 2) in vec3 normal;
out vec4 fcolour;
uniform mat4 model, view, projection;

void main()
{
	vec3 lightDirection = vec3(0,1,9.0);
	vec4 diffuseColour = vec4(0.4, 0.4, 0.4, 0.4);

	vec4 ambient = diffuseColour * 0.1;

	// calculate diffuse lighting
	mat4 mv_matrix = view * model;					// Be careful with the order of matrix multiplication!
	mat3 n_matrix = transpose(inverse(mat3(mv_matrix)));  // It's more efficient to calcuate this in your application
	vec3 N = normalize(n_matrix * normal);			// Be carefull with the order of multiplication!
	vec3 L = normalize(lightDirection);					// Ensure light_dir is unit length
	vec4 diffuse = max(dot(L, N), 0) * diffuseColour;

	// Calculate specular lighting
	vec4 specular_colour = vec4(1.0, 1.0, 0.6, 0.4);	// Bright yellow light
	float shininess = 8;							// smaller values give sharper specular repsonses, larger more spread out
	vec4 P = mv_matrix * position;				// Calculate vertex position in eye space
	vec3 V = normalize(-P.xyz);
	vec3 R= reflect(-L, N);							// Calculate the reflected beam, N defines the plane (see diagram on labsheet)
	vec4 specular = pow(max(dot(R, V), 0), shininess) * specular_colour;	// Calculate specular component


	gl_Position = (projection * view * model) * position;
	
	//fcolour = vec4(0.5,0.5,0.0,1.0);
	fcolour = ambient + diffuse + (0.2*specular);
}