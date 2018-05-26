#ifndef CURVILINEARTRIANGLEFUNCTION_H
#define CURVILINEARTRIANGLEFUNCTION_H

#include "trianglefunction.h"



class CurvilinearTriangleFunction : public TriangleFunction
{
public:
    CurvilinearTriangleFunction();
    virtual Hit operator()(Vertex* &V, float x, float y);
};

#endif // CURVILINEARTRIANGLEFUNCTION_H
