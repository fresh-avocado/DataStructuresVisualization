#include <fstream>

#include "shaders.hpp"

Shader::Shader(const char* vertexShaderPath, const char* fragmentShaderPath) {
  id = compileVertexAndFragment(vertexShaderPath, fragmentShaderPath);
}

void Shader::use() const {
  glUseProgram(id);
}

void Shader::setInt(const char* uniformName, int value) const {
  glUniform1i(glGetUniformLocation(id, uniformName), value);
}

void Shader::setFloat(const char* uniformName, float value) const {
  glUniform1f(glGetUniformLocation(id, uniformName), value);
}

void Shader::setVec3(const char* uniformName, const glm::vec3& value) const {
  glUniform3fv(glGetUniformLocation(id, uniformName), 1, &value[0]);
}

void Shader::setVec3(const char* uniformName, float x, float y, float z) const {
  glUniform3f(glGetUniformLocation(id, uniformName), x, y, z);
}

void Shader::setMat4(const char* uniformName, const glm::mat4& mat) const {
  glUniformMatrix4fv(glGetUniformLocation(id, uniformName), 1, GL_FALSE,
                     &mat[0][0]);
}

GLuint Shader::compileVertexAndFragment(const char* vertexShaderPath,
                                        const char* fragmentShaderPath) {
  std::ifstream vsFile{vertexShaderPath};
  if (!vsFile)
    throw "could not open vertex shader file";
  std::ifstream fsFile{fragmentShaderPath};
  if (!fsFile)
    throw "could not open fragment shader file";
  std::string line;
  std::string vertexShader, fragmentShader;
  while (vsFile) {
    std::getline(vsFile, line);
    vertexShader += line;
    vertexShader += "\n";
  }
  while (fsFile) {
    std::getline(fsFile, line);
    fragmentShader += line;
    fragmentShader += "\n";
  }
  const char* vertexShaderString = vertexShader.c_str();
  const char* fragmentShaderString = fragmentShader.c_str();

  unsigned int vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShaderId, 1, &vertexShaderString, NULL);
  glCompileShader(vertexShaderId);
  // check for shader compile errors
  int success;
  char infoLog[512];
  glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertexShaderId, 512, NULL, infoLog);
    printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n%s\n", infoLog);
  }
  // fragment shader
  unsigned int fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShaderId, 1, &fragmentShaderString, NULL);
  glCompileShader(fragmentShaderId);
  // check for shader compile errors
  glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fragmentShaderId, 512, NULL, infoLog);
    printf("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n%s\n", infoLog);
  }
  // link shaders
  GLuint shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShaderId);
  glAttachShader(shaderProgram, fragmentShaderId);
  glLinkProgram(shaderProgram);
  // check for linking errors
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    printf("ERROR::SHADER::PROGRAM::LINKING_FAILED\n%s\n", infoLog);
  }
  glDeleteShader(vertexShaderId);
  glDeleteShader(fragmentShaderId);
  return shaderProgram;
}

Shader::~Shader() noexcept {
  glDeleteProgram(id);
}