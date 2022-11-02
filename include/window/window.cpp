#include "window.hpp"

#define WINDOW_W 119
#define WINDOW_A 97
#define WINDOW_S 115
#define WINDOW_D 100
#define WINDOW_Q 113
#define WINDOW_E 101

// TODO: Window debería tener una referencia a la cámara
extern glm::vec3 cameraPos;
extern glm::vec3 cameraFront;
extern glm::vec3 cameraUp;
extern float cameraSpeed;
const float sensitivity = 0.1f;
extern float lastY, lastX;
extern float yaw, pitch;
extern bool firstMouse;
extern float fov;

Window::Window(unsigned width, unsigned height) : width{width}, height{height} {
  aspectRatio = (float)width / (float)height;

  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  _window = glfwCreateWindow(width, height, "OpenGL Basics", NULL, NULL);
  if (_window == NULL) {
    std::cout << "Failed to create GLFW window"
              << "\n";
    glfwTerminate();
    return;
  }
  glfwMakeContextCurrent(_window);
  const char* text = glfwGetClipboardString(NULL);
  printf("tu portapapeles tiene: %s\n", text ? text : "NULL");
  glfwSetClipboardString(
      NULL,
      "https://www.youtube.com/watch?v=gDjMZvYWUdo&ab_channel=Itsnickford");
  glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  setCallbacks();
  setWindowIcon("../../assets/images/bloopblip.jpeg");
}

void Window::setWindowIcon(const char* path) {
  GLFWimage images[1];
  images[0].pixels = stbi_load(path, &images[0].width, &images[0].height, 0,
                               4);  // rgba channels
  glfwSetWindowIcon(_window, 1, images);
  stbi_image_free(images[0].pixels);
}

/* position of the camera */
void Window::characterCallback(GLFWwindow* window, unsigned int codepoint) {
  if (codepoint == WINDOW_W) {
    cameraPos += cameraSpeed * cameraFront;
  } else if (codepoint == WINDOW_A) {
    cameraPos -=
        glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
  } else if (codepoint == WINDOW_D) {
    cameraPos +=
        glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
  } else if (codepoint == WINDOW_S) {
    cameraPos -= cameraSpeed * cameraFront;
  } else if (codepoint == WINDOW_Q) {
    cameraPos += cameraSpeed * glm::vec3(0.0f, 1.1f, 0.0f);
  } else if (codepoint == WINDOW_E) {
    cameraPos -= cameraSpeed * glm::vec3(0.0f, 1.1f, 0.0f);
  } else {
    // printf("%d\n", codepoint);
  }
  // printf("%f,%f,%f\n", cameraPos.x, cameraPos.y, cameraPos.z);
}

/* direction of the camera */
void Window::cursorPositionCallback(GLFWwindow* window,
                                    double xpos,
                                    double ypos) {
  if (firstMouse) {
    firstMouse = false;
    lastX = xpos;
    lastY = ypos;
  }
  float xoffset = xpos - lastX;
  float yoffset =
      lastY - ypos;  // reversed since y-coordinates range from bottom to top
  lastX = xpos;
  lastY = ypos;

  xoffset *= sensitivity;
  yoffset *= sensitivity;

  if (pitch + yoffset > 89.0f)
    pitch = 89.0f;
  else
    pitch += yoffset;
  if (yaw + xoffset < -89.0f)
    pitch = -89.0f;
  else
    yaw += xoffset;
  // printf("yaw: %f\npitch: %f\n", yaw, pitch);
}

void Window::cursorEnterCallback(GLFWwindow* window, int entered) {
  // if (entered) {
  //   printf("cursor inside window\n");
  // } else {
  //   printf("cursor outside window\n");
  // }
}

void Window::mouseButtonCallback(GLFWwindow* window,
                                 int button,
                                 int action,
                                 int mods) {
  double xpos, ypos;
  glfwGetCursorPos(window, &xpos, &ypos);
  if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
    printf("right click at (%lf, %lf)\n", xpos, ypos);
  } else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
    printf("left click at (%lf, %lf)\n", xpos, ypos);
  }
}

void Window::dropCallback(GLFWwindow* window, int count, const char** paths) {
  int i;
  for (i = 0; i < count; i++)
    printf("path %d: %s\n", i, paths[i]);
}

void Window::scrollCallback(GLFWwindow* window,
                            double xoffset,
                            double yoffset) {
  if (fov - yoffset < 1.0f)
    fov = 1.0f;
  else if (fov - yoffset > 45.0f)
    fov = 45.0f;
  else
    fov -= (float)yoffset;
}

extern GLint ambientStrengthLoc;
extern float ambientStrength;

void Window::keyCallback(GLFWwindow* window,
                         int key,
                         int scancode,
                         int action,
                         int mods) {
  if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
    printf("⬅\n");
  else if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
    printf("➡️\n");
  else if (key == GLFW_KEY_UP && action == GLFW_PRESS) {
    printf("up\n");
  } else if (key == GLFW_KEY_DOWN && action == GLFW_PRESS) {
    printf("down\n");
  }
}

// glfw: whenever the window size changed (by OS or user resize) this callback
// function executes
// ---------------------------------------------------------------------------------------------
void Window::framebufferSizeCallback(GLFWwindow* window,
                                     int width,
                                     int height) {
  // make sure the viewport matches the new window dimensions; note that width
  // and height will be significantly larger than specified on retina displays.
  glViewport(0, 0, width, height);
}

void Window::windowIconifyCallback(GLFWwindow* window, int iconified) {
  // if (iconified) {
  //   printf("window iconified\n");  // minimizado
  // } else {
  //   printf("window de-iconified\n");  // "maximizado"
  // }
}

void Window::setCallbacks() {
  glfwSetFramebufferSizeCallback(_window, framebufferSizeCallback);
  glfwSetKeyCallback(_window, keyCallback);
  glfwSetScrollCallback(_window, scrollCallback);
  glfwSetDropCallback(_window, dropCallback);
  glfwSetMouseButtonCallback(_window, mouseButtonCallback);
  glfwSetCursorEnterCallback(_window, cursorEnterCallback);
  glfwSetCursorPosCallback(_window, cursorPositionCallback);
  glfwSetCharCallback(_window, characterCallback);
  glfwSetWindowIconifyCallback(_window, windowIconifyCallback);
}

Window::~Window() noexcept {
  glfwTerminate();
}