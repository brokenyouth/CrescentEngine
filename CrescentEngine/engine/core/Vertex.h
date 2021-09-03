//
// Created by manan on 02/08/2021.
//

#ifndef CRESCENTENGINE_VERTEX_H
#define CRESCENTENGINE_VERTEX_H

#include <glm/glm.hpp>

struct Vertex
{
    glm::vec3               Position;
    glm::vec3               Normal;
    glm::vec3               Color;
    glm::vec2               TexUV;
};


#endif //CRESCENTENGINE_VERTEX_H
