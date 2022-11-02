// clang-format off
#include "include/glad/glad.h"
#include <GLFW/glfw3.h>
#include "include/glm/glm.hpp"
#include "include/glm/gtc/matrix_transform.hpp"
#include "include/glm/gtc/type_ptr.hpp"
#include "include/shaders/shaders.hpp"
#include "include/model/model.hpp"
#include "include/shaders/shaders.hpp"
#include "include/pyramid/pyramid.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "include/window/window.hpp"
#include "include/line/line.hpp"
#include "include/bst/BST.hpp"
#include "include/textRenderer/textRenderer.hpp"
// clang-format on

#include <pthread.h>
#include <iostream>

// settings
GLint ambientStrengthLoc;
float ambientStrength = 0.1f;

glm::vec3 cameraPos = glm::vec3(2.752718, -2.891845, 20.667009);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
float cameraSpeed = 3.5f;
float unitsPerSecond = 4.5f;
bool firstMouse = true;
float fov = 45.0f;

float lastX;
float lastY;

float yaw = 260.f;
float pitch = 0.0f;

void* handleUserInput(void* bts) {
  pthread_detach(pthread_self());
  BST* bst = (BST*)bts;
  std::string command;
  while (1) {
    std::cout << "\033[41;33m=====MENU=====\033[0m\n";
    std::cout << "\033[4;33mclear (c):\033[0m remove all nodes from BST\n";
    std::cout << "\033[4;36minsert (i):\033[0m insert an integer value into "
                 "the BST\n";
    std::cin >> command;
    if (command == "clear" or command == "c") {
      bst->clear();
      std::cout << "\033[4;33mcleared!\033[0m"
                << "\n";
    } else if (command == "insert" or command == "i") {
      int value;
      std::cout << "\033[4;36mvalue to insert:\033[0m ";
      std::cin >> value;
      bst->insert(value);
    }
  }
  return NULL;
}

