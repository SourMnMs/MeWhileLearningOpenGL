//
// Created by sourmnms on 1/25/26.
//

#ifndef FIRSTOPENGLPROJ_SHADERS_OLD_H
#define FIRSTOPENGLPROJ_SHADERS_OLD_H

unsigned int makeShader(GLenum type, auto source);
unsigned int makeShaderProgram(const char* vertexSource, const char* fragmentSource);
bool checkShaderCompiled(unsigned int& shader);

namespace ms
{
    // Interesting thing here is that the compiler kinda just combines all of these string literals

    inline const char* vertexSource1 =
        "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "  gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\0";

    inline const char* fragmentSource1 =
        "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "   FragColor = vec4(1.0f, .5f, .2f, 1.0f);\n"
        "}\0";
    inline const char* fragmentSource2 =
        "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "   FragColor = vec4(0.75f, 0.0f, 0.75f, 1.0f);\n"
        "}\0";
}

#endif // FIRSTOPENGLPROJ_SHADERS_OLD_H