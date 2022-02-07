#version 330 core 
layout (location=0) in vec3 position; 
layout (location=1) in vec3 colorpos; 

out vec3 vertexcolor;
out vec3 mycolor;


uniform mat4 model1;
uniform mat4 view2;

void main()  // 4 must add paranthesis
{ 
vertexcolor= colorpos;
gl_Position = model1*view2*vec4(position,1.0);	
} 