#version 330

// uniform mat4 WorldView, WorldInverse, WorldProj, ModelTr, NormalTr;

in vec4 vertex;
in vec3 lighting;

out vec3 color;

void main()
{
	color = lighting;
    gl_Position = vertex;
}
