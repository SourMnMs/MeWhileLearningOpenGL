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
    Shape(
        std::vector<glm::vec2>& verts,
        std::vector<unsigned int>& inds,
        glm::vec4 color = {0.0f, 0.0f, 0.0f, 1.0f},
        std::string id = "");

    GLsizeiptr memSize() const;

    /// Adds the vertices to the given VBO and the indices
    /// to the given EBO.
    void addToBuffer(bufferLog& VBO, bufferLog& EBO);

    /// Positions itself according to translation and rotates
    /// according to rotation. Then it renders itself with the given shader.
    void render(Shader& shader);
};


#endif //SHAPE_H