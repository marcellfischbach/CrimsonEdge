#version 330
layout(location = 0) out vec4 ce_FragColor;

uniform samplerCube ce_Diffuse;


in vec3 texCoord;

void main ()
{
	vec3 tex = normalize(texCoord);
	ce_FragColor = texture(ce_Diffuse, texCoord);
}

