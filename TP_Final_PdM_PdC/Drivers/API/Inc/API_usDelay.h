/*
 * Simple microseconds delay routine, utilizing ARM's DWT
 * (Data Watchpoint and Trace Unit) and HAL library.
 *
 *
 * Based on Mastering "Mastering STM32 – Carmine Noviello"
 *
 *
 */



#ifndef INC_DWT_DELAY_H_
#define INC_DWT_DELAY_H_

#include <API_header.h>

#define DWT_DELAY_NEWBIE 0
/**
 * Initialization routine.
 *
 * @param  None
 * @retval None
 */
void delayUS_DWT_Init(void);
/**
 * Delay routine.
 * Time is in microseconds.
 *
 *
 * @param uint32_t us  Number of microseconds to delay for
 * @param
 * @retval None
 */
void delayUS_DWT(uint32_t us);

#endif /* INC_DWT_DELAY_DWT_DELAY_H_ */
