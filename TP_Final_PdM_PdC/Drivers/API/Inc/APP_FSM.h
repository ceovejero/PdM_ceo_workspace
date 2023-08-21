/*
 * API_FSM.h
 *
 *  Created on: Aug 11, 2023
 *      Author: CEO
 */

#ifndef API_INC_APP_FSM_H_
#define API_INC_APP_FSM_H_

#include "API_header.h"

/**
  * @brief Inicializacion de la APPlicacion y todos sus componentes
  * @param None
  * @retval None
  */
void APP_FSM_init(void);		// debe cargar el estado inicial
/**
  * @brief Lee las entradas y Actualiza el estado segun la logica
  * @param None
  * @retval None
  */
void APP_FSM_update(void);		// debe leer las entradas, resolver la logica de
													// transicion de estados y actualizar las salidas

/**
  * @brief Actualiza el parpadeo de LEDs para testigo visual
  * @param None
  * @retval None
  */
void APP_FSM_LED(uint16_t period1, uint16_t period2);

#endif /* API_INC_APP_FSM_H_ */
