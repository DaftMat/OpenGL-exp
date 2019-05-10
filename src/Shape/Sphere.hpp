//
// Created by daftmat on 06/05/19.
//

#ifndef OPENGLTUTO_SPHERE_HPP
#define OPENGLTUTO_SPHERE_HPP

#include "Model.hpp"
#include "TerrainFace.hpp"

class Sphere {
    unsigned int resolution; //from 2 to 256
    Model model;
    std::vector<TerrainFace> terrainFaces;

public:
    explicit Sphere(unsigned int resolution = 2);
    void Draw(Shader shader);
};


#endif //OPENGLTUTO_SPHERE_HPP
