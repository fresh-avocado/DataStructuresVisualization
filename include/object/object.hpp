#ifndef OBJECT_HPP_
#define OBJECT_HPP_

#include <vector>
#include "../glm/glm.hpp"
#include "../shaders/shaders.hpp"
#include "../texture/texture.hpp"
#include "../vertex/vertex.hpp"

class Object {
 public:
  // mesh data
  std::vector<Vertex> vertices;
  std::vector<unsigned int> indices;
  std::vector<Texture> textures;
  /* buffer with vertices + configuration + (optional) indices */
  unsigned int VAO = -1;
  /* buffer */
  unsigned int VBO = -1;
  /* indices buffer */
  unsigned int EBO = -1;

  Object(const std::vector<Vertex>& vertices,
         const std::vector<unsigned int>& indices,
         const std::vector<Texture>& textures)
      : vertices{vertices}, indices{indices}, textures{textures} {}
  virtual void draw(Shader& shader, unsigned offset = 0) = 0;

 private:
  virtual void setupObject() = 0;
  void setModelMatrix(Shader& shader, glm::mat4 modelMatrix) {
    shader.use();
    shader.setMat4("model", modelMatrix);
  };
  void setViewMatrix(Shader& shader, glm::mat4 viewMatrix) {
    shader.use();
    shader.setMat4("view", viewMatrix);
  };
  void setProjectionMatrix(Shader& shader, glm::mat4 projectionMatrix) {
    shader.use();
    shader.setMat4("projection", projectionMatrix);
  };
};

#endif