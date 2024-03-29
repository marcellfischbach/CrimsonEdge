#version 330
layout(location = 0) out vec4 ce_FragColor;

uniform sampler2DArray ce_Diffuse;
uniform float ce_ArrayIndex;


in vec2 texCoord;

void main ()
{
	ce_FragColor = texture(ce_Diffuse, vec3(texCoord, 1.0));
}

