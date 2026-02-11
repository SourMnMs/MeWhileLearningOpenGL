//
// Created by sourmnms on 2/7/26.
//

#include "Shape.h"

#include <glm/glm.hpp>
#include "glm/ext/matrix_transform.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>

#include <vector>

Shape::Shape(
    std::vector<glm::vec2> &verts,
    std::vector<unsigned int> &inds,
    glm::vec4 color,
    std::string id)
{
    numVertices = verts.size();
    for (int i = 0; i < numVertices; i++)
        vertices.push_back(glm::vec3(verts[i], 0.0));
    indices = inds;
    numIndices = indices.size();
    this->color = color;
    identifier = id;
}


void Shape::addToBuffer(bufferLog& VBO, bufferLog& EBO)
{
    // add vertices to vbo
    glBindBuffer(VBO.target, VBO.buffer);
    VBO.bufferSubData(memSize(), vertices.data());

    // add colors to vbo
    // note: buffer will look like 111222333111122223333 because of this
    // but so long as we set offsets correctly the glVertexAttribPointer
    // thing will still work. test
    std::vector<glm::vec4> colorVec = {};
    for (int i = 0; i < numVertices; i++) colorVec.push_back(color);
    VBO.bufferSubData(numVertices*sizeof(glm::vec4), colorVec.data());

    // add indices to ebo
    glBindBuffer(EBO.target, EBO.buffer);
    EBO.bufferSubData(indices.size()*sizeof(unsigned int), indices.data());
}


void Shape::render(Shader& shader)
{
    // remember that there only needs to be one shader.use() call
    glm::mat4 modelMatrix = {1.0f};
    modelMatrix = glm::translate(modelMatrix, glm::vec3(translation, 0.0f));
    // 2d shape so only rotations around Z-axis
    modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation), glm::vec3(0.0, 0.0, 1.0));
    modelMatrix = glm::scale(modelMatrix, {scaleFactor, 1.0f});
    shader.setMat4("model", modelMatrix);
    // glDrawArrays(GL_TRIANGLES, 0, numVertices);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}


GLsizeiptr Shape::memSize() const
{
    return numVertices * sizeof(glm::vec3);
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