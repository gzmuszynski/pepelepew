#ifndef DEFERREDSHADING_H
#define DEFERREDSHADING_H

#include "light.h"
#include "postprocessor.h"



class DeferredShading : public PostProcess
{
public:
    DeferredShading();

    QVector<Light> lights;

    // PostProcess interface
public:
    void operator ()(Buffer &buffer);
};

#endif // DEFERREDSHADING_H
