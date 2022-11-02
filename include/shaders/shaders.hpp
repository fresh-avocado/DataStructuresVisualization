#ifndef SHADERS_HPP_
#define SHADERS_HPP_

// clang-format off
#include <stdio.h>
#include "../glad/glad.h"
#include "../glm/glm.hpp"
#include <GLFW/glfw3.h>
// clang-format on

class Shader {
 public:
  unsigned int id;

  Shader(const char* vertexShaderPath, const char* fragmentShaderPath);
  // use/activate the shader
  void use() const;
  // utility uniform functions
  void setInt(const char* uniformName, int value) const;
  void setFloat(const char* uniformName, float value) const;
  void setVec3(const char* uniformName, const glm::vec3& value) const;
  void setVec3(const char* uniformName, float x, float y, float z) const;
  void setMat4(const char* uniformName, const glm::mat4& mat) const;
  ~Shader() noexcept;

 private:
  GLuint compileVertexAndFragment(const char* vertexShaderPath,
                                  const char* fragmentShaderPath);
};

#endif