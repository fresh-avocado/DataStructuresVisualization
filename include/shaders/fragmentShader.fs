#version 330 core

in vec3 normal;
in vec3 fragPos;
in vec2 TexCoord;

uniform vec3 pyramidColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;
uniform float ambientStrength;
uniform sampler2D texture_diffuse1;
uniform sampler2D texture_diffuse2;

out vec4 FragColor;
  
void main()
{
  // ambient
  vec4 ambient = vec4(ambientStrength * lightColor, 1.0);
  
  // diffuse 
  vec3 norm = normalize(normal);
  vec3 lightDir = normalize(lightPos - fragPos);
  float diff = max(dot(norm, lightDir), 0.0);
  vec4 diffuse = vec4(diff * lightColor, 1.0);
  
  // specular
  float specularStrength = 0.9;
  vec3 viewDir = normalize(viewPos - fragPos);
  // TODO: como esto no toma en cuenta intersecciones, se ve especular aun asi de espalda a la luz
  vec3 reflectDir = reflect(-lightDir, norm);  
  float spec = pow(max(dot(viewDir, reflectDir), 0.0), 256);
  vec4 specular = vec4(specularStrength * spec * lightColor, 1.0);  
  
  vec4 objectColor = mix(texture(texture_diffuse1, TexCoord), texture(texture_diffuse2, TexCoord), 0.2) * vec4(pyramidColor, 1.0);
  FragColor = (ambient + diffuse + specular) * objectColor;
}
