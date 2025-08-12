#version 330 core
out vec4 FragColor;

in vec3 crntPos;
in vec3 normal;
in vec3 color;
in vec2 texCoord;

uniform sampler2D diffuse0;
uniform sampler2D specular0;

uniform vec4 lightColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
uniform vec3 lightPos = vec3(2.0f, 0.0f, 0.0f);
uniform vec3 camPos;

vec4 pointLight(float a, float b)
{
	vec3 lightVec = lightPos - crntPos;
	float dist = length(lightVec);
	float intensity = 1 / (a * dist * dist + b * dist + 1);

	float ambient = 0.2f;

	vec3 unitNormal = normalize(normal);
	vec3 lightDir = normalize(lightVec);

	float diffuse = max(dot(lightDir, unitNormal), 0.0f);

	float specularLight = 1.0f;

	vec3 viewDir = normalize(camPos - crntPos);
	vec3 reflectDir = reflect(-lightDir, unitNormal);
	float specAmount = pow(max(dot(viewDir, reflectDir), 0.0f), 16);
	float specular = specAmount * specularLight;

	return (texture(diffuse0, texCoord) * lightColor * (diffuse * intensity + ambient) + (1 - texture(specular0, texCoord).r) * specular * intensity) * lightColor;
}

vec4 directionalLight(vec3 dir)
{
	float ambient = 0.2f;

	vec3 unitNormal = normalize(normal);
	vec3 lightDir = normalize(dir);

	float diffuse = max(dot(lightDir, unitNormal), 0.0f);

	float specularLight = 1.0f;

	vec3 viewDir = normalize(camPos - crntPos);
	vec3 reflectDir = reflect(-lightDir, unitNormal);
	float specAmount = pow(max(dot(viewDir, reflectDir), 0.0f), 16);
	float specular = specAmount * specularLight;

	return (texture(diffuse0, texCoord) * lightColor * (diffuse + ambient) + (1 - texture(specular0, texCoord).r) * specular) * lightColor;
}

vec4 spotLight(float outerCone, float innerCone, vec3 dir)
{	
	float ambient = 0.2f;

	vec3 unitNormal = normalize(normal);
	vec3 lightDir = normalize(lightPos - crntPos);

	float diffuse = max(dot(lightDir, unitNormal), 0.0f);

	float specularLight = 1.0f;

	vec3 viewDir = normalize(camPos - crntPos);
	vec3 reflectDir = reflect(-lightDir, unitNormal);
	float specAmount = pow(max(dot(viewDir, reflectDir), 0.0f), 16);
	float specular = specAmount * specularLight;

	float angle = dot(dir, -lightDir);
	float intensity = clamp((angle - outerCone) / (innerCone - outerCone), 0, 1);

	return (texture(diffuse0, texCoord) * lightColor * (diffuse * intensity + ambient) + (1 - texture(specular0, texCoord).r) * specular * intensity) * lightColor;
}

void main()
{
	FragColor = pointLight(1.1f, 0.05f);
};