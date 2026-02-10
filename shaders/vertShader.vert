#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 shpColor;
//layout (location = 2) in vec2 aTexCoord;

//uniform mat4 transform;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec4 color;
//out vec2 TexCoord;
//out float dist;


void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    color = shpColor;
//    dist = sqrt(pos.x*pos.x + pos.y*pos.y + pos.z*pos.z);
    //ourColor = aPos + offset + vec3(1, 1, 0);
    //ourColor = aPos + offset;
//    ourColor = aColor;
//    TexCoord = aTexCoord;
}