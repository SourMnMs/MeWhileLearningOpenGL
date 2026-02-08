//
// Created by sourmnms on 2/8/26.
//

#include "CoordinateSystem.h"

#include <glad/glad.h>
#include <glm/glm.hpp>

CoordinateSystem::CoordinateSystem(glm::vec2 min, glm::vec2 max)
{
    minimum = min;
    maximum = max;

    center = (minimum+maximum) / glm::vec2(2.0);
}


glm::vec2 CoordinateSystem::toScreenCoord(glm::vec2 p) const
{
    const glm::vec2 scale = (maximum-minimum) / glm::vec2(2.0);
    return scale * p + center;
}
std::vector<glm::vec2> CoordinateSystem::toScreenCoords(std::vector<glm::vec2>& v) const
{
    std::vector<glm::vec2> newV = {};
    const unsigned int n = v.size();
    for (int i = 0; i < n; i++)
        newV.push_back(toScreenCoord(v[i]));
    return newV;
}


glm::vec2 CoordinateSystem::toWindowCoord(glm::vec2 p) const
{
    const glm::vec2 scale = (maximum-minimum) / glm::vec2(2.0);
    return (p - center) / scale;
}
std::vector<glm::vec2> CoordinateSystem::toWindowCoords(std::vector<glm::vec2> &v)
{
    std::vector<glm::vec2> newV = {};
    const unsigned int n = v.size();
    for (int i = 0; i < n; i++)
        newV.push_back(toWindowCoord(v[i]));
    return newV;
}
