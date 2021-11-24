#version 330 core
in vec3 color; // Input color from the vertex shader

layout(location = 0) out vec4 outColor; // Fragment color

void main()
{
	outColor = vec4(color, 1.0f); // Output color of each fragment
}