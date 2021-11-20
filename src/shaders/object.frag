#version 330 core
in vec3 color;
in vec2 textCoord;

layout(location = 0) out vec4 outColor;

uniform sampler2D textSlot;

void main()
{
	outColor = texture(textSlot, textCoord) * vec4(color, 1.0f);
	//outColor = mix(texture(textSlot, textCoord), vec4(color, 1.0f), 0.5f);
}