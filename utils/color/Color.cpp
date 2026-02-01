//
// Created by sourmnms on 1/27/26.
//

#include "Color.h"
#include <string>

Color::Color() = default;

Color::Color(float r, float g, float b)
{
    fr = r; fg = g; fb = b;
    ir = r*255; ig = g*255; ib = b*255;
}
Color::Color(float r, float g, float b, float a)
{
    fr = r; fg = g; fb = b; fa = a;
    ir = r*255; ig = g*255; ib = b*255; ia = a*255;
}

Color::Color(int r, int g, int b)
{
    ir = r; ig = g; ib = b;
    fr = r/255; fg = g/255; fb = b/255;
}
Color::Color(int r, int g, int b, int a)
{
    ir = r; ig = g; ib = b; ia = a;
    fr = r/255; fg = g/255; fb = b/255; fa = a/255;
}

// std::string Color::hexStr()
// {
//     std::string output = "";
//
// }
// std::string Color::hexStr(bool capitalize)
// {
//
// }
//
//
// std::string Color::toHex(int x)
// {
//     std::string output = "";
//     int tx = x / 16 + 1;
//     if (tx < 10) output += tx;
//     else output += ('F' - (16-tx));
//     tx = x % 16;
//     if (tx < 10) output += tx;
// }
