#ifndef TEXT_RENDERER_HPP_
#define TEXT_RENDERER_HPP_

#include <ft2build.h>
#include <iostream>
#include <map>
#include "../glad/glad.h"
#include "../glm/glm.hpp"
#include "../shaders/shaders.hpp"
#include FT_FREETYPE_H

class TextRenderer {
  FT_Library ft;
  FT_Face face;
  GLuint VAO, VBO;

  struct Character {
    unsigned int textureId;  // ID handle of the glyph texture
    glm::ivec2 size;         // Size of glyph
    glm::ivec2 bearing;      // Offset from baseline to left/top of glyph
    unsigned int advance;    // Offset to advance to next glyph
  };

  std::map<char, Character> chars;
  void setupBuffers();

 public:
  TextRenderer();
  void renderText(Shader& shader,
                  const std::string& text,
                  float x,
                  float y,
                  float z,
                  float scale,
                  const glm::vec3& color);
};

#endif