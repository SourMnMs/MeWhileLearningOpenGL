//
// Created by sourmnms on 2/8/26.
//

#include "bufferLog.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

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
    // memBlocks.push_back(totalStoredSize);
    // if (memBlocks.empty()) startNewBlock();
    startNewBlock();
    glBindBuffer(target, buffer);
    glBufferSubData(target, totalStoredSize, dataSize, data);
    totalStoredSize += dataSize;
}

void bufferLog::bind()
{
    glBindBuffer(target, buffer);
}
GLsizeiptr bufferLog::currentStoredSize()
{
    return totalStoredSize;
}

void bufferLog::startNewBlock()
{
    memBlocks.push_back(totalStoredSize);
}

GLsizeiptr bufferLog::memToBlock(int idx)
{
    if (memBlocks.empty()) return 0;
    return memBlocks[idx];
}
GLsizeiptr bufferLog::memToBlock()
{
    if (memBlocks.empty()) return 0;
    return memBlocks[memBlocks.size()-1];
}

void bufferLog::deleteBuffer()
{
    glDeleteBuffers(1, &buffer);
    memBlocks = {};
    totalStoredSize = 0;
}
