//
// Created by mathis on 10/05/19.
//

#include "Gizmo.h"


Gizmo::Gizmo() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, triangles.size() * sizeof(unsigned int), &triangles[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}

void Gizmo::Draw(Shader &shader) {
    if (!activated) return;

    //Y arrow
    glBindVertexArray(VAO);
    glm::mat4 utilTransform = transform;
    shader.setMat4f("model", utilTransform);
    shader.setVec3f("color", 0.f, 1.f, 0.f);
    glDrawElements(GL_TRIANGLES, triangles.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    //X arrow
    glBindVertexArray(VAO);
    utilTransform = glm::rotate(transform, glm::radians(-90.f), glm::vec3(0.f, 0.f, 1.f));
    shader.setMat4f("model", utilTransform);
    shader.setVec3f("color", 1.f, 0.f, 0.f);
    glDrawElements(GL_TRIANGLES, triangles.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    //Z arrow
    glBindVertexArray(VAO);
    utilTransform = glm::rotate(transform, glm::radians(90.f), glm::vec3(1.f, 0.f, 0.f));
    shader.setMat4f("model", utilTransform);
    shader.setVec3f("color", 0.f, 0.f, 1.f);
    glDrawElements(GL_TRIANGLES, triangles.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

Gizmo::~Gizmo() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}