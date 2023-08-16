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

/**
 * Rutina de Inicializacion
 *
 * @param  None
 * @retval None
 */
void delayUS_DWT_Init(void);
/**
 * Rutina de demora.
 * Tiempo en microsegundos.
 *
 *
 * @param uint32_t us  Numero de microsegundos para Demora
 * @param
 * @retval None
 */
void delayUS_DWT(uint32_t us);

#endif /* INC_DWT_DELAY_DWT_DELAY_H_ */
