#version 330 core
out vec4 FragColor;

in vec3 color;
in vec2 texCoord;

in vec3 normal;
in vec3 crntPos;

uniform sampler2D tex0;

uniform vec4 lightColor;
uniform vec3 lightPos;
uniform vec3 camPos;

void main()
{
	float ambient = 0.2f;

	vec3 unitNormal = normalize(normal);
	vec3 lightDir = normalize(lightPos - crntPos);

	float diffuse = max(dot(lightDir, unitNormal), 0.0f);

	float specularLight = 1.0f;

	vec3 viewDir = normalize(camPos - crntPos);
	vec3 reflectDir = reflect(-lightDir, unitNormal);
	float specAmount = pow(max(dot(viewDir, reflectDir), 0.0f), 8);
	float specular = specAmount * specularLight;


	FragColor = texture(tex0, texCoord) * lightColor * (diffuse + ambient + specular);
};