#pragma once
#include <GL/glew.h>

class GLelementBuffer {
public:
    GLelementBuffer();
    ~GLelementBuffer();
    void bind() const;
    void index(int size, GLuint *indices, GLenum usage) const;
private:
    GLuint m_id;
};
