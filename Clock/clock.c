
#include "clock.h"

/**
 * @brief  Function called wto read the current millisecond
 * @param  None
 * @retval None
 */
uint32_t getCurrentMillis(void)
{
  return HAL_GetTick();
}

/**
 * @brief  Function called to read the current micro second
 * @param  None
 * @retval None
 */
uint32_t getCurrentMicros(void)
{
  uint32_t m0 = HAL_GetTick();
  __IO uint32_t u0 = SysTick->VAL;
  uint32_t m1 = HAL_GetTick();
  __IO uint32_t u1 = SysTick->VAL;
  const uint32_t tms = SysTick->LOAD + 1;

  if (m1 != m0)
  {
    return (m1 * 1000 + ((tms - u1) * 1000) / tms);
  }
  else
  {
    return (m0 * 1000 + ((tms - u0) * 1000) / tms);
  }
}

uint32_t millis(void)
{
  // ToDo: ensure no interrupts
  return getCurrentMillis();
}

// Interrupt-compatible version of micros
uint32_t micros(void)
{
  return getCurrentMicros();
}

void delay(uint32_t ms)
{
  if (ms != 0)
  {
    uint32_t start = getCurrentMillis();
    do
    {
      // yield();
    } while (getCurrentMillis() - start < ms);
  }
}
