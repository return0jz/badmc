#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "core.hpp"
#define GLEW_STATIC

GLcore::GLcore(std::string name, int w, int h) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // macOS compatibility
    //glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    this->m_win = glfwCreateWindow(w, h, name.c_str(), NULL, NULL);
    if(!this->m_win) {
        std::cout << "Failed to initialize GLFW window." << std::endl;
        glfwTerminate();
    }
    else {
        glfwMakeContextCurrent(this->m_win);
        glfwSetFramebufferSizeCallback(this->m_win, GLcore::setViewport);
        glewExperimental = GL_TRUE;
        if (glewInit() != glewInit()) {
            std::cout << "Failed to initialize GLEW library." << std::endl;
        }
        else {
            GLcore::setViewport(this->m_win, w, h);
        }
    }
}

GLcore::~GLcore() {
    glfwTerminate();
}

int GLcore::exists() {
    return !glfwWindowShouldClose(this->m_win);
}

void GLcore::swap() {
    glfwSwapBuffers(this->m_win);
}

void GLcore::setViewport(GLFWwindow *win, int w, int h) {
    static int stw = w;
    static int sth = h;
    glfwGetFramebufferSize(win, &stw, &sth); // Retina display compatibility reasons
    glViewport(0, 0, w, h);
}
