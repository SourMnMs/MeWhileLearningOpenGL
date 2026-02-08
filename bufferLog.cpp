//
// Created by sourmnms on 2/8/26.
//

#include "bufferLog.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

bufferLog::bufferLog(GLenum target, GLsizeiptr size, GLenum usage)
{
    glGenBuffers(1, &buffer);
    glBindBuffer(target, buffer);
    glBufferData(target, size, nullptr, usage);

    maxSize = size;
    this->target = target;
}

void bufferLog::bufferSubData(GLsizeiptr dataSize, const void *data)
{
    glBindBuffer(target, buffer);
    glBufferSubData(target, storedSize, dataSize, data);
    storedSize += dataSize;
}