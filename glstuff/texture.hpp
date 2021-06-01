#pragma once
#include <string>
#include <iostream>
#include "../libs/stb_image.h"
#include "GL/glew.h"

class GLtexture {
public:
    GLtexture(std::string const& path);
    ~GLtexture();
    void bind() const;
    void activate(GLenum unit) const;
private:
    GLuint m_id;
    int m_image_w;
    int m_image_h;
    int m_image_cc; // number of color channels
    unsigned char *m_image_data;
};
