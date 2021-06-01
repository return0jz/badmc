#include "input.hpp"

Input::Input(GLcore &core) : m_core(core) {}
void Input::poll() {
    this->vertical = 0;
    this->horizontal = 0;
    glfwPollEvents();
    if (glfwGetKey(this->m_core.m_win, GLFW_KEY_W)) {
        this->vertical = 1;
    }
    if (glfwGetKey(this->m_core.m_win, GLFW_KEY_A)) {
        this->horizontal = 1;
    }
    if (glfwGetKey(this->m_core.m_win, GLFW_KEY_S)) {
        this->vertical = 1;
    }
    if (glfwGetKey(this->m_core.m_win, GLFW_KEY_D)) {
        this->horizontal = 1;
    }
}
Input::~Input() {}
