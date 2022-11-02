#ifndef TEXTURE_HPP_
#define TEXTURE_HPP_

#include <string>

struct Texture {
  unsigned int id;
  std::string type;
  std::string
      path;  // we store the path of the texture to compare with other textures
};

#endif