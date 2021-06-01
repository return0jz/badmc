#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class GLvertexArray {
public:
    GLvertexArray();
    ~GLvertexArray();
    void bind() const;
private:
    GLuint m_id;
};
