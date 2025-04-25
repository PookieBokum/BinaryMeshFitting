#pragma once

#include <Windows.h>

// GLFW types
typedef struct GLFWwindow GLFWwindow;
typedef struct GLFWmonitor GLFWmonitor;
typedef struct GLFWcursor GLFWcursor;

// Callback types
typedef void (*GLFWerrorfun)(int, const char*);
typedef void (*GLFWwindowposfun)(GLFWwindow*, int, int);
typedef void (*GLFWwindowsizefun)(GLFWwindow*, int, int);
typedef void (*GLFWwindowclosefun)(GLFWwindow*);
typedef void (*GLFWwindowrefreshfun)(GLFWwindow*);
typedef void (*GLFWwindowfocusfun)(GLFWwindow*, int);
typedef void (*GLFWwindowiconifyfun)(GLFWwindow*, int);
typedef void (*GLFWframebuffersizefun)(GLFWwindow*, int, int);
typedef void (*GLFWmousebuttonfun)(GLFWwindow*, int, int, int);
typedef void (*GLFWcursorposfun)(GLFWwindow*, double, double);
typedef void (*GLFWcursorenterfun)(GLFWwindow*, int);
typedef void (*GLFWscrollfun)(GLFWwindow*, double, double);
typedef void (*GLFWkeyfun)(GLFWwindow*, int, int, int, int);
typedef void (*GLFWcharfun)(GLFWwindow*, unsigned int);

// GLFW constants
#define GLFW_FALSE 0
#define GLFW_TRUE 1
#define GLFW_RELEASE 0
#define GLFW_PRESS 1
#define GLFW_REPEAT 2
#define GLFW_KEY_ESCAPE 256
#define GLFW_KEY_W 87
#define GLFW_KEY_A 65
#define GLFW_KEY_S 83
#define GLFW_KEY_D 68
#define GLFW_KEY_SPACE 32
#define GLFW_KEY_LEFT_SHIFT 340
#define GLFW_MOUSE_BUTTON_LEFT 0
#define GLFW_MOUSE_BUTTON_RIGHT 1
#define GLFW_MOUSE_BUTTON_MIDDLE 2

// Function declarations
extern "C" {
    // Initialization and termination
    int glfwInit();
    void glfwTerminate();
    void glfwGetVersion(int* major, int* minor, int* rev);
    const char* glfwGetVersionString();
    
    // Error handling
    GLFWerrorfun glfwSetErrorCallback(GLFWerrorfun callback);
    
    // Window handling
    GLFWwindow* glfwCreateWindow(int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share);
    void glfwDestroyWindow(GLFWwindow* window);
    int glfwWindowShouldClose(GLFWwindow* window);
    void glfwSetWindowShouldClose(GLFWwindow* window, int value);
    void glfwSetWindowTitle(GLFWwindow* window, const char* title);
    void glfwGetWindowSize(GLFWwindow* window, int* width, int* height);
    void glfwSetWindowSize(GLFWwindow* window, int width, int height);
    void glfwGetFramebufferSize(GLFWwindow* window, int* width, int* height);
    void glfwGetWindowPos(GLFWwindow* window, int* xpos, int* ypos);
    void glfwSetWindowPos(GLFWwindow* window, int xpos, int ypos);
    void glfwIconifyWindow(GLFWwindow* window);
    void glfwRestoreWindow(GLFWwindow* window);
    void glfwShowWindow(GLFWwindow* window);
    void glfwHideWindow(GLFWwindow* window);
    void glfwFocusWindow(GLFWwindow* window);
    GLFWmonitor* glfwGetWindowMonitor(GLFWwindow* window);
    void glfwSetWindowMonitor(GLFWwindow* window, GLFWmonitor* monitor, int xpos, int ypos, int width, int height, int refreshRate);
    
    // Input handling
    void glfwPollEvents();
    void glfwWaitEvents();
    void glfwWaitEventsTimeout(double timeout);
    void glfwPostEmptyEvent();
    int glfwGetInputMode(GLFWwindow* window, int mode);
    void glfwSetInputMode(GLFWwindow* window, int mode, int value);
    int glfwGetKey(GLFWwindow* window, int key);
    int glfwGetMouseButton(GLFWwindow* window, int button);
    void glfwGetCursorPos(GLFWwindow* window, double* xpos, double* ypos);
    void glfwSetCursorPos(GLFWwindow* window, double xpos, double ypos);
    
    // Context handling
    void glfwMakeContextCurrent(GLFWwindow* window);
    GLFWwindow* glfwGetCurrentContext();
    void glfwSwapBuffers(GLFWwindow* window);
    void glfwSwapInterval(int interval);
    
    // Callback setters
    GLFWwindowposfun glfwSetWindowPosCallback(GLFWwindow* window, GLFWwindowposfun callback);
    GLFWwindowsizefun glfwSetWindowSizeCallback(GLFWwindow* window, GLFWwindowsizefun callback);
    GLFWwindowclosefun glfwSetWindowCloseCallback(GLFWwindow* window, GLFWwindowclosefun callback);
    GLFWwindowrefreshfun glfwSetWindowRefreshCallback(GLFWwindow* window, GLFWwindowrefreshfun callback);
    GLFWwindowfocusfun glfwSetWindowFocusCallback(GLFWwindow* window, GLFWwindowfocusfun callback);
    GLFWwindowiconifyfun glfwSetWindowIconifyCallback(GLFWwindow* window, GLFWwindowiconifyfun callback);
    GLFWframebuffersizefun glfwSetFramebufferSizeCallback(GLFWwindow* window, GLFWframebuffersizefun callback);
    GLFWmousebuttonfun glfwSetMouseButtonCallback(GLFWwindow* window, GLFWmousebuttonfun callback);
    GLFWcursorposfun glfwSetCursorPosCallback(GLFWwindow* window, GLFWcursorposfun callback);
    GLFWcursorenterfun glfwSetCursorEnterCallback(GLFWwindow* window, GLFWcursorenterfun callback);
    GLFWscrollfun glfwSetScrollCallback(GLFWwindow* window, GLFWscrollfun callback);
    GLFWkeyfun glfwSetKeyCallback(GLFWwindow* window, GLFWkeyfun callback);
    GLFWcharfun glfwSetCharCallback(GLFWwindow* window, GLFWcharfun callback);
} 