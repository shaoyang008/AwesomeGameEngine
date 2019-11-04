#version 330

in vec3 color;

void main()
{
   gl_FragColor.xyz = color;
}