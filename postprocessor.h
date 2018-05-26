#ifndef POSTPROCESSOR_H
#define POSTPROCESSOR_H

#include "buffer.h"

#include <QVector>

class PostProcess
{
public:
    virtual void operator()(Buffer &buffer);
};

class PostProcessor
{
public:
    PostProcessor();

    QVector<PostProcess*> postProcesses;

    void process(Buffer &buffer);
};

#endif // POSTPROCESSOR_H
