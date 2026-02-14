//
// Created by sourmnms on 2/12/26.
//

#include "RegPolygon.h"
#include <glm/glm.hpp>
#include <vector>
#include <iostream>

RegPolygon::RegPolygon(int numVertices, float radius, glm::vec4 color, std::string id)
{
    this->color = color;
    identifier = id;

    for (int i = 0; i < numVertices; i++)
    {
        /// add 90 degrees to angle to make the first point at the top of the shape
        const float angle = glm::radians(360.0f/numVertices * i + 90);
        glm::vec3 newPoint = {radius*glm::cos(angle), radius*glm::sin(angle), 0.0f};
        vertices.push_back(newPoint);
        // std::cout << "added a vertice " << newPoint.x << " " << newPoint.y << std::endl;
    }
    this->numVertices = vertices.size();

    // std::cout << "vertices size: " << vertices.size() << std::endl;
    for (int i = 1; i <= numVertices-2; i++)
    {
        indices.push_back(0);
        indices.push_back((i)%numVertices);
        indices.push_back((i+1)%numVertices);
        // std::cout << "added " << 0 << " " << (i)%(numVertices) << " " << (i+1)%(numVertices) << std::endl;
    }
    numIndices = indices.size();
    std::cout << "created " << numIndices << " indices" << std::endl;
}
