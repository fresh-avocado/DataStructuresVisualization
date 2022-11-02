#ifndef MESH_HPP_
#define MESH_HPP_

#include <vector>

#include "../texture/texture.hpp"
#include "../vertex/vertex.hpp"

// clang-format off
#include "../glad/glad.h"
#include "../shaders/shaders.hpp"
#include "../object/object.hpp"
#include <GLFW/glfw3.h>
// clang-format on

class Mesh : public Object {
 public:
  Mesh(const std::vector<Vertex>& vertices,
       const std::vector<unsigned int>& indices,
       const std::vector<Texture>& textures);

  void draw(Shader& shader, unsigned offset = 0) override;

 private:
  void setupObject() override;
};

#endif