#include <Arduino.h>

#ifndef __LOWPASS_FILTER_H__
#define __LOWPASS_FILTER_H__

typedef struct
{
  /* 滤波时间常数 */
  float Tf;

  /* Sample time (in seconds) */
  float dT;

  /* timestamp of last execution */
  unsigned long prevTimestamp;

  /* prevY of last execution */
  float prevY;

  /*output */
  float out;

} LowPassFilter;

#endif //__LOWPASS_FILTER_H__
