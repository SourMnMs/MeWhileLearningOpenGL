//
// Created by sourmnms on 2/7/26.
//

#include "Shape.h"

#include <glm/glm.hpp>
#include "glm/ext/matrix_transform.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>

Shape::Shape(
    std::vector<glm::vec3> &verts,
    std::vector<unsigned int> &inds,
    glm::vec4 color = {0.0, 0.0, 0.0, 1.0},
    std::string id = "")
{
    vertices = verts;
    numVertices = vertices.size();
    indices = inds;
    numIndices = indices.size();
    this->color = color;
    identifier = id;
}

void Shape::render(Shader& shader)
{
    // remember that there only needs to be one shader.use() call
    glm::mat4 modelMatrix = {1.0f};
    modelMatrix = glm::translate(modelMatrix, translation);
    // 2d shape so only rotations around Z-axis
    modelMatrix = glm::rotate(modelMatrix, rotation, glm::vec3(0.0, 0.0, 1.0));
    shader.setMat4("model", modelMatrix);
    glDrawArrays(GL_TRIANGLES, 0, numVertices);
}


void Shape::addToBuffer(bufferLog& VBO, bufferLog& EBO)
{
    glBindBuffer(VBO.target, VBO.buffer);
    VBO.bufferSubData(memSize(), &vertices[0]);

    glBindBuffer(EBO.target, EBO.buffer);
    EBO.bufferSubData(indices.size()*sizeof(unsigned int), &indices[0]);
}


GLsizeiptr Shape::memSize() const
{
    return numVertices * sizeof(glm::vec3);
}
