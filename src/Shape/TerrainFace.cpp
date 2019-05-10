//
// Created by daftmat on 06/05/19.
//

#include "Sphere.hpp"

Sphere::TerrainFace::TerrainFace(unsigned int resolution, glm::vec3 normal) : resolution(resolution), normal(normal) {
    axisA = glm::vec3(normal.y, normal.z, normal.x);
    axisB = glm::cross(normal, axisA);
}

void Sphere::TerrainFace::constructMesh() {
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    for (int y = 0 ; y < resolution ; ++y) {
        for (int x = 0 ; x < resolution ; ++x) {
            unsigned int i = x + y * resolution;
            glm::vec2 percent = glm::vec2(x, y) / (resolution - 1.f);
            glm::vec3 pointOnUnitCube = normal + (percent.x - .5f) * 2 * axisA + (percent.y - .5f) * 2 * axisB;
            glm::vec3 pointOnUnitSphere = glm::normalize(pointOnUnitCube);
            Vertex vertice;
            vertice.Position = pointOnUnitSphere;
            vertice.Normal = pointOnUnitSphere;
            vertice.TexCoords = percent;
            vertice.Tangent = glm::vec3(0, 0, 0);
            vertice.Bitangent = glm::vec3(0, 0, 0);
            vertices.emplace_back(vertice);

            if (x != resolution - 1 && y != resolution - 1) {
                indices.push_back(i);
                indices.push_back(i + resolution + 1);
                indices.push_back(i + resolution);

                indices.push_back(i);
                indices.push_back(i + 1);
                indices.push_back(i + resolution + 1);
            }
        }
    }

    mesh.vertices = vertices;
    mesh.indices = indices;
    mesh.setupMesh();
}

void Sphere::TerrainFace::addTexture(const std::string &path, TexType type) {
    Texture newTex;
    newTex.path = path;
    switch ( type ) {
        case DIFFUSE:
            newTex.type = "diffuse";
            break;
        case SPECULAR:
            newTex.type = "specular";
            break;
        case NORMAL:
            newTex.type = "normal";
            break;
        default:
            newTex.type = "none";
            break;
    }
    newTex.id = TextureFromFile(path);
}