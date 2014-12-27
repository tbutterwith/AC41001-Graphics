#version 400

// Interpolated values from the vertex shaders
in vec2 UV;
in vec4 particlecolor;

// Ouput data
out vec4 color;

uniform sampler2D myTextureSampler;

uniform uint weather;

void main(){
	// Output color = color of the texture at the specified UV
	//color = texture2D( myTextureSampler, UV ) * particlecolor;
	
	color = particlecolor;


}