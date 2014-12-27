// Minimal fragment shader

#version 420

in vec4 fcolour;
in vec2 ftexcoord;
out vec4 outputColor;

uniform sampler2D tex1;
uniform sampler2D norm1;

void main()
{
	vec4 texcolour = texture(tex1, ftexcoord);
	vec4 bumpColour = texture(norm1, ftexcoord);
	outputColor = fcolour * (texcolour * bumpColour);
}