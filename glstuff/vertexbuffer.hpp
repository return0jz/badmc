#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class GLvertexBuffer {
public:
    GLvertexBuffer();
    ~GLvertexBuffer();
    void bind() const;
    void data(int size, GLfloat *data, GLenum usage) const;
    void attribute(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid *pointer) const;
private:
    GLuint m_id;
};
