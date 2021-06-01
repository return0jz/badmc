#include "vertexbuffer.hpp"
#include <iostream>

GLvertexBuffer::GLvertexBuffer() {
    glGenBuffers(1, &m_id);
}

GLvertexBuffer::~GLvertexBuffer() {
    glDeleteBuffers(1, &m_id);
}

void GLvertexBuffer::bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, m_id);
}

void GLvertexBuffer::data(int size, GLfloat *data, GLenum usage) const {
    glBufferData(GL_ARRAY_BUFFER, size, data, usage);
}

void GLvertexBuffer::attribute(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid *pointer) const {
    this->bind();
    glVertexAttribPointer(index, size, type, normalized, stride, pointer);
    glEnableVertexAttribArray(index);
}
