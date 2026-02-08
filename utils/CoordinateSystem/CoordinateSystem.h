//
// Created by sourmnms on 2/8/26.
//

#ifndef COORDINATESYSTEM_H
#define COORDINATESYSTEM_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>

class CoordinateSystem
{
    glm::vec2 minimum = {-1.0, -1.0};
    glm::vec2 maximum = {1.0, 1.0};
    glm::vec2 center = {0.0, 0.0};

public:
    CoordinateSystem(glm::vec2 min, glm::vec2 max);

    // REMEMBER:
    // SCREEN COORDS ARE WITHIN [minimum, maximum]
    // WINDOW COORDS ARE WITHIN [-1.0, 1.0]

    glm::vec2 toScreenCoord(glm::vec2 p) const;
    std::vector<glm::vec2> toScreenCoords(std::vector<glm::vec2>& v) const;

    glm::vec2 toWindowCoord(glm::vec2 p) const;
    std::vector<glm::vec2> toWindowCoords(std::vector<glm::vec2>& v);
};


#endif //COORDINATESYSTEM_H