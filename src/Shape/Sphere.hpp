//
// Created by daftmat on 06/05/19.
//

#ifndef OPENGLTUTO_SPHERE_HPP
#define OPENGLTUTO_SPHERE_HPP

#include "Model.hpp"
#include "TerrainFace.hpp"

class Sphere {
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
    unsigned int resolution; //from 2 to 256
    std::vector<TerrainFace> terrainFaces;

public:
    explicit Sphere(unsigned int resolution = 2);
    void Draw(Shader shader) const;
};


#endif //OPENGLTUTO_SPHERE_HPP
