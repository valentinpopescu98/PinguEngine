#version 330 core
in vec3 normal; // Input normals from the vertex shader
in vec2 textCoord; // Input texture coordinates from the vertex shader
in vec3 color; // Input color from the vertex shader

in vec3 objPos; // The global position of the object

layout(location = 0) out vec4 outColor; // Fragment color

uniform sampler2D textSlot; // Value coresponding to the used texture slot
uniform vec3 lightColor; // Color of the light source (TODO: implement a combined color from many light sources)
uniform vec3 lightPos; // Color of the light position (TODO: implement an array of many light sources)
uniform vec3 camPos; // Position of the camera

void main()
{
	vec3 outNormal = normalize(normal); // Normalize the normals (make it in range [0, 1])
	vec3 lightDirection = normalize(lightPos - objPos); // Calculate light direction and normalize it

	float ambient = 0.2f; // Ambient light value
	/* Calculate cos between normal and light direction.
	   Take the maximum between this and 0 because the higher the cos,
	   the lower the angle is, so at higher angles take a lower value
	   and diffuse lesser light. */
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	float maxSpecular = 0.5f; // Maximum intensity of specular light
	vec3 viewDirection = normalize(camPos - objPos); // Calculate vector of view direction
	// Reflection direction is tangent to light direction and is calculated depending on the direction of normal vector
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	/* Calculate cos between view direction and light reflection.
	   Take the maximum between this and 0.
	   Raise the result to the power of 8 (or choose any other constant),
	   the higher the power is the more focused the specular light is. */
	float specularAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 8);
	float specular = maxSpecular * specularAmount;

	outColor = texture(textSlot, textCoord) * vec4(color, 1.0f) * vec4(lightColor, 1.0f) * (ambient + diffuse + specular); // Output color of each fragment
	//outColor = mix(texture(textSlot, textCoord), vec4(color, 1.0f) * vec4(lightColor, 1.0f) * (ambient + diffuse + specular), 0.5f);
}