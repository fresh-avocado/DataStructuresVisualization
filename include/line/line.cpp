#include "line.hpp"

Line::Line(const std::vector<Line::LineVertex>& lineVertices,
           const std::vector<unsigned int>& indices,
           const std::vector<Texture>& textures)
    : Object({}, indices, textures), lineVertices{lineVertices} {
  setupObject();
};

void Line::borrowVBO(GLuint vboId) {
  VBO = vboId;
  vboBorrowed = true;
};

void Line::setupObject() {
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);

  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);

  if (!vboBorrowed) {
    glBufferData(GL_ARRAY_BUFFER,
                 lineVertices.size() * sizeof(Line::LineVertex),
                 &lineVertices[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    // NOTE: estan consecutivos por eso el stride es 0
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
  } else {
    // FIXME: creo q igual no se debería usar esta opción
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
  }
}

void Line::draw(Shader& shader, unsigned offset) {
  glBindVertexArray(VAO);
  // TODO: dibujar todos los vertices
  glDrawArrays(GL_LINES, offset, vertexCount);
}

Line::~Line() noexcept {
  if (VBO != -1u) {
    glDeleteBuffers(1, &VBO);
  }
  if (EBO != -1u) {
    glDeleteBuffers(1, &EBO);
  }
  if (VAO != -1u) {
    glDeleteVertexArrays(1, &VAO);
  }
}
