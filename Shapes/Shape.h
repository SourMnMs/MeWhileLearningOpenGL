//
// Created by sourmnms on 2/7/26.
//

#ifndef SHAPE_H
#define SHAPE_H

#include "../bufferLog.h"
#include "../Shader.h"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>

class Shape
{
    std::vector<glm::vec3> vertices{};
    unsigned int numVertices = 0;

    std::vector<unsigned int> indices{};
    unsigned int numIndices = 0;

    glm::vec4 color = {0.0, 0.0, 0.0, 1.0f};
    std::string identifier;

    glm::vec3 translation = {0.0, 0.0, 0.0};
    float rotation = 0.0;

public:
    Shape(std::vector<glm::vec3>& verts, std::vector<unsigned int>& inds, glm::vec4 color, std::string id);

    GLsizeiptr memSize() const;

    void addToBuffer(bufferLog& VBO, bufferLog& EBO);
    void render(Shader& shader);
};


#endif //SHAPE_H