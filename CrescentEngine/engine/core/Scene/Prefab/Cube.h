//
// Created by manan on 04/08/2021.
//

#ifndef CRESCENTENGINE_CUBE_H
#define CRESCENTENGINE_CUBE_H

#include <vector>
#include <glm/glm.hpp>



std::vector<glm::vec3> cubeVertices = {
        // VO
        glm::vec3(0.5, 0.5, -0.5),
        // V1
        glm::vec3(0.5, -0.5, -0.5),
        // V2
        glm::vec3(-0.5, -0.5, -0.5),
        // V3
        glm::vec3(-0.5, 0.5, -0.5),
        // V4
        glm::vec3(0.5, 0.5, 0.5),
        // V5
        glm::vec3(0.5, -0.5, 0.5),
        // V6
        glm::vec3(-0.5, -0.5, 0.5),
        // V7
        glm::vec3(-0.5, 0.5, 0.5),
};

std::vector<unsigned int> cubeIndices = {
        /*// Front
        0, 1, 3,      3, 1, 2,
        // Top
        4, 0, 3,      5, 4, 3,
        // Right
        3, 2, 7,      5, 3, 7,
        // Left
        6, 1, 0,      6, 0, 4,
        // Bottom
        2, 1, 6,      2, 6, 7,
        // Back
        7, 6, 4,      7, 4, 5,*/
        // front
        0, 1, 3,   1, 2, 3,
        0, 1, 4,   1, 4, 5,
        2, 3, 7,   2, 6, 7,
        4, 5, 7,   5, 6, 7,
        0, 3, 10,  3, 10, 8,
        1, 2, 9,   2, 9, 11,
};

std::vector<glm::vec2> cubeUVCoords = {
        glm::vec2(1.0f, 1.0f),
        glm::vec2(1.0f, 0.0f),
        glm::vec2(0.0f, 0.0f),
        glm::vec2(0.0f, 1.0f),
        glm::vec2(0.0f, 1.0f),
        glm::vec2(0.0f, 0.0f),
        glm::vec2(1.0f, 0.0f),
        glm::vec2(1.0f, 1.0f),

};

#endif //CRESCENTENGINE_CUBE_H
