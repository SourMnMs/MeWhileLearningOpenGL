//
// Created by sourmnms on 1/27/26.
//

#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

#include <string>

class Shader
{
public:
    unsigned int programID;

    // reads and builds the shader
    Shader(const char* vertexPath, const char* fragmentPath);

    // use the shader
    void use();

    // utility uniform functions
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;

    // check compilation
    static unsigned int makeShader(GLenum type, auto source);
    static bool checkCompileErrors(unsigned int &shader);
};


#endif // SHADER_H