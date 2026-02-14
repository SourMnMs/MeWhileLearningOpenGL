//
// Created by sourmnms on 2/8/26.
//

#ifndef BUFFERLOG_H
#define BUFFERLOG_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>

/// Generic class for handling memory inside a buffer.
/// Doesn't store anything do any fancy stuff,
/// it literally just keeps track of how much memory is already in the buffer.
class bufferLog
{
    int numItemsStored = 0;
    GLsizeiptr totalStoredSize = 0;
    GLsizeiptr maxSize = 0;

    /// Holds locations of "blocks" of memory (typically per shape)
    std::vector<GLsizeiptr> memBlocks{};

public:
    unsigned int buffer;
    GLenum target;

    bufferLog(GLenum target, GLsizeiptr size, GLenum usage);

    /// This does not resize or erase the data in the buffer.
    /// It only adds on to what is already there using glBufferSubData().
    /// \n\n It is **VERY IMPORTANT** that if you are using a vector, data
    /// should be the output of the vector.data() method, NOT &vector[0].
    /// Otherwise, it will SEGFAULT.
    void bufferSubData(GLsizeiptr dataSize, void* data);

    void bind();
    GLsizeiptr currentStoredSize();

    void startNewBlock();
    /// Returns length of memory to a given memory block
    GLsizeiptr memToBlock(int idx);
    /// Returns length of memory to current memory block
    GLsizeiptr memToBlock();

    void deleteBuffer();
};


#endif //BUFFERLOG_H