int main() {
  Window window(800, 600);
  lastX = (float)window.width / 2.0f;
  lastY = (float)window.height / 2.0f;

  BST bst = BST();
  // bst.insert(10);
  // bst.insert(9);
  // bst.insert(1);
  // bst.insert(3);
  // bst.insert(7);
  // bst.insert(30);
  // bst.insert(25);
  // // bst.insert(5);
  // bst.insert(2);
  // bst.insert(100);

  // bst.insert(-5);
  // bst.insert(-10);
  // bst.insert(-3);

  pthread_t userCommandThread;
  int s =
      pthread_create(&userCommandThread, NULL, handleUserInput, (void*)&bst);
  if (s != 0) {
    printf("userCommandThread thread creation failed\n");
    return -1;
  }

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD"
              << "\n";
    return -1;
  }

  glActiveTexture(GL_TEXTURE30);
  GLuint texture1 = textureFromFile("./assets/images/container.jpeg");
  glActiveTexture(GL_TEXTURE31);
  GLuint texture2 = textureFromFile("./assets/images/awesomeface.png");

  Shader objectShader = Shader("./include/shaders/vertexShader.vs",
                               "./include/shaders/fragmentShader.fs");
  Shader lightShader = Shader("./include/shaders/vertexShader.vs",
                              "./include/shaders/lightFragmentShader.fs");
  Shader modelShader = Shader("./include/shaders/vertexShader.vs",
                              "./include/shaders/modelFragmentShader.fs");
  Shader lineShader = Shader("./include/shaders/simpleVertexShader.vs",
                             "./include/shaders/simpleFragmentShader.fs");
  Shader textShader = Shader("./include/shaders/textVertexShader.vs",
                             "./include/shaders/textFragmentShader.fs");

  TextRenderer textRenderer = TextRenderer();

  const std::vector<Texture> pyramidTextures = {
      {texture1, "texture_diffuse", ""},
      {texture2, "texture_diffuse", ""},
  };

  Pyramid pyramid = {pyramidVertices,
                     {},
                     pyramidTextures,
                     Options::normals | Options::texCoords};
  Pyramid lightPyramid = {pyramidVertices, {}, pyramidTextures, 0};
  lightPyramid.borrowVBO(pyramid.VBO);

  glm::vec3 lightPos(4.298038f, -2.891845f, 29.430952f);

  // TODO: indexed drawing
  Line line1{{
      lightPos,
      glm::vec3(2.0f, 2.0f, 2.0f),
      glm::vec3(2.0f, 2.0f, 2.0f),
      glm::vec3(4.0f, 4.0f, 4.0f),
      glm::vec3(4.0f, 4.0f, 4.0f),
      glm::vec3(6.0f, 6.0f, 6.0f),
  }};

  // descomentar para dibujar solo el contorno de los primitivos
  // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  glm::mat4 model = glm::mat4(1.0f);
  glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
  glm::mat4 projection =
      glm::perspective(glm::radians(fov), window.aspectRatio, 0.1f, 100.0f);

  objectShader.use();
  objectShader.setMat4("model", model);
  objectShader.setMat4("view", view);
  objectShader.setMat4("projection", projection);
  objectShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
  objectShader.setFloat("ambientStrength", ambientStrength);
  objectShader.setVec3("lightPos", lightPos);
  objectShader.setVec3("viewPos", 0.0f, 0.0f, 20.0f);
  objectShader.setInt("texture_diffuse1", 30);
  objectShader.setInt("texture_diffuse2", 31);

  lightShader.use();
  lightShader.setMat4("view", view);
  lightShader.setMat4("projection", projection);

  modelShader.use();
  // modelShader.setMat4("model", model);
  // modelShader.setMat4("view", view);
  // modelShader.setMat4("projection", projection);
  modelShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
  modelShader.setFloat("ambientStrength", ambientStrength);
  modelShader.setVec3("lightPos", lightPos);
  modelShader.setVec3("viewPos", 0.0f, 0.0f, 20.0f);

  lineShader.use();
  lineShader.setMat4("model", model);
  lineShader.setMat4("view", view);
  lineShader.setMat4("projection", projection);

  textShader.use();
  textShader.setMat4("projection", projection);
  textShader.setInt("text", 27);

  // TODO: chequear
  glm::vec3 pyramidPositions[] = {
      glm::vec3(-0.95f, 0.95f, -1.0f),  glm::vec3(-0.95f, 0.0f, -1.0f),
      glm::vec3(-0.95f, -0.95f, -1.0f), glm::vec3(0.0f, 0.95f, -1.0f),
      glm::vec3(0.0f, 0.0f, -1.0f),     glm::vec3(0.0f, -0.95f, -1.0f),
      glm::vec3(0.95f, 0.95f, -1.0f),   glm::vec3(0.95f, 0.0f, -1.0f),
      glm::vec3(0.95f, -0.95f, -1.0f),
  };

  glm::vec3 pyramidColors[] = {
      glm::vec3(0.6f, 0.6f, 0.7f), glm::vec3(0.4f, 0.4f, 0.7f),
      glm::vec3(0.2f, 0.2f, 0.7f), glm::vec3(0.6f, 0.6f, 0.7f),
      glm::vec3(0.7f, 0.7f, 0.6f), glm::vec3(0.8f, 0.8f, 0.6f),
      glm::vec3(0.2f, 0.7f, 0.2f), glm::vec3(0.7f, 0.2f, 0.2f),
      glm::vec3(0.4f, 0.2f, 0.2f),
  };

  Model sphereModel("./assets/models/sphere.blend");

  float lastFrame = 0.0f;
  float deltaTime = 0.0f;

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  while (!glfwWindowShouldClose(window._window)) {
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
    cameraSpeed = unitsPerSecond * deltaTime;
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(direction);

    view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
    projection =
        glm::perspective(glm::radians(fov), window.aspectRatio, 0.1f, 100.0f);

    // NOTE: lineas
    lineShader.use();
    lineShader.setMat4("view", view);
    lineShader.setMat4("projection", projection);
    lineShader.setVec3("lineColor", glm::vec3(1.0f, 0.0f, 0.0f));
    line1.draw(lineShader, 0);
    lineShader.setVec3("lineColor", glm::vec3(1.0f, 1.0f, 0.0f));
    line1.draw(lineShader, 2);
    lineShader.setVec3("lineColor", glm::vec3(0.0f, 0.0f, 1.0f));
    line1.draw(lineShader, 4);

    // NOTE: triangulos
    objectShader.use();
    objectShader.setMat4("projection", projection);
    objectShader.setMat4("view", view);

    for (unsigned int i = 0; i < 9; i++) {
      glm::mat4 modelMatrix = glm::mat4(1.0f);
      modelMatrix = glm::translate(modelMatrix, pyramidPositions[i]);
      modelMatrix =
          glm::rotate(modelMatrix, (float)glfwGetTime() * glm::radians(10.0f),
                      glm::vec3(0.5f, 1.0f, 1.0f));
      modelMatrix = glm::scale(modelMatrix, glm::vec3(0.8f));
      objectShader.setMat4("model", modelMatrix);
      glm::vec3 pColor = pyramidColors[i];
      objectShader.setVec3("pyramidColor", pColor);
      pyramid.draw(objectShader);
    }

    textShader.use();
    textShader.setMat4("projection", projection);
    textShader.setMat4("view", view);
    textShader.setMat4("model", glm::mat4(1.0f));

    // NOTE: models
    modelShader.use();
    modelShader.setMat4("projection", projection);
    modelShader.setMat4("view", view);

    // NOTE: nodos
    for (auto& vertice : bst.vertices) {
      auto [key, tuple] = vertice;
      auto [x, y, z, colorDraw] = tuple;
      glm::mat4 modelMatrix = glm::mat4(1.0f);
      modelMatrix = glm::translate(modelMatrix, glm::vec3(x, y, z));
      modelMatrix = glm::scale(modelMatrix, glm::vec3(0.4f));
      modelShader.use();
      modelShader.setMat4("model", modelMatrix);
      modelShader.setVec3("color", glm::vec3(0.0f, 1.0f, 0.0f));
      sphereModel.draw(modelShader);
      if (colorDraw == red) {
        textRenderer.renderText(textShader, std::to_string(key), x, y, z + 0.5f,
                                0.01f, glm::vec3(1.0f, 0.0f, 0.0f));

      } else if (colorDraw == white) {
        textRenderer.renderText(textShader, std::to_string(key), x, y, z + 0.5f,
                                0.01f, glm::vec3(1.0f, 1.0f, 1.0f));
      }
    }

    lineShader.use();
    lineShader.setVec3("lineColor", glm::vec3(0.0f, 1.0f, 0.0f));

    // NOTE: aristas
    for (auto& arista : bst.aristas) {
      auto [v1, v2] = arista;
      auto [x1, y1, z1] = v1;
      auto [x2, y2, z2] = v2;
      // TODO: optimizar esta dibujada xq esta creando un VAO por cada arista (y
      // mandando el VBO al GPU)
      Line edge{{
          glm::vec3(x1, y1, z1),
          glm::vec3(x2, y2, z2),
      }};
      edge.draw(lineShader);
    }

    // NOTE: light source
    lightShader.use();
    lightShader.setMat4("projection", projection);
    lightShader.setMat4("view", view);

    model = glm::mat4(1.0f);
    model = glm::translate(model, lightPos);
    model = glm::scale(model, glm::vec3(0.4f));
    lightShader.setMat4("model", model);
    lightPyramid.draw(lightShader);

    // NOTE: render
    glfwSwapBuffers(window._window);
    glfwPollEvents();
  }

  // NOTE: cleanup
  glDeleteTextures(1, &texture1);
  glDeleteTextures(1, &texture2);
  return 0;
}
