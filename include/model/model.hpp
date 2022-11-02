#ifndef MODEL_HPP_
#define MODEL_HPP_

#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <vector>
#include "../helpers/helpers.hpp"
#include "../mesh/mesh.hpp"
#include "../shaders/shaders.hpp"
#include "../texture/texture.hpp"

class Model {
 public:
  Model(const char* path);
  void draw(Shader& shader);

 private:
  // model data
  std::vector<Texture> texturesLoaded;
  std::vector<Mesh> meshes;
  std::string directory;

  void loadModel(const std::string& path);
  void processNode(aiNode* node, const aiScene* scene);
  Mesh processMesh(aiMesh* mesh, const aiScene* scene);
  std::vector<Texture> loadMaterialTextures(aiMaterial* mat,
                                            aiTextureType type,
                                            const std::string& typeName);
};

#endif