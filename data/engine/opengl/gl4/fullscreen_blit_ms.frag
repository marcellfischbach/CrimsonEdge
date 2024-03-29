#version 330
layout(location = 0) out vec4 ce_FragColor;

uniform sampler2DMS  ce_Diffuse;
uniform int ce_Samples;


in vec2 texCoord;

void main ()
{
	ivec2 size = textureSize (ce_Diffuse);
	vec4 color = vec4(0, 0, 0, 0);

	for (int i=0; i<ce_Samples; i++)
	{
	    color += texelFetch(ce_Diffuse, ivec2(texCoord * size), i);
	}
	ce_FragColor = color / ce_Samples;
}

