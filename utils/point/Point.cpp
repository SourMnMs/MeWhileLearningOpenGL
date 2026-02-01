//
// Created by sourmnms on 1/27/26.
//

#include "Point.h"

Point::Point() = default;
Point::Point(float x, float y) : x(x), y(y) {}
Point::Point(float x, float y, float z) : x(x), y(y), z(z) {}

Point Point::op(char c, Point &p) const
{
    if (c == '-') return {x-p.x, y-p.y};
    if (c == 'x') return {x*p.x, y*p.y};
    if (c == '/') return {y/p.y, y/p.y};
    return {x+p.x, y+p.y};
}

Point Point::round(int places)
{
    float mult = 1.0f;
    for (int i = 0; i < places; i++) mult *= 10;
    float newX = ((int)(x*mult)) / mult;
    float newY = ((int)(y*mult)) / mult;
    return {newX, newY};
}
