#version 330 core 
layout (location=0) in vec3 position; 
//layout (location=1) in vec3 colorpos; 

out vec3 texcor;
uniform mat4 projection;
//uniform mat4 model;
//uniform mat4 model1;
uniform mat4 view;

void main()  // 4 must add paranthesis
{
vec4 pos = projection * view * vec4(position, 1.0);
gl_Position = pos.xyww;//bcs we do not have z-axis, is a legal vec4 component when u will not have z
//gl_Position = projection*view*vec4(position,1.0); //original
texcor=position;
} 
