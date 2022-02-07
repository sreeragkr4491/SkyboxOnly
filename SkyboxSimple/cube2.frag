#version 330 core 

in vec3 normal;
in vec3 fragPosition;
uniform vec3 lightposition;

uniform vec3 viewPosition;
out vec4 Kr;
uniform vec3 objcolor;
uniform vec3 lgtcolor;
in vec3 vertexcolor;

//material
struct material{
vec3 ambient,diffuse,specular;
float shininess;
};

//light
struct light{
vec3 ambient,diffuse,specular,position;
};

uniform material mat;
uniform light lgt;

void main()  
{
//ambient
vec3 ambient = mat.ambient*lgt.ambient;

//diffuse
vec3 norm2 = normalize(normal);
vec3 lightDirection = normalize(lgt.position - fragPosition);
float diff = max(dot(norm2,lightDirection),0.0);
vec3 diffuse = lgt.diffuse*(diff*mat.diffuse);

//specular
//float strnspec=60;
vec3 dirview=normalize(viewPosition-fragPosition);
vec3 viewreflectdir=reflect(-lightDirection,norm2);
float spec1=pow(max(dot(dirview,viewreflectdir),0.0),mat.shininess);
vec3 specular=lgt.specular*(spec1*mat.specular);


vec3 result=(ambient+diffuse+specular);
Kr =vec4(result,1.0);
} 