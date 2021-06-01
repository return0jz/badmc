#include "vertexarray.hpp"

GLvertexArray::GLvertexArray() {
    glGenVertexArrays(1, &m_id);
}

GLvertexArray::~GLvertexArray() {
    glDeleteVertexArrays(1, &m_id);
}

void GLvertexArray::bind() const {
    glBindVertexArray(m_id);
}
