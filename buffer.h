#ifndef BUFFER_H
#define BUFFER_H

#include "float4.h"



class Buffer
{
public:
    Buffer(int width, int height);

    void clear();

    int width;
    int height;

    float4 *color;
    float4 *depth;
    float4 *normal;
    float4 *position;

    float4 *final;
};

#endif // BUFFER_H
