/*
 * Simple microseconds delay routine, utilizing ARM's DWT
 * (Data Watchpoint and Trace Unit) and HAL library.
 *
 *
 * Based on Mastering "Mastering STM32 – Carmine Noviello"
 *
 *
 */

#include "API_header.h"          // change to whatever MCU you use
#include "API_usDelay.h"

/**
 * Initialization routine.
 *
 * @param  None
 * @retval None
 */
void delayUS_DWT_Init(void)
{
    if (!(CoreDebug->DEMCR & CoreDebug_DEMCR_TRCENA_Msk))
    {
        // (DEMCR) Debug Exception and Monitor Control Register
    	// (TRCENA = tracing enable) This enables control of power usage unless tracing is required.
    	CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
        DWT->CYCCNT = 0;  // reset the counter
        DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk; // DWT_CTRL_CYCCNT ENA_Msk equals: enable the counter
    }
}


/**
 * Delay routine.
 * Time is in microseconds.
 *
 *
 * @param uint32_t us  Number of microseconds to delay for
 * @param
 * @retval None
 */
void delayUS_DWT(uint32_t us) // microseconds
{
    uint32_t startTick = DWT->CYCCNT,
             delayTicks = us * (SystemCoreClock/1000000);

    while (DWT->CYCCNT - startTick < delayTicks);
}

