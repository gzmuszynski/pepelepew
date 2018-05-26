#include "postprocessor.h"

PostProcessor::PostProcessor()
{

}

void PostProcessor::process(Buffer &buffer)
{
    for(PostProcess* postProcess: postProcesses)
    {
        postProcess->operator ()(buffer);
    }
}

void PostProcess::operator()(Buffer &buffer)
{

}
