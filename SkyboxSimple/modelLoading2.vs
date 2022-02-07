#version 330 core
layout ( location = 0 ) in vec3 position;
layout ( location = 1 ) in vec3 normal;
layout ( location = 2 ) in vec2 texCoords;

out vec2 TexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main( )
{

	//for position adjustment 
    gl_Position = projection * view * model * vec4( position, 0.5f );
    TexCoords = texCoords;
}