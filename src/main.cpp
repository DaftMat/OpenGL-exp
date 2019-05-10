#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shaders/Shader.hpp"
#include "Cameras/Camera.hpp"
#include "Shape/Model.hpp"
#include "Shape/Sphere.hpp"
#include "Shape/Gizmo.h"
#include <cmath>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

float screenWidth = 1920.f;
float screenHeight = 1080.f;

float deltaTime = 0.0f; //Time between current frame and last frame
float lastFrame = 0.0f; //Time of last frame;
float refreshTime = 0.0f;

bool firstMouse = true;

float lastX = screenWidth/2.f, lastY = screenHeight/2.f;

glm::mat4 model = glm::mat4(1.0f);

Camera camera;

/**
 * General input handler example
 * @param window - window that recieved input
 */
void processInput(GLFWwindow *window);

/**
 * Resize event handler
 * @param window - window to apply change
 * @param width - new width
 * @param height - new height
 */
void framebuffer_size_callback(GLFWwindow *window, int width, int height);

/**
 * Mouse moving event handler
 * @param window - window to apply change
 * @param xpos - x position of the mouse
 * @param ypos - y position of the mouse
 */
void mouse_callback(GLFWwindow* window, double xpos, double ypos);

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 32);

    //Window initialization
    GLFWwindow *window = glfwCreateWindow(unsigned(screenWidth), unsigned(screenHeight), "Learn OpenGL", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    //GLAD initialization
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "failed to initialize GLAD" << std::endl;
        return -1;
    }

    glViewport(0,0,(int)screenWidth,(int)screenHeight);

    //lock mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    //set mouse move event
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    //set viewport on resize event
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    //glEnable(GL_FRAMEBUFFER_SRGB);

    glEnable(GL_MULTISAMPLE);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_STENCIL_TEST);
    glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
    glStencilOp(GL_REPLACE, GL_KEEP, GL_KEEP);

    //glDisable(GL_DEPTH_TEST);
    //glDisable(GL_STENCIL_TEST);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    glFrontFace(GL_CW);

