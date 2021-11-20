#version 330 core
layout(location = 0) in vec3 vPos; // Position of each vertex (XYZ)
layout(location = 1) in vec3 vNormal; // Direction of normal vectors for each vertex (XYZ)
layout(location = 2) in vec3 vColor; // Color of each vertex (RGB)

out vec3 color; // Output color for the fragment shader

uniform vec3 uniColor; // The color of all the object

uniform mat4 model; // Model matrix (LOCAL COORDS -> WORLD COORDS)
uniform mat4 view; // View matrix (WORLD COORDS -> VIEW COORDS)
uniform mat4 projection; // Projection matrix (VIEW COORDS -> CLIP COORDS)
// CLIP COORDS -> SCREEN COORDS transformation is done automatically

void main()
{
	gl_Position = projection * view * model * vec4(vPos, 1.0); // Compute the 3D position of each vertex
	
	color = uniColor; // Send the uniform object color to the fragment shader
	//color = vColor; // Send each vertex color to the fragment shader
}