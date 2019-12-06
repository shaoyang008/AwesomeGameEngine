#version 330 core

in vec2 texCoord;
// out vec4 color;

uniform sampler2D TextureMap;

void main()
{    
	// gl_FragColor = vec4(texCoord, 0.0, 1.0);
	gl_FragColor = texture(TextureMap, texCoord);
}  