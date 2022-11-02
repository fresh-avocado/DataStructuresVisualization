#version 330 core
layout (location = 0) in vec3 textPos;
layout (location = 1) in vec2 textureCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec2 TexCoords;

void main()
{
  gl_Position = projection * view * model * vec4(textPos, 1.0);
  TexCoords = textureCoords;
}
