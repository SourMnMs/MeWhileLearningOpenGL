//
// Created by sourmnms on 2/12/26.
//

#ifndef REGPOLY_H
#define REGPOLY_H

#include "Shape.h"

class RegPolygon : public Shape
{
public:
    RegPolygon(
        int numVertices,
        float radius = 1.0f,
        glm::vec4 color = DEFAULT_COLOR,
        std::string id = "");
};


#endif //REGPOLY_H