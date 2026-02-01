//
// Created by sourmnms on 1/27/26.
//

#ifndef FIRSTOPENGLPROJ_COLOR_H
#define FIRSTOPENGLPROJ_COLOR_H

#include <string>

class Color
{
    Color();
    Color(int r, int g, int b);
    Color(int r, int g, int b, int a);
    Color(float r, float g, float b);
    Color(float r, float g, float b, float a);

    // std::string toHex(int x);

public:
    int ir = 0;
    int ig = 0;
    int ib = 0;
    int ia = 255;

    float fr = 0.0f;
    float fg = 0.0f;
    float fb = 0.0f;
    float fa = 1.0f;

    // std::string hexStr();
    // std::string hexStr(bool capitalize);
};


#endif //FIRSTOPENGLPROJ_COLOR_H