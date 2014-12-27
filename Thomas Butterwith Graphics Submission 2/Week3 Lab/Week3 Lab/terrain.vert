// Minimal vertex shader

#version 400

// These are the vertex attributes
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec3 texcoord;
layout(location = 3) in vec3 emissiveColour;

// Uniform variables are passed in from the application
uniform mat4 model, view, projection;
uniform uint colourmode;


// Output the vertex colour - to be rasterized into pixel fragments
out vec4 fcolour;
out vec2 ftexcoord;
out vec3 normal_f;
out vec4 position_f;



void main()
{
	position_f = vec4(position, 1.0);
	// Define the vertex position
	gl_Position = projection * view * model * position_f;

	// Output the texture coordinates
	ftexcoord = texcoord.xy;

	normal_f = normal;

	fcolour = vec4(emissiveColour, 1.0);
}

