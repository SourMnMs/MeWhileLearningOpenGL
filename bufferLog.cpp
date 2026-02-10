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

void bufferLog::bufferSubData(GLsizeiptr dataSize, void *data)
{
    memLocs.push_back(totalStoredSize);
    glBindBuffer(target, buffer);
    glBufferSubData(target, totalStoredSize, dataSize, data);
    totalStoredSize += dataSize;
}

GLsizeiptr bufferLog::memToAttrib(int idx)
{
    return memLocs[idx];
}

void bufferLog::deleteBuffer()
{
    glDeleteBuffers(1, &buffer);
    memLocs = {};
    totalStoredSize = 0;
}
