#ifndef HELPERS_HPP_
#define HELPERS_HPP_

#include <iostream>
#include "../glad/glad.h"
#include "../stbi/stbi.h"

GLuint textureFromFile(const char* path, bool gamma = false);

#endif