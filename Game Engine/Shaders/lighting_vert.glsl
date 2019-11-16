#version 330

// uniform mat4 WorldView, WorldInverse, WorldProj, ModelTr, NormalTr;

in vec3 vertex;
in vec2 texcoord;
in vec3 normal;

uniform mat4 WorldView, WorldProj;

out vec3 position;

void main()
{
	position = vertex.xyz;
	gl_Position.w = 1.0;
    gl_Position.xyz = vertex.xyz / 1000.0;
}
