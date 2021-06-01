#include "shader.hpp"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

GLshaderPart::GLshaderPart(std::string const& path, GLenum type) {
    // ---------- I/O stuff ---------- //
    const char* src;
    std::string srcstring;
    std::ifstream file;
    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        file.open(path);
        std::stringstream srcstream;
        srcstream << file.rdbuf();
        file.close();
        srcstring = srcstream.str();
    }
    catch(std::ifstream::failure e) {
        std::cout << "Error: Unable to read shader." << std::endl;
    }
    src = srcstring.c_str();
    // ---------- OpenGL stuff ---------- //
    GLint result;
    GLchar infoLog[512];
    this->m_id = glCreateShader(type);
    glShaderSource(this->m_id, 1, &src, NULL);
    glCompileShader(this->m_id);
    glGetShaderiv(this->m_id, GL_COMPILE_STATUS, &result);
    if(!result) {
        glGetShaderInfoLog(this->m_id, 512, NULL, infoLog);
        std::cout << "Error: Unable to compile shader ->\n" << infoLog << std::endl;
    }
}

GLshaderPart::~GLshaderPart() {
    glDeleteShader(this->m_id);
}

GLshaderProgram::GLshaderProgram(GLshaderPart &vertexShader, GLshaderPart &fragmentShader) {
    GLint result;
    GLchar infoLog[512];
    this->m_id = glCreateProgram();
    glAttachShader(this->m_id, vertexShader.m_id);
    glAttachShader(this->m_id, fragmentShader.m_id);
    glLinkProgram(this->m_id);
    glGetProgramiv(this->m_id, GL_LINK_STATUS, &result);
    if (!result) {
        glGetProgramInfoLog(this->m_id, 512, NULL, infoLog);
        std::cout << "Error: Unable to link shaders -> \n" << infoLog << std::endl;
    }
}

GLshaderProgram::~GLshaderProgram() {
    glDeleteProgram(this->m_id);
}

void GLshaderProgram::bind() const {
    glUseProgram(this->m_id);
}

void GLshaderProgram::setBool(const std::string &name, bool value) const
{
    glUniform1i(glGetUniformLocation(this->m_id, name.c_str()), (int)value);
}
// ------------------------------------------------------------------------
void GLshaderProgram::setInt(const std::string &name, int value) const
{
    glUniform1i(glGetUniformLocation(this->m_id, name.c_str()), value);
}
// ------------------------------------------------------------------------
void GLshaderProgram::setFloat(const std::string &name, float value) const
{
    glUniform1f(glGetUniformLocation(this->m_id, name.c_str()), value);
}
// ------------------------------------------------------------------------
void GLshaderProgram::setVec2(const std::string &name, const glm::vec2 &value) const
{
    glUniform2fv(glGetUniformLocation(this->m_id, name.c_str()), 1, &value[0]);
}
void GLshaderProgram::setVec2(const std::string &name, float x, float y) const
{
    glUniform2f(glGetUniformLocation(this->m_id, name.c_str()), x, y);
}
// ------------------------------------------------------------------------
void GLshaderProgram::setVec3(const std::string &name, const glm::vec3 &value) const
{
    glUniform3fv(glGetUniformLocation(this->m_id, name.c_str()), 1, &value[0]);
}
void GLshaderProgram::setVec3(const std::string &name, float x, float y, float z) const
{
    glUniform3f(glGetUniformLocation(this->m_id, name.c_str()), x, y, z);
}
// ------------------------------------------------------------------------
void GLshaderProgram::setVec4(const std::string &name, const glm::vec4 &value) const
{
    glUniform4fv(glGetUniformLocation(this->m_id, name.c_str()), 1, &value[0]);
}
void GLshaderProgram::setVec4(const std::string &name, float x, float y, float z, float w) const
{
    glUniform4f(glGetUniformLocation(this->m_id, name.c_str()), x, y, z, w);
}
// ------------------------------------------------------------------------
void GLshaderProgram::setMat2(const std::string &name, const glm::mat2 &mat) const
{
    glUniformMatrix2fv(glGetUniformLocation(this->m_id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
// ------------------------------------------------------------------------
void GLshaderProgram::setMat3(const std::string &name, const glm::mat3 &mat) const
{
    glUniformMatrix3fv(glGetUniformLocation(this->m_id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
// ------------------------------------------------------------------------
void GLshaderProgram::setMat4(const std::string &name, const glm::mat4 &mat) const
{
    glUniformMatrix4fv(glGetUniformLocation(this->m_id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
