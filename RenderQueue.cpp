//
// Created by sourmnms on 2/13/26.
//

#include "RenderQueue.h"

RenderQueue::RenderQueue(bufferLog &VBO, bufferLog& CBO, bufferLog &EBO) : VBO(VBO), CBO(CBO), EBO(EBO) {}

void RenderQueue::addObject(Shape *object)
{
    objects.push_back(object);
    numObjs++;
}

void RenderQueue::bufferObjects()
{
    for (int objI = 0; objI < numObjs; objI++)
    {
        // if (objects[objI].isInBuffer()) continue;
        objects[objI]->addVertsToBuffer(VBO, CBO);
        objects[objI]->addIndsToBuffer(EBO, indexMod);

        indexMod += objects[objI]->numVerts();
    }
}

void RenderQueue::renderObjects(Shader& shader)
{
    for (int objI = 0; objI < numObjs; objI++)
    {
        shader.use();

        objects[objI]->render(shader);
    }
}
