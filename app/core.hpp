#pragma once
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class GLcore {
public:
    GLcore(std::string name, int w, int h);
    ~GLcore();
    int exists();
    void swap();
    GLFWwindow *m_win;
private:
    static void setViewport(GLFWwindow *window, int w, int h);
private:
    GLint m_w;
    GLint m_h;
    friend class Input;
};
