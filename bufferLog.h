//
// Created by sourmnms on 2/8/26.
//

#ifndef BUFFERLOG_H
#define BUFFERLOG_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

/// Generic class for handling memory inside a buffer.
/// Doesn't store anything in a vector or do any fancy stuff,
/// it literally just keeps track of how much memory is already in the buffer.
class bufferLog
{
    GLsizeiptr storedSize = 0;
    GLsizeiptr maxSize = 0;
public:
    unsigned int buffer;
    GLenum target;

    bufferLog(GLenum target, GLsizeiptr size, GLenum usage);

    /// This does not resize or erase the data in the buffer.
    /// It only adds on to what is already there using glBufferSubData().
    void bufferSubData(GLsizeiptr dataSize, void* data);
};


#endif //BUFFERLOG_H