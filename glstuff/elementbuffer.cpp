#include "elementbuffer.hpp"

GLelementBuffer::GLelementBuffer() {
    glGenBuffers(1, &m_id);
}

GLelementBuffer::~GLelementBuffer() {
    glDeleteBuffers(1, &m_id);
}

void GLelementBuffer::bind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
}

void GLelementBuffer::index(int size, GLuint *indices, GLenum usage) const {
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, usage);
}
