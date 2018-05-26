#ifndef BARRELDISTORTIONPOSTPROCESS_H
#define BARRELDISTORTIONPOSTPROCESS_H

#include "postprocessor.h"



class BarrelDistortionPostProcess : public PostProcess
{
public:
    BarrelDistortionPostProcess();

    // PostProcess interface
public:
    void operator ()(Buffer &buffer);
};

#endif // BARRELDISTORTIONPOSTPROCESS_H
