/*
 * Simple microseconds delay routine, utilizing ARM's DWT
 * (Data Watchpoint and Trace Unit) and HAL library.
 *
 *
 * Based on Mastering "Mastering STM32 – Carmine Noviello"
 *
 *
 */

#include "API_header.h"      // header para integrar librerias comunes
#include "API_usDelay.h"

/**
 * Rutina de Inicializacion
 *
 * @param  None
 * @retval None
 */
void delayUS_DWT_Init(void)  //fuente Matering STM - Carmine Noviello
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
 * Rutina de demora.
 * Tiempo en microsegundos.
 *
 *
 * @param uint32_t us  Numero de microsegundos para demora
 * @param
 * @retval None
 */
void delayUS_DWT(uint32_t us) // microsegundos
{
    uint32_t 		start = DWT->CYCCNT,
    					cycles = (SystemCoreClock/1000000) * us;

    while (DWT->CYCCNT - start < cycles);
}

