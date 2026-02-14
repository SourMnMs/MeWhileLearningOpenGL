//
// Created by sourmnms on 2/7/26.
//

#include "Shape.h"

#include <glm/glm.hpp>
#include "glm/ext/matrix_transform.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>

#include <vector>
#include <iostream>

Shape::Shape(
    std::vector<glm::vec2> &verts,
    std::vector<unsigned int> &inds,
    glm::vec4 color,
    std::string id)
{
    numVertices = verts.size();
    for (int i = 0; i < numVertices; i++)
        vertices.emplace_back(verts[i], 0.0);
    indices = inds;
    numIndices = indices.size();
    this->color = color;
    identifier = id;
}


void Shape::addVertsToBuffer(bufferLog &VBO, bufferLog &CBO)
{
    // VBO.startNewBlock();
    // add vertices to vbo
    glBindBuffer(VBO.target, VBO.buffer);
    VBO.bufferSubData(vertsMemSize(), vertices.data());


    // CBO.startNewBlock();
    glBindBuffer(CBO.target, CBO.buffer);
    // add colors to cbo
    std::vector<glm::vec4> colorVec = {};
    for (int i = 0; i < numVertices; i++) colorVec.push_back(color);
    CBO.bufferSubData(numVertices*sizeof(glm::vec4), colorVec.data());
}

void Shape::addIndsToBuffer(bufferLog &EBO, unsigned int offset)
{
    glBindBuffer(EBO.target, EBO.buffer);
    indicesMemOffset = EBO.currentStoredSize();

    std::cout << "offset: " << offset << std::endl;
    std::vector<unsigned int> modInds = {};
    for (int i = 0; i < numIndices; i++) modInds.push_back(indices[i]+offset);

    EBO.bufferSubData(numIndices*sizeof(unsigned int), modInds.data());
}


void Shape::render(Shader& shader)
{
    // remember that there only needs to be one shader.use() call
    glm::mat4 modelMatrix = {1.0f};
    modelMatrix = glm::translate(modelMatrix, glm::vec3(translation, 0.0f));
    // 2d shape so only rotations around Z-axis (0.0, 0.0, 1.0)
    modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
    modelMatrix = glm::scale(modelMatrix, {scaleFactor, 1.0f});
    shader.setMat4("model", modelMatrix);
    // glDrawArrays(GL_TRIANGLES, 0, numVertices);
    glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, (void*)indicesMemOffset);
}


GLsizeiptr Shape::vertsMemSize() const
{
    return numVertices * sizeof(glm::vec3);
}
int Shape::numVerts()
{
    return numVertices;
}

void Shape::setTranslations(glm::vec2 transl, float rot, glm::vec2 fscale)
{
    translation = transl;
    rotation = rot;
    scaleFactor = fscale;
}
void Shape::translateAll(glm::vec2 transl, float rot, glm::vec2 fscale)
{
    translation += transl;
    rotation += rot;
    scaleFactor *= fscale;
}
void Shape::translateDefault(int defs)
{
    if (defs % 10 == 2) scaleFactor = {1.0f, 1.0f};
    defs /= 10;
    if (defs % 10 == 2) rotation = 0.0f;
    defs /= 10;
    if (defs % 10 == 2) translation = {0.0f, 0.0f};
}


void Shape::translate(glm::vec2 transl) {translation += transl;}
void Shape::setTranslation(glm::vec2 transl) {translation = transl;}
void Shape::rotate(float deg) {rotation += deg;}
void Shape::setRotation(float deg) {rotation = deg;}
void Shape::scale(glm::vec2 fscale) {scaleFactor *= fscale;}
void Shape::setScale(glm::vec2 fscale) {scaleFactor = fscale;}