#version 330 core
out vec4 fragData;

in vec3 normal;
in vec3 pos;

uniform vec3 camerapos;
uniform samplerCube skybox;

void main()
{
    //reflection
    vec3 I=normalize(pos-camerapos);
    vec3 R=reflect(I,normalize(normal));
    fragData=vec4(texture(skybox,R).rgb,1.0);
    

    /*//refraction must have refraction function having 3 parameter
    float ratio = 1.00 / 1.52;
    vec3 I=normalize(pos-camerapos);
    vec3 R=refract(I,normalize(normal),ratio);
    fragData=vec4(texture(skybox,R).rgb,1.0);*/
}