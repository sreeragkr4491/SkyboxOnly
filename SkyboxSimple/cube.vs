#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normaldata ;

out vec3 normal;
out vec3 pos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    normal=mat3(transpose(inverse(model)))*normaldata;
    pos=vec3(model*vec4((position.x-2),position.y,position.z,1.0));
    gl_Position = projection * view * model * vec4(pos, 1.0f);
}