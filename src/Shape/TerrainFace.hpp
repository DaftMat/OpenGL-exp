//
// Created by daftmat on 06/05/19.
//

#ifndef OPENGLTUTO_TERRAINFACE_HPP
#define OPENGLTUTO_TERRAINFACE_HPP


#include "Model.hpp"

class TerrainFace {
    unsigned int resolution; //number of triangles per face (from 2 to 256)
    glm::vec3 normal;
    glm::vec3 axisA;
    glm::vec3 axisB;

public:
    TerrainFace(unsigned int resolution, glm::vec3 normal);
    void constructMesh();
    void addTexture(const std::string &path, TexType type);

    Mesh mesh;
};


#endif //OPENGLTUTO_TERRAINFACE_HPP
