#include "pyramid.hpp"

Pyramid::Pyramid(const std::vector<Vertex>& vertices,
                 const std::vector<unsigned int>& indices,
                 const std::vector<Texture>& textures,
                 std::uint8_t renderOptions)
    : Object(vertices, indices, textures), renderOptions{renderOptions} {
  setupObject();
};

void Pyramid::borrowVBO(GLuint vboId) {
  VBO = vboId;
  renderOptions |= Options::borrowVBO;
};

void Pyramid::setupObject() {
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);

  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);

  Vertex* verticesStart = &vertices[0];

  if ((renderOptions & Options::borrowVBO) == 0) {
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex),
                 verticesStart, GL_STATIC_DRAW);
  }

  // vertex positions
  glEnableVertexAttribArray(0); // of layout 0
  // vertex has 3 vertex attributes, each one 3 FLOATS
  // GL_FALSE: sin normalizar
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
  // vertex normals
  if (renderOptions & Options::normals) {
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (void*)offsetof(Vertex, normal));
  }

  if (renderOptions & Options::texCoords) {
    // vertex texture coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (void*)offsetof(Vertex, texCoords));
  }
}

void Pyramid::draw(Shader& shader, unsigned offset) {
  unsigned int diffuseNr = 1;
  unsigned int specularNr = 1;
  std::string number, name;
  for (unsigned int i = 0; i < textures.size(); i++) {
    glActiveTexture(GL_TEXTURE0 + i);
    name = textures[i].type;
    if (name == "texture_diffuse")
      number = std::to_string(diffuseNr++);
    else if (name == "texture_specular")
      number = std::to_string(specularNr++);
    shader.setInt((name + number).c_str(), i);
    glBindTexture(GL_TEXTURE_2D, textures[i].id);
  }
  // glActiveTexture(GL_TEXTURE0);

  glBindVertexArray(VAO);
  // FIXME: no debería ser vertexCount, debería ser otro
  // for triangles: multiple of 3
  glDrawArrays(GL_TRIANGLES, 0, vertexCount);
}

Pyramid::~Pyramid() noexcept {
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
