#pragma once
#include "core.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Input {
public:
    Input(GLcore &core);
    ~Input();
    void poll();
public:
    int vertical;
    int horizontal;
private:
    GLcore &m_core;
};
