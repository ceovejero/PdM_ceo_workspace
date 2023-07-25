/*
 * API_debounce.c
 *
 *  Created on: 25 jul. 2023
 *      Author: CEO
 */

#include "API_header.h"
#include "API_delay.h"
#include "API_debounce.h"

#define DEBOUNCE_PERIOD 40

 typedef enum{
					BUTTON_UP,
					BUTTON_FALLING,
					BUTTON_DOWN,
					BUTTON_RAISING,
				} debounceState_t;

static delay_t delayDebounceFSM; //Estructura para control de tiempos
static debounceState_t estadoActual; // Variable de estado (global) interna de Maquina de Estados

/**
 * @brief  Inicializa la Maquina de Estado - debounce
 * @param  None
 * @retval None
 */
void debounceFSM_init()
{
		estadoActual = BUTTON_UP;
		BSP_PB_Init(BUTTON_USER, BUTTON_MODE_GPIO);
		delayInit(&delayDebounceFSM, DEBOUNCE_PERIOD);  //control de tiempos para debounce
}

/**
 * @brief  Implementacion de la maquia de estado.
 * @param  None
 * @retval None
 */
void debounceFSM_update()
{
	switch (estadoActual)
		{
			case BUTTON_UP:
					if (BSP_PB_GetState(BUTTON_USER))
						{
							estadoActual = BUTTON_FALLING; //estado siguiente
							delayRead(&delayDebounceFSM);  //inicia la cuenta de antirrebote
						}
			break;
			case BUTTON_FALLING:
					if (delayRead(&delayDebounceFSM))  // control de tiempo de antirrebote
					{// padado el tiempo de antirebote se controla el estado del pulsador
						if (BSP_PB_GetState(BUTTON_USER))
						{	// si sigue presionado se pasa al sigte estado
							estadoActual = BUTTON_DOWN;
							buttonPressed();	//accion para estado presionado
						}
						else // si se detecta estado inestable del pulsador
						{
							estadoActual = BUTTON_UP;   //regreso al estado previo
						}
					}
			break;
			case BUTTON_DOWN:
					if (!BSP_PB_GetState(BUTTON_USER))
						{	// si el pulsador se libera se regresa al estado anterior
							estadoActual = BUTTON_RAISING;
							delayRead(&delayDebounceFSM);
						}
			break;
			case BUTTON_RAISING:
					if (delayRead(&delayDebounceFSM))   // control de tiempo de antirrebote
					{	// padado el tiempo de antirebote se controla el estado del pulsador
						if(!BSP_PB_GetState(BUTTON_USER))
						{	//  si se libera se pasa al sigte estado
							estadoActual = BUTTON_UP;
							buttonReleased();   //accion para estado NO presionado
						}
						else   // si se detecta estado inestable del pulsador
						{
							estadoActual = BUTTON_DOWN;  //regreso al estado previo
						}
					}
			break;
			default:
					// si se carga algun valor no contemplado, se regresa al estado inicial
					estadoActual = BUTTON_UP;
			break;
		}
}

/**
* @brief  Accion para boton presionado - invierte el estado del LED1
* @param  None
* @retval None
*/
void buttonPressed()
{
	BSP_LED_Toggle(LED1);
}


 /**
 * @brief  Accion para boton liberado - invierte el estado del LED3
 * @param  None
 * @retval None
 */
void buttonReleased()
{
	BSP_LED_Toggle(LED3);
}


