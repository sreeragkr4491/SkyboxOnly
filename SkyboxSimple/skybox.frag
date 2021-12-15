#version 330 core 
out vec4 Temp;
in vec3 texcor;
//in vec3 vertexcolor;
uniform samplerCube skybox;

void main()  //5 must add paranthesis
{
Temp =texture(skybox,texcor);
} 
