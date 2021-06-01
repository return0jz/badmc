#pragma once
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../libs/glm/glm.hpp"

class GLshaderPart {
public:
    GLshaderPart(std::string const& path, GLenum type);
    ~GLshaderPart();
private:
    GLuint m_id;
    friend class GLshaderProgram;
};

class GLshaderProgram {
public:
    GLshaderProgram(GLshaderPart &vertexShader, GLshaderPart &fragmentShader);
    GLshaderProgram(GLshaderPart *vertexShader, GLshaderPart *fragmentShader);
    ~GLshaderProgram();
    void bind() const;
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
    void setVec2(const std::string &name, const glm::vec2 &value) const;
    void setVec2(const std::string &name, float x, float y) const;
    void setVec3(const std::string &name, const glm::vec3 &value) const;
    void setVec3(const std::string &name, float x, float y, float z) const;
    void setVec4(const std::string &name, const glm::vec4 &value) const;
    void setVec4(const std::string &name, float x, float y, float z, float w) const;
    void setMat2(const std::string &name, const glm::mat2 &mat) const;
    void setMat3(const std::string &name, const glm::mat3 &mat) const;
    void setMat4(const std::string &name, const glm::mat4 &mat) const;
private:
    GLuint m_id;
};
