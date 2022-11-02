#ifndef WINDOW_HPP_
#define WINDOW_HPP_

// clang-format off
#include "../glad/glad.h"
#include "../glm/glm.hpp"
#include "../stbi/stbi.h"
#include <GLFW/glfw3.h>
#include <iostream>
// clang-format on

class Window {
 public:
  GLFWwindow* _window;
  unsigned width, height;
  float aspectRatio;
  Window(unsigned width, unsigned height);
  ~Window() noexcept;

 private:
  void setCallbacks();
  void setWindowIcon(const char* path);
  static void framebufferSizeCallback(GLFWwindow* window,
                                      int width,
                                      int height);
  static void keyCallback(GLFWwindow* window,
                          int key,
                          int scancode,
                          int action,
                          int mods);
  static void scrollCallback(GLFWwindow* window,
                             double xoffset,
                             double yoffset);
  static void dropCallback(GLFWwindow* window, int count, const char** paths);
  static void mouseButtonCallback(GLFWwindow* window,
                                  int button,
                                  int action,
                                  int mods);
  static void cursorEnterCallback(GLFWwindow* window, int entered);
  static void cursorPositionCallback(GLFWwindow* window,
                                     double xpos,
                                     double ypos);
  static void characterCallback(GLFWwindow* window, unsigned int codepoint);
  static void windowIconifyCallback(GLFWwindow* window, int iconified);
};

#endif