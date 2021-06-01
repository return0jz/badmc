#pragma once
#include <GL/glew.h>

class GLindexedBuffer {
public:
    GLindexedBuffer();
    ~GLindexedBuffer();
    
    void bind() const;
    void data(int size, GLfloat *data, GLenum usage) const;
    void attribute(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid *pointer) const;
    void index(int size, GLuint *indices, GLenum usage) const;
private:
    GLuint b_id;
    GLuint e_id;
};
