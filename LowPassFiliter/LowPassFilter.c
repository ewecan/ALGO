#include "LowPassFilter.h"

void LowPassFilter_Init(LowPassFilter *lpf)
{
    /* Clear controller variables */
    lpf->prevTimestamp = 0;
    lpf->prevY = 0.0f;
    lpf->out = 0.0f;
}

float LowPassFilter_Update(LowPassFilter *lpf, float input)
{

    // unsigned long timestamp = micros();
    // lpf->dT = (timestamp - lpf->prevTimestamp) * 1e-6f;
    // lpf->prevTimestamp = timestamp;

    if (lpf->dT < 0.0f)
    {
        lpf->dT = 1e-3f;
    }
    else if (lpf->dT > 0.3f)
    {
        lpf->prevY = input;
        return input;
    }

    float alpha = lpf->Tf / (lpf->Tf + lpf->dT);
    lpf->out = alpha * lpf->prevY + (1.0f - alpha) * input;
    lpf->prevY = lpf->out;

    return lpf->out;
}
