/*
 * API_delay.c
 *
 *  Created on: Jul 10, 2023
 *      Author: ceo
 */
#include "stm32f4xx_hal.h"
#include "API_delay.h"

/* ========== Non-bloquing delay functions ========== */

void delayInit(delay_t *delay, tick_t duration)
{
	delay->duration = duration;
	delay->running = false;
}

bool_t delayRead(delay_t *delay)
{
	if (delay->running == false)
	{
		delay->running = true;
		delay->startTime = HAL_GetTick();
		return false;
	}
	else
	{
		if ((HAL_GetTick() - delay->startTime) < delay->duration)
		{
			return false;
		}
		else
		{
			delay->running = false;
			return true;
		}
	}
}

void delayWrite(delay_t *delay, tick_t duration)
{
	delay->duration = duration;
}


/* ============================================================ */