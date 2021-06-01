#include <string>
#include <iostream>
#include "app/core.hpp"
#include "app/input.hpp"
#include "glstuff/shader.hpp"
#include "glstuff/vertexarray.hpp"
#include "glstuff/vertexbuffer.hpp"
#include "glstuff/indexedbuffer.hpp"
#include "glstuff/texture.hpp"
#include "libs/stb_image.h"
#include "libs/glm/glm.hpp"
#include "libs/glm/gtc/matrix_transform.hpp"
#include "libs/glm/gtc/type_ptr.hpp"

glm::vec3 cameraPos   = glm::vec3(0.0f, 3.0f, 0.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f, 0.0f);
bool firstMouse = true;
float yaw   = -90.0f;    // yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
float pitch =  0.0f;
float lastX =  1280.0f / 2.0;
float lastY =  720.0f / 2.0;
float fov   =  45.0f;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(front);
}

int main(int argc, const char * argv[]) {
    GLcore app = GLcore("Window", 1280, 720);
    Input inp = Input(app);
    glfwSetInputMode(app.m_win, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(app.m_win, mouse_callback);

    glEnable(GL_DEPTH_TEST);

    GLshaderPart vertexShader("/Users/jasperjzhou/Desktop/projs/archived/mcdemo/mcdemo/shaders/textureVertex.glsl", GL_VERTEX_SHADER);
    GLshaderPart fragmentShader("/Users/jasperjzhou/Desktop/projs/archived/mcdemo/mcdemo/shaders/textureFragment.glsl", GL_FRAGMENT_SHADER);
    GLshaderProgram shaderProgram(vertexShader, fragmentShader);
    shaderProgram.bind();

    GLfloat cubeVertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };
    glm::vec3 cubePositions[10000];
    for(int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            cubePositions[(i*10)+j] = glm::vec3(i*j,0.0f,j*i);
        }
    }

    GLtexture texture = GLtexture("/Users/jasperjzhou/Desktop/projs/archived/mcdemo/mcdemo/res/dirt.jpg");
    GLvertexArray triangleArray = GLvertexArray();
    GLvertexBuffer triangleBuffer = GLvertexBuffer();
    triangleArray.bind();

    triangleBuffer.bind();
    triangleBuffer.data(sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

    triangleBuffer.attribute(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    triangleBuffer.attribute(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    
    shaderProgram.bind();
    shaderProgram.setInt("texture1", 0);

    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    while (app.exists()) {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        
        inp.poll();
  
        glClearColor(0.9f, 0.9f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        shaderProgram.bind();
        texture.activate(GL_TEXTURE0);
        triangleArray.bind();
        if (glfwGetKey(app.m_win, GLFW_KEY_W) == GLFW_PRESS)
            cameraPos += (15*deltaTime) * cameraFront;
        if (glfwGetKey(app.m_win, GLFW_KEY_S) == GLFW_PRESS)
            cameraPos -= (15*deltaTime) * cameraFront;
        if (glfwGetKey(app.m_win, GLFW_KEY_A) == GLFW_PRESS)
            cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * (15*deltaTime);
        if (glfwGetKey(app.m_win, GLFW_KEY_D) == GLFW_PRESS)
            cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * (15*deltaTime);
        if (glfwGetKey(app.m_win, GLFW_KEY_Q) == GLFW_PRESS)
            break;

        glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float) 1280  / (float) 720, 0.1f, 100.0f);
        shaderProgram.setMat4("view", view);
        shaderProgram.setMat4("projection", projection);
        
        triangleArray.bind();
        for (unsigned int i = 0; i < 100; i++) {
            // calculate the model matrix for each object and pass it to shader before drawing
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            shaderProgram.setMat4("model", model);

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        
        app.swap();
    }
    return 0;
}
