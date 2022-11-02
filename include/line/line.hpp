#ifndef LINE_HPP_
#define LINE_HPP_

#include "../object/object.hpp"

class Line : public Object {
 public:
  // TODO: pair<glm::vec3, glm::vec3>
  typedef glm::vec3 LineVertex;
  Line(const std::vector<LineVertex>& lineVertices,
       const std::vector<unsigned int>& indices = {},
       const std::vector<Texture>& textures = {});
  void draw(Shader& shader, unsigned offset = 0) override;
  void borrowVBO(GLuint vboId);
  ~Line() noexcept;

 private:
  static const uint8_t vertexCount = 2;
  bool vboBorrowed = false;
  std::vector<LineVertex> lineVertices;
  void setupObject() override;
};

#endif