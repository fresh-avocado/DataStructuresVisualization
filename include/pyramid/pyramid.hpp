#ifndef PYRAMID_HPP_
#define PYRAMID_HPP_

#include "../glad/glad.h"
#include "../object/object.hpp"

struct Options {
  enum : std::uint8_t {
    normals = 1 << 1,
    texCoords = 1 << 2,
    borrowVBO = 1 << 3,
  };
};

const std::vector<Vertex> pyramidVertices = {
    // triangulo 1
    {glm::vec3(-0.5f, 0.0f, -0.75f), glm::vec3(0.0f, -1.0f, 0.0f),
     glm::vec2(0.0f, 0.0f)},
    {glm::vec3(-0.5f, 0.0f, 0.75f), glm::vec3(0.0f, -1.0f, 0.0f),
     glm::vec2(1.0f, 0.0f)},
    {glm::vec3(0.5f, 0.0f, -0.75f), glm::vec3(0.0f, -1.0f, 0.0f),
     glm::vec2(0.5f, 1.0f)},
    // triangulo 2
    {glm::vec3(0.5f, 0.0f, -0.75f), glm::vec3(0.0f, -1.0f, 0.0f),
     glm::vec2(0.0f, 0.0f)},
    {glm::vec3(0.5f, 0.0f, 0.75f), glm::vec3(0.0f, -1.0f, 0.0f),
     glm::vec2(1.0f, 0.0f)},
    {glm::vec3(-0.5f, 0.0f, 0.75f), glm::vec3(0.0f, -1.0f, 0.0f),
     glm::vec2(0.5f, 1.0f)},
    // triangulo 3
    {glm::vec3(-0.5f, 0.0f, -0.75f), glm::vec3(0.0f, 0.705882f, -0.470588f),
     glm::vec2(0.0f, 0.0f)},
    {glm::vec3(0.5f, 0.0f, -0.75f), glm::vec3(0.0f, 0.705882f, -0.470588f),
     glm::vec2(1.0f, 0.0f)},
    {glm::vec3(0.0f, 0.5f, 0.0f), glm::vec3(0.0f, 0.705882f, -0.470588f),
     glm::vec2(0.5f, 1.0f)},
    // triangulo 4
    {glm::vec3(-0.5f, 0.0f, -0.75f), glm::vec3(-0.705882, 0.705882, 0.000000),
     glm::vec2(0.0f, 0.0f)},
    {glm::vec3(-0.5f, 0.0f, 0.75f), glm::vec3(-0.705882, 0.705882, 0.000000),
     glm::vec2(1.0f, 0.0f)},
    {glm::vec3(0.0f, 0.5f, 0.0f), glm::vec3(-0.705882, 0.705882, 0.000000),
     glm::vec2(0.5f, 1.0f)},
    // triangulo 5
    {glm::vec3(0.5f, 0.0f, -0.75f), glm::vec3(0.705882, 0.705882, 0.000000),
     glm::vec2(0.0f, 0.0f)},
    {glm::vec3(0.5f, 0.0f, 0.75f), glm::vec3(0.705882, 0.705882, 0.000000),
     glm::vec2(1.0f, 0.0f)},
    {glm::vec3(0.0f, 0.5f, 0.0f), glm::vec3(0.705882, 0.705882, 0.000000),
     glm::vec2(0.5f, 1.0f)},
    // triangulo 6
    {glm::vec3(-0.5f, 0.0f, 0.75f), glm::vec3(0.0f, 0.705882f, 0.470588f),
     glm::vec2(0.0f, 0.0f)},
    {glm::vec3(0.5f, 0.0f, 0.75f), glm::vec3(0.0f, 0.705882f, 0.470588f),
     glm::vec2(1.0f, 0.0f)},
    {glm::vec3(0.0f, 0.5f, 0.0f), glm::vec3(0.0f, 0.705882f, 0.470588f),
     glm::vec2(0.5f, 1.0f)},
};

class Pyramid : public Object {
  static const uint8_t vertexCount = 18;
  std::uint8_t renderOptions;

 public:
  Pyramid(const std::vector<Vertex>& vertices,
          const std::vector<unsigned int>& indices,
          const std::vector<Texture>& textures,
          std::uint8_t renderOptions);

  void draw(Shader& shader, unsigned offset = 0) override;
  void borrowVBO(GLuint vboId);
  ~Pyramid() noexcept;

 private:
  void setupObject() override;
};

#endif