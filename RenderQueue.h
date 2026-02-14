//
// Created by sourmnms on 2/13/26.
//

#ifndef RENDERQUEUE_H
#define RENDERQUEUE_H

#include "../bufferLog.h"
#include "../Shader.h"
#include "Shapes/Shape.h"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>

class RenderQueue
{
    std::vector<Shape*> objects{};
    unsigned int numObjs = 0;
    bufferLog& VBO;
    bufferLog& CBO;
    bufferLog& EBO;

    unsigned int indexMod = 0;

public:
    RenderQueue(bufferLog& VBO, bufferLog& CBO, bufferLog& EBO);

    void addObject(Shape* object);
    void bufferObjects();

    void renderObjects(Shader& shader);
};


#endif //RENDERQUEUE_H