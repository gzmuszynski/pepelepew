#include "buffer.h"

Buffer::Buffer()
{

}

Buffer::Buffer(int width, int height) : width(width), height(height)
{
    color    = new float4[width*height];
    depth    = new float4[width*height];
    normal   = new float4[width*height];
    position = new float4[width*height];

    final    = new float4[width*height];
}

void Buffer::clear()
{
    for(int y = 0; y < height; y++)
    {
        int offset = y*width;
        for(int x = 0; x < width; x++)
        {
            color   [offset+x] = float4(0.0f, 0.0f, 0.0f, 0.0f);
            depth   [offset+x] = float4(1.0f, 1.0f, 1.0f, 0.0f);
            normal  [offset+x] = float4(0.0f, 0.0f, 0.0f, 0.0f);
            position[offset+x] = float4(0.0f, 0.0f, 0.0f, 0.0f);

            final   [offset+x] = float4(0.0f, 0.0f, 0.0f, 0.0f);
        }
    }
}
