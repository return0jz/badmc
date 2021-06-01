#include "texture.hpp"

GLtexture::GLtexture(std::string const& path) { // Implemented only for 3 channels (no transparency)
    stbi_set_flip_vertically_on_load(true);

    m_image_data = stbi_load(path.c_str(), &m_image_w, &m_image_h, &m_image_cc, 0);
    if (m_image_data) {
        glGenTextures(1, &this->m_id);
        this->bind();
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_image_w, m_image_h, 0, GL_RGB, GL_UNSIGNED_BYTE, m_image_data);
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(m_image_data);
    }
    else {
        std::cout << "Error: Unable to load texture. " << std::endl;
    }
}

GLtexture::~GLtexture() {
    glDeleteTextures(1, &this->m_id);
}

void GLtexture::bind() const {
    glBindTexture(GL_TEXTURE_2D, this->m_id);
}

void GLtexture::activate(GLenum unit) const {
    glActiveTexture(unit); // e.g GL_TEXTURE0
    this->bind();
}
