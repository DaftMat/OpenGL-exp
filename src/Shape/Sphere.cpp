//
// Created by daftmat on 06/05/19.
//

#include "Sphere.hpp"
Sphere::Sphere(unsigned int resolution) : resolution(resolution) {
    std::vector<glm::vec3> directions = {glm::vec3(0.f, 1.f, 0.f), glm::vec3(0.f, -1.f, 0.f),
                                         glm::vec3(1.f, 0.f, 0.f), glm::vec3(-1.f, 0.f, 0.f),
                                         glm::vec3(0.f, 0.f, 1.f), glm::vec3(0.f, 0.f, -1.f)};

    for (int i = 0 ; i < 6 ; ++i) {
        terrainFaces.emplace_back(TerrainFace(resolution, directions[i]));
        terrainFaces.back().constructMesh();
    }
}

void Sphere::Draw(Shader shader) const {
    for (const auto &terrain : terrainFaces)
        terrain.mesh.Draw(shader);
}