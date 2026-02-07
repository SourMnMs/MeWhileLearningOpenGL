#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
//layout (location = 1) in vec2 aTexCoord;

//uniform mat4 transform;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

//out vec3 ourColor;
//out vec2 TexCoord;
out float dist;


void main()
{
    vec4 pos = projection * view * model * vec4(aPos, 1.0);
    gl_Position = pos;
    dist = sqrt(pos.x*pos.x + pos.y*pos.y + pos.z*pos.z);
    //ourColor = aPos + offset + vec3(1, 1, 0);
    //ourColor = aPos + offset;
//    ourColor = aColor;
//    TexCoord = aTexCoord;
}