/*
 * API_ds18b20.h
 *
 *  Created on: Aug 10, 2023
 *      Author: CEO
 */

#ifndef API_INC_API_DS18B20_H_
#define API_INC_API_DS18B20_H_

#include <API_header.h>




/**
 * Funcion de Inicializacion de Comunicacion con Sensor DS18B20.
 *
 * @param  None
 * @retval  Low for the presence pulse is there.
 */
uint8_t ds18b20_init (void);


/**
 * Funcion de lectura de temperatura.
 *
 * @param  None
 * @retval float - Temperatura en centigrados
 */
float ds18b20_read_temp(void);




#endif /* API_INC_API_DS18B20_H_ */