//    unsigned int fbo;
//    glGenFramebuffers(1, &fbo);
//    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
//
//    unsigned int frameBufferTexture = 0;
//    glGenTextures(1, &frameBufferTexture);
//    glBindTexture(GL_TEXTURE_2D, frameBufferTexture);
//    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, unsigned(screenWidth), unsigned(screenHeight), 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, frameBufferTexture, 0);
//
//    unsigned int rbo;
//    glGenRenderbuffers(1, &rbo);
//    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
//    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, unsigned(screenWidth), unsigned(screenHeight));
//    glBindRenderbuffer(GL_RENDERBUFFER, 0);
//
//    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);
//
//    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
//        std::cout << "ERROR:FRAMEBUFFER:: Framebuff is not completed" << std::endl;
//    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    Shader lightShader("../src/shaders/lighting.vertex", "../src/shaders/light.fragment");
    Shader lightingShader("../src/shaders/lighting.vertex", "../src/shaders/lighting.fragment");
    Shader borderShader("../src/shaders/lighting.vertex", "../src/shaders/border.fragment");
    Shader lineShader("../src/shaders/border.vertex", "../src/shaders/border.fragment");
    //Shader screenShader("../resources/shaders/screen.vertex", "../resources/shaders/screen.fragment");

    //Model myModel("../resources/img/nanosuit.obj");
    Sphere mySphere(4);
    Gizmo gizmo;

    lightingShader.use();
    model = glm::scale(model, glm::vec3(.2f, .2f, .2f));

    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    Vertex vertice;
    vertice.Position = glm::vec3(0.0f, 0.0f, 0.0f);
    vertice.TexCoords = glm::vec2(1.0f, 1.0f);
    vertice.Normal = glm::vec3(0.0f, 0.0f, 1.0f);
    vertice.Tangent = glm::vec3(1.0f, 0.0f, 0.0f);
    vertice.Bitangent = glm::vec3(0.0f, 1.0f, 0.0f);
    vertices.push_back(vertice);

    vertice.Position = glm::vec3(1.0f, 0.0f, 0.0f);
    vertice.TexCoords = glm::vec2(0.0f, 1.0f);
    vertices.push_back(vertice);

    vertice.Position = glm::vec3(0.0f, 1.0f, 0.0f);
    vertice.TexCoords = glm::vec2(1.0f, 0.0f);
    vertices.push_back(vertice);

    vertice.Position = glm::vec3(1.0f, 1.0f, 0.0f);
    vertice.TexCoords = glm::vec2(0.0f, 0.0f);
    vertices.push_back(vertice);

    indices.push_back(0);
    indices.push_back(1);
    indices.push_back(2);
    indices.push_back(2);
    indices.push_back(1);
    indices.push_back(3);

    Texture texture;
    texture.path = "../resources/img/grass.png";
    texture.type = "texture_diffuse";
    //texture.id = TextureFromFile(texture.path);
    textures.push_back(texture);

    //Mesh grass(vertices, indices, textures);

    float lineVertice[] = {
            //positions
            0.f, 0.f, 0.f,
            0.f, 3.f, 0.f
    };

    unsigned int lineVAO, lineVBO;
    glGenVertexArrays(1, &lineVAO);
    glGenBuffers(1, &lineVBO);
    glBindVertexArray(lineVAO);
    glBindBuffer(GL_ARRAY_BUFFER, lineVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(lineVertice), &lineVertice, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

//    float quadVertices[] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
//            // positions   // texCoords
//            -1.0f,  1.0f,  0.0f, 1.0f,
//            -1.0f, -1.0f,  0.0f, 0.0f,
//             1.0f, -1.0f,  1.0f, 0.0f,
//
//            -1.0f,  1.0f,  0.0f, 1.0f,
//             1.0f, -1.0f,  1.0f, 0.0f,
//             1.0f,  1.0f,  1.0f, 1.0f
//    };
//
//    unsigned int quadVAO, quadVBO;
//    glGenVertexArrays(1, &quadVAO);
//    glGenBuffers(1, &quadVBO);
//    glBindVertexArray(quadVAO);
//    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
//    glEnableVertexAttribArray(0);
//    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
//    glEnableVertexAttribArray(1);
//    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

    //rendering loop
    while(!glfwWindowShouldClose(window)) {
        //update deltaTime
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        if (refreshTime >= 1.f) {
            glfwSetWindowTitle(window, ("FPS : " + std::to_string(int(1.f / deltaTime))).c_str());
            refreshTime = 0.0f;
        }
        refreshTime += deltaTime;

        //input
        processInput(window);

        glm::mat4 projection = glm::perspective(glm::radians(camera.getFov()), screenWidth / screenHeight, 0.1f, 100.0f);
        //glBindFramebuffer(GL_FRAMEBUFFER, fbo);
        //rendering commands
        glClearColor(.2f, .2f, .2f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        //glEnable(GL_DEPTH_TEST);
        //glEnable(GL_STENCIL_TEST);

        ///Drawing object
        //render object
        glStencilFunc(GL_ALWAYS, 1, 0xFF);
        glStencilMask(0x00);
        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        lineShader.use();
        //model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f));
        lineShader.setMat4f("view", camera.getViewMatrix());
        lineShader.setMat4f("projection", projection);
//
//        glm::mat4 model2 = glm::scale(model, glm::vec3(1000.f, 1.f, 1000.f));
        gizmo.setTransform(model);
        gizmo.Draw(lineShader);
        //render object
        //model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f));
        //mySphere.Draw(lineShader);
        //glBindVertexArray(lineVAO);
        //glDrawArrays(GL_LINES, 0, 2);
        //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        glStencilFunc(GL_NOTEQUAL, 1, 0xFF); ///if it has to be bordered ///
        glStencilMask(0xFF);
        //Edit shader
        lightingShader.use();

        //add dir light
        lightingShader.setVec3f("pointLights[0].position", 0.0f, 1.f, 1.0f);
        lightingShader.setVec3f("pointLights[0].ambient", 0.2f, 0.2f, 0.2f);
        lightingShader.setVec3f("pointLights[0].diffuse", 1.0f, 1.0f, 1.0f);
        lightingShader.setVec3f("pointLights[0].specular", 1.f, 1.0f, 1.0f);
        lightingShader.setFloat("pointLights[0].constant", .2f);
        lightingShader.setFloat("pointLights[0].linear", .2f);
        lightingShader.setFloat("pointLights[0].quadratic", .2f);
        lightingShader.setVec3f("material.defaultDiffuse", 1.0f, 0.0f, 1.0f);
        lightingShader.setVec3f("material.defaultSpecular", 0.8f, 0.8f, 0.8f);
        lightingShader.setFloat("material.shininess", 1.f);
        lightingShader.setBool("material.diffTex", true);
        lightingShader.setBool("material.specTex", true);
        lightingShader.setBool("material.png", false);

        //view/projection transformations
        lightingShader.setVec3f("viewPos", camera.getPos());
        lightingShader.setMat4f("view", camera.getViewMatrix());
        lightingShader.setMat4f("projection", projection);

        //print soldier
        lightingShader.setMat4f("model", gizmo.getTransform());
        //myModel.Draw(lightingShader);

        //print grass
        lightingShader.setBool("material.specTex", false);
        lightingShader.setBool("material.png", true);
        lightingShader.setVec3f("material.defaultSpecular", 0.f, 0.f, 0.f);
        lightingShader.setFloat("material.shininess", 0.1f);
        //grass.Draw(lightingShader);

        //print sphere
        lightingShader.setBool("material.diffTex", false);
        lightingShader.setBool("material.png", false);
        lightingShader.setVec3f("material.defaultSpecular", 0.8f, 0.8f, 0.8f);
        lightingShader.setFloat("material.shininess", 0.5f);
        mySphere.Draw(lightingShader);

        glStencilMask(0xFF);

        //glBindFramebuffer(GL_FRAMEBUFFER, 0);
        //glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        //glClear(GL_COLOR_BUFFER_BIT);

        //Draw framebuffer -> the quad textured with the current scene
        //screenShader.use();
        //glBindVertexArray(quadVAO);
        //glDisable(GL_DEPTH_TEST);
        //glDisable(GL_STENCIL_TEST);
        //glBindTexture(GL_TEXTURE_2D, frameBufferTexture);
        //glDrawArrays(GL_TRIANGLES, 0, 6);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteShader(lightingShader.ID);
    glDeleteShader(lightShader.ID);
    glDeleteShader(borderShader.ID);
    //glDeleteFramebuffers(1, &fbo);
    //glDeleteRenderbuffers(1, &rbo);
    //glDeleteTextures(1, &frameBufferTexture);

    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    //camera control
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.processKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.processKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.processKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.processKeyboard(RIGHT, deltaTime);
    float velocity = 5.f;
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        model = glm::translate(model, velocity * glm::vec3(0.f, 0.f, -deltaTime));
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        model = glm::translate(model, velocity * glm::vec3(0.f, 0.f, deltaTime));
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        model = glm::translate(model, velocity * glm::vec3(deltaTime, 0.f, 0.f));
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        model = glm::translate(model, velocity * glm::vec3(-deltaTime, 0.f, 0.f));
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        model = glm::translate(model, velocity * glm::vec3(0.f, deltaTime, 0.f));
    if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
        model = glm::translate(model, velocity * glm::vec3(0.f, -deltaTime, 0.f));
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;

    lastX = xpos;
    lastY = ypos;

    camera.processMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset){
    camera.processMouseScroll(yoffset);
}