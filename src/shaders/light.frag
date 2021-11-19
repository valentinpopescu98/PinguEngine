#version 330 core
in vec3 color;
in vec2 textCoord;

layout(location = 0) out vec4 outColor;

//uniform sampler2D text0;

void main()
{
	outColor = vec4(color, 1.0f);
	//outColor = texture(text0, textCoord) * vec4(color, 1.0f);
	//outColor = mix(texture(text0, textCoord), vec4(color, 1.0f), 0.5f);
}