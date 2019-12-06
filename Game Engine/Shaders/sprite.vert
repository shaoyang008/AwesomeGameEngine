#version 330 core

in vec4 vertex; // <vec2 position, vec2 texCoords>

out vec2 texCoord;

uniform mat4 ModelTr, WorldOrtho;

void main()
{
    texCoord = vertex.zw;
    gl_Position = WorldOrtho * ModelTr * vec4(vertex.xy, 0.0, 1.0);
}
