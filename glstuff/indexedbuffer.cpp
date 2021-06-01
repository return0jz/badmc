#include "indexedbuffer.hpp"

GLindexedBuffer::GLindexedBuffer() {
    glGenBuffers(1, &b_id);
    glGenBuffers(1, &e_id);
}

GLindexedBuffer::~GLindexedBuffer() {
    glDeleteBuffers(1, &b_id);
    glDeleteBuffers(1, &e_id);
}

void GLindexedBuffer::bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, b_id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, e_id);
}

void GLindexedBuffer::data(int size, GLfloat *data, GLenum usage) const {
    glBufferData(GL_ARRAY_BUFFER, size, data, usage);
}

void GLindexedBuffer::attribute(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid *pointer) const {
    this->bind();
    glVertexAttribPointer(index, size, type, normalized, stride, pointer);
    glEnableVertexAttribArray(index);
}

void GLindexedBuffer::index(int size, GLuint *indices, GLenum usage) const {
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, usage);
}
