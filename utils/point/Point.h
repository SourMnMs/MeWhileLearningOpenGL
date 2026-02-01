//
// Created by sourmnms on 1/27/26.
//

#ifndef FIRSTOPENGLPROJ_POINT_H
#define FIRSTOPENGLPROJ_POINT_H


struct Point
{
    Point();
    Point(float x, float y);
    Point(float x, float y, float z);
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;

    Point op(char c, Point& p) const;

    Point round(int places);
};


#endif //FIRSTOPENGLPROJ_POINT_H