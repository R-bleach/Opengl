#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec3 aColor;
layout (location = 3) in vec2 aTex;


out vec3 crntPos;
out vec3 Normal;
out vec3 color;
out vec2 texCoord;



uniform mat4 camMatrix; 
uniform mat4 model;

void main()
{
   crntPos = vec3(model * vec4(aPos,1.f));
   Normal = aNormal;

   gl_Position = camMatrix * vec4(crntPos,1.0);
   color = aColor;
   texCoord = aTex;
  
}