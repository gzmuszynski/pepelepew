#ifndef BARRELDISTORTIONTANPOSTPROCESS_H
#define BARRELDISTORTIONTANPOSTPROCESS_H

#include "postprocessor.h"



class BarrelDistortionTanPostProcess : public PostProcess
{
public:
    BarrelDistortionTanPostProcess();

    // PostProcess interface
public:
    void operator ()(Buffer &buffer);
};

#endif // BARRELDISTORTIONTANPOSTPROCESS_H
