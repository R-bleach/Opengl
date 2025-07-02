#version 330 core
out vec4 FragColor;

in vec3 crntPos;
in vec3 Normal;
in vec3 color;
in vec2 texCoord;



uniform sampler2D diffuse0;
uniform sampler2D specular0;
uniform vec4 lightColor;
uniform vec3 lightPos;
uniform vec3 camPos;


vec4 pointLight()
{
	vec3 lightVec = lightPos-crntPos;
	float dist = length(lightVec); 
	float a = 3.0f;
	float b = 0.7f;
	float attenuation = 1.f/(a*dist*b*dist*dist + 1.f);


	float ambient = 0.2f;

	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(lightVec);

	float diffuse = max(dot(normal, lightDirection),0.0f);


	float specLight = 0.5f;
	vec3 viewDirection = normalize(camPos - crntPos);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection),0.f),16);
	float specular = specAmount*specLight;

	return (texture(diffuse0, texCoord) * (diffuse* attenuation + ambient) + texture(specular0, texCoord).r * specular * attenuation) * lightColor;
}

vec4 directLight()
{
	float ambient = 0.2f;

	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(vec3(1.f,1.f,0.f));

	float diffuse = max(dot(normal, lightDirection),0.0f);


	float specLight = 0.5f;
	vec3 viewDirection = normalize(camPos - crntPos);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection),0.f),16);
	float specular = specAmount*specLight;

	return (texture(diffuse0, texCoord) * (diffuse + ambient) + texture(specular0, texCoord).r * specular) * lightColor;
}

vec4 spotLight()
{
	vec3 lightVec = lightPos-crntPos;

	float outerCone = 0.9f;
	float innerCone = 0.95f;
	float ambient = 0.2f;

	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(lightVec);

	float diffuse = max(dot(normal, lightDirection),0.0f);


	float specLight = 0.5f;
	vec3 viewDirection = normalize(camPos - crntPos);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection),0.f),16);
	float specular = specAmount*specLight;

	float angle = dot(vec3(0.f, -1.f, 0.f), -lightDirection);
	float inten = clamp((angle-outerCone)/(innerCone-outerCone),0.f,1.f);

	return (texture(diffuse0, texCoord) * (diffuse * inten + ambient) + texture(specular0, texCoord).r * specular* inten) * lightColor;
}

void main()
{
   FragColor = spotLight();
};