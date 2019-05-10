//
// Created by mathis on 10/05/19.
//

#ifndef OPENGLTUTO_GIZMO_H
#define OPENGLTUTO_GIZMO_H

#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <vector>
#include "../Shaders/Shader.hpp"

class Gizmo {
    bool activated = true;
    glm::mat4 transform = glm::mat4(1.f);

    ///one for each direction
    unsigned int VAO, VBO, EBO;

public:

    Gizmo();
    ~Gizmo();

    void setTransform(const glm::mat4 &t) { transform=t; }
    const glm::mat4 & getTransform() { return transform; }

    void Draw(Shader &shader);

private:
    std::vector<float> vertices {
            0.01f, 0.f, 0.f,
            0.0075f, 0.f, 0.0075f,
            0.f, 0.f, 0.01f,
            -0.0075f, 0.f, 0.0075f,
            -0.01f, 0.f, 0.f,
            -0.0075f, 0.f, -0.0075f,
            0.f, 0.f, -0.01f,
            0.0075f, 0.f, -0.0075f,

            0.01f, 1.f, 0.f,
            0.0075f, 1.f, 0.0075f,
            0.f, 1.f, 0.01f,
            -0.0075f, 1.f, 0.0075f,
            -0.01f, 1.f, 0.f,
            -0.0075f, 1.f, -0.0075f,
            0.f, 1.f, -0.01f,
            0.0075f, 1.f, -0.0075f,

            0.02f, 1.f, 0.f,
            0.015f, 1.f, 0.015f,
            0.f, 1.f, 0.02f,
            -0.015f, 1.f, 0.015f,
            -0.02f, 1.f, 0.f,
            -0.015f, 1.f, -0.015f,
            0.f, 1.f, -0.02f,
            0.015f, 1.f, -0.015f,
            0.f, 1.05f, 0.f
    };

    std::vector<unsigned int> triangles {
            0, 8, 1,
            1, 8, 9,
            1, 9, 2,
            2, 9, 10,
            2, 10, 3,
            3, 10, 11,
            3, 11, 4,
            4, 11, 12,
            4, 12, 5,
            5, 12, 13,
            5, 13, 6,
            6, 13, 14,
            6, 14, 7,
            7, 14, 15,
            7, 15, 0,
            0, 15, 8,
            16, 24, 17,
            17, 24, 18,
            18, 24, 19,
            19, 24, 20,
            20, 24, 21,
            21, 24, 22,
            22, 24, 23,
            23, 24, 16
    };
};


#endif //OPENGLTUTO_GIZMO_H
