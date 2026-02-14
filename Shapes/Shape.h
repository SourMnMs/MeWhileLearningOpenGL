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
protected:
    constexpr static glm::vec4 DEFAULT_COLOR{1.0f};

    bool isInBuffer = false;

    std::vector<glm::vec3> vertices{};
    unsigned int numVertices = 0;

    std::vector<unsigned int> indices{};
    unsigned int numIndices = 0;
    GLsizeiptr indicesMemOffset;

    glm::vec4 color = DEFAULT_COLOR;
    std::string identifier;

    glm::vec2 translation = {0.0, 0.0};
    /// @brief Rotation of the shape in DEGREES
    float rotation = 0.0;
    glm::vec2 scaleFactor = {1.0f, 1.0f};

    /// @brief This constructor is protected because it's only meant
    /// to be used by subclasses
    Shape() = default;

public:
    Shape(
        std::vector<glm::vec2>& verts,
        std::vector<unsigned int>& inds,
        glm::vec4 color = DEFAULT_COLOR,
        std::string id = "");

    /// Returns the memory size of the vertex vector.
    /// Formally, vertices.size()*sizeof(glm::vec3).
    GLsizeiptr vertsMemSize() const;
    int numVerts();

    /// Adds the shape's vertices to the given VBO and the
    /// shape's indices to the given EBO.
    void addToBuffer(bufferLog& VBO, bufferLog& CBO, bufferLog& EBO);
    void addVertsToBuffer(bufferLog& VBO, bufferLog& CBO);
    void addIndsToBuffer(bufferLog& EBO, unsigned int offset);

    /// Positions itself according to translation and rotates
    /// according to rotation. Then it renders itself with the given shader.
    void render(Shader& shader);

    void setTranslations(glm::vec2 transl, float rot, glm::vec2 fscale);
    void translateAll(glm::vec2 transl, float rot, glm::vec2 fscale);
    /// @brief Takes in a 3-digit number in order: translation,
    /// rotation, scale. 2=On, 1=Off
    void translateDefault(int defs);

    void translate(glm::vec2 transl);
    void setTranslation(glm::vec2 transl);
    /// @brief
    void rotate(float deg);
    void setRotation(float deg);
    /// @brief Scales the shape MULTIPLICATIVELY
    void scale(glm::vec2 fscale);
    void setScale(glm::vec2 fscale);
};


#endif //SHAPE_H