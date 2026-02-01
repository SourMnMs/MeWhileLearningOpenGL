#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

uniform vec3 offset = vec3(0.0f, 0.0f, 0.0f);

out vec3 ourColor;
out vec2 TexCoord;
out vec3 ourOffset;

void main()
{
    gl_Position = vec4(aPos + offset, 1.0);
    //ourColor = aPos + offset + vec3(1, 1, 0);
    //ourColor = aPos + offset;
    ourColor = aColor;
    TexCoord = aTexCoord;
    ourOffset = offset;
}