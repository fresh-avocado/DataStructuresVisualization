#ifndef VERTEX_HPP_
#define VERTEX_HPP_

#include "../glm/glm.hpp"

struct Vertex {
  glm::vec3 position;
  glm::vec3 normal;
  glm::vec2 texCoords;
};

#endif