#include "textRenderer.hpp"

TextRenderer::TextRenderer() {
  // Aller_Lt.ttf
  if (FT_Init_FreeType(&ft)) {
    std::cerr << "ERROR::FREETYPE: Could not init FreeType Library"
              << "\n";
    throw "could not initialize freetype";
  }
  // if (FT_New_Face(ft, "../../assets/fonts/Aller/Aller_Bd.ttf", 0, &face)) {
  if (FT_New_Face(ft,
                  "/Users/gabrielspranger/2022-2/Grafica/Labs/OpenGL/assets/"
                  "fonts/Aller/Aller_Bd.ttf",
                  0, &face)) {
    std::cerr << "ERROR::FREETYPE: Failed to load font" << std::endl;
    throw "could not load font";
  }
  FT_Set_Pixel_Sizes(face, 0, 48);
  glPixelStorei(GL_UNPACK_ALIGNMENT,
                1);  // disable byte-alignment restriction

  for (unsigned char c = 0; c < 128; c++) {
    // load character glyph
    if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
      std::cerr << "ERROR::FREETYTPE: Failed to load Glyph"
                << "\n";
      continue;
    }
    // generate texture
    unsigned int texture;
    /* like VBO */
    glGenTextures(1, &texture);
    /* like VAO */
    glActiveTexture(GL_TEXTURE27);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, face->glyph->bitmap.width,
                 face->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE,
                 face->glyph->bitmap.buffer);
    // set texture options
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // now store character for later use
    Character character = {
        texture,
        glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
        glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
        (unsigned int)face->glyph->advance.x};
    chars.insert(std::pair<char, Character>(c, character));
  }
  FT_Done_Face(face);
  FT_Done_FreeType(ft);
  setupBuffers();
}

void TextRenderer::setupBuffers() {
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 5, NULL, GL_DYNAMIC_DRAW);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
                        (void*)(3 * sizeof(float)));
  // glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void TextRenderer::renderText(Shader& shader,
                              const std::string& text,
                              float x,
                              float y,
                              float z,
                              float scale,
                              const glm::vec3& color) {
  shader.use();
  shader.setVec3("textColor", color);
  glActiveTexture(GL_TEXTURE27);
  glBindVertexArray(VAO);

  // TODO: chapar caracter del medio y el centro de todo el texto debe ser:
  // caracterDelMedio.advance / 2.0f

  // pero ojo que cada caracter son 2 triangulos, asi q se tiene que hacer una
  // mate ahí para que el centro del rectangulo formado por dos triangulos esté
  // en cierto lugars

  // origin position of the quad (as xpos and ypos) and the quad's size (as w
  // and h)

  // iterate through all characters
  for (auto c : text) {
    Character ch = chars[c];

    float xpos = x + ch.bearing.x * scale;
    float ypos = y - (ch.size.y - ch.bearing.y) * scale;

    float w = ch.size.x * scale;
    float h = ch.size.y * scale;
    // update VBO for each character
    float vertices[6][5] = {
        {xpos, ypos + h, z, 0.0f, 0.0f},    {xpos, ypos, z, 0.0f, 1.0f},
        {xpos + w, ypos, z, 1.0f, 1.0f},

        {xpos, ypos + h, z, 0.0f, 0.0f},    {xpos + w, ypos, z, 1.0f, 1.0f},
        {xpos + w, ypos + h, z, 1.0f, 0.0f}};
    // render glyph texture over quad
    glBindTexture(GL_TEXTURE_2D, ch.textureId);
    // update content of VBO memory
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferSubData(
        GL_ARRAY_BUFFER, 0, sizeof(vertices),
        vertices);  // be sure to use glBufferSubData and not glBufferData

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    // render quad
    glDrawArrays(GL_TRIANGLES, 0, 6);
    // now advance cursors for next glyph (note that advance is number of 1/64
    // pixels)
    x += (ch.advance >> 6) *
         scale;  // bitshift by 6 to get value in pixels (2^6 = 64 (divide
                 // amount of 1/64th pixels by 64 to get amount of pixels))
  }
}