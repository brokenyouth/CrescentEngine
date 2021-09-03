#version 450 core
out vec4 FragColor;

struct Material {
    sampler2D diffuse;
    sampler2D specular;    
    float shininess;
}; 

struct Light {
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float intensity;
};

in vec3 Position;  
in vec3 Normal;  
in vec2 TexCoord;

uniform vec3 cameraPosition;
uniform Material material;
uniform Light light;

void main()
{
	vec4 texColor = texture(material.diffuse, TexCoord);
	if (texColor.a < 0.1)
		discard;
    // ambient
    vec3 ambient = light.ambient * texColor.rgb;
  	
    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(-light.direction);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * texColor.rgb;  
    
    // specular
    vec3 viewDir = normalize(cameraPosition - Position);
    vec3 reflectDir = reflect(-lightDir, norm);  
    
	vec3 halfDir = normalize(lightDir + viewDir);
	float spec = pow(max(dot(norm, halfDir), 0.0), material.shininess);
	vec3 specular = light.specular * light.intensity * spec * texture(material.specular, TexCoord).rgb;

    
    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
} 