#version 330

in vec3 vertex;
in vec2 texcoord;
in vec3 normal;

uniform mat4 WorldView, WorldProj, WorldInverse;
uniform mat4 ModelTr, NormalTr;

out vec3 normalVec, lightVec, eyeVec;
out vec2 texCoord;

uniform vec3 lightPos;

void main()
{
	vec3 worldPos = (ModelTr * vec4(vertex, 1.0)).xyz;
	vec3 eyePos = (WorldInverse * vec4(0, 0, 0, 1)).xyz;

	normalVec = normal * mat3(NormalTr); 

	eyeVec = eyePos - worldPos;
	lightVec = lightPos - worldPos;

	gl_Position = WorldProj * WorldView * ModelTr * vec4(vertex, 1.0);
	texCoord = texcoord;
}
