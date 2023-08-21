/*
 * API_ds18b20.c
 *
 *  Created on: Aug 10, 2023
 *      Author: CEO
 */


#include "API_header.h"
#include "API_ds18b20.h"
#include "API_usDelay.h"
#include "API_delay.h"


#define LOW 0								// Estado Logico de GPIO_PIN para Comunicacion
#define COMM_PIN GPIO_PIN_13				// Seleccion de  GPIO_PIN para la comunicacion de acuerdo a la definicion en la HAL
#define COMM_PORT GPIOB						// seleccion de  PORT para la comunicacion de acuerdo a la definicion en la  HAL
#define MASTER_Tx_RESET_PULSE 480			// uSeg -
#define MASTER_WAIT_FOR_PRESENCE 80			// uSeg
#define MASTER_WAIT_FOR_END_PRESENCE_PULSE 400	// 400 uS
#define MASTER_Rx_TIME 480			// uSeconds

#define SKIP_ROM 0xCC // comando para establecer comunicacion sin distinguir cuantos sensores estan en el BUS
#define CONVERT_T 0x44 // Inicia una conversion
#define READ_SCRATCHPAD 0xBE // acceso de lectura a los datos de conversion

#define ERROR_RETURN 14 // en hexadecimal 0x0E
#define TRUE 1
#define FALSE 0

#define SENSOR_PERIOD 800

GPIO_InitTypeDef GPIO_InitStruct;

static delay_t sensorTimed;

static bool_t ds18b20_cmd_flag = FALSE;

static uint8_t  temp_l;
static uint8_t  temp_h;
static uint16_t temp;
static float temperature=0;





//================== Funciones Privadas ===========================

/**
 * Funcion de configuracion del GPIO - Input - para la comunicacion.
 *
 * @param  None
 * @retval None
 */
static void gpio_set_input (void);
/**
 * Funcion de configuracion del GPIO - Output - para la comunicacion.
 *
 * @param  None
 * @retval None
 */
static void gpio_set_output (void);

/**
 * Funcion de Escritura de comando para  Sensor DS18B20.
 *
 * @param  uint8_t COMMAND
 * @retval  None
 */
static void ds18b20_write_cmd (uint8_t data);
/**
 * Funcion de Lectura de Nibble data desde el  Sensor DS18B20.
 *
 * @param None
 * @retval  uint8_t Data from Sensor DS18B20 (Nibble)
 */
static uint8_t ds18b20_read (void);

//===============================================================




//================== Funciones Publicas ===========================
/**
 * Funcion de lectura de temperatura.
 *
 * @param  None
 * @retval float - Temperatura en centigrados
 */
float ds18b20_read_temp(void)
{
	uint8_t check = 2;
	check = ds18b20_init ();

	if(ds18b20_cmd_flag == FALSE)
	{
		delayInit(&sensorTimed, SENSOR_PERIOD);
		ds18b20_write_cmd (SKIP_ROM);  // skip ROM  - pagina 11 del DAtasheet
		ds18b20_write_cmd (CONVERT_T);  // convert t - Inicia conversion
		ds18b20_cmd_flag = TRUE;
	}
	else if(delayRead(&sensorTimed))   // Delay (800us);
			{
				ds18b20_init ();
				ds18b20_write_cmd (SKIP_ROM);  // skip ROM // transmite que el siguiente comando sera para todos los presentes en el bus
				ds18b20_write_cmd (READ_SCRATCHPAD);  // Read Scratchpad - Acceso de lectura a los datos de conversion

				temp_l = ds18b20_read();
				temp_h = ds18b20_read();
				temp = (temp_h<<8)|temp_l;
				temperature = (float)temp/16;

				ds18b20_cmd_flag = FALSE;
			}

	if(check == FALSE)
		{
			return (ERROR_RETURN);
		}
		else
		{
			return (temperature);
		}
}


/**
 * Funcion de Inicializacion de Comunicacion con Sensor DS18B20.
 *
 * @param  None
 * @retval  Low for the presence pulse is there.
 */
uint8_t ds18b20_init (void)
{

	gpio_set_output ();   // set the pin as output
	HAL_GPIO_WritePin (COMM_PORT, COMM_PIN, LOW);  // Lleva estado logico del pin a LOW
	delayUS_DWT (MASTER_Tx_RESET_PULSE);   // 480 uS Se envia pulso LOW con el tiempo apropiado para inicializar comunicacion

	gpio_set_input ();    // set the pin as input
	delayUS_DWT (MASTER_WAIT_FOR_PRESENCE);    // 80 uS esperando pulso de PRESENCE, segun  datasheet

	if (!(HAL_GPIO_ReadPin (COMM_PORT, COMM_PIN)))    // Si el estado esta en LOW, significa que PRESENCE es detectado
	{
		delayUS_DWT (MASTER_WAIT_FOR_END_PRESENCE_PULSE);  // espera de 400 us, segun datasheet
		return TRUE; //dato logico como retorno de Comunicaciones establecida
	}

	else
	{
		delayUS_DWT (MASTER_WAIT_FOR_END_PRESENCE_PULSE);
		return FALSE;  // Comunicacion NO establecida
	}
}

//===============================================================


//================== Desarrollo de Funciones Privadas ===========================

/**
 * Funcion de configuracion del GPIO - Input - para la comunicacion.
 *
 * @param  None
 * @retval None
 */
static void gpio_set_input (void)
{
  GPIO_InitStruct.Pin = COMM_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(COMM_PORT, &GPIO_InitStruct);
}

/**
 * Funcion de configuracion del GPIO - Output - para la comunicacion.
 *
 * @param  None
 * @retval None
 */
static void gpio_set_output (void)
{
  GPIO_InitStruct.Pin = COMM_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(COMM_PORT, &GPIO_InitStruct);
}


/**
 * Funcion de Escritura de comando para  Sensor DS18B20.
 *
 * @param  uint8_t COMMAND
 * @retval  None
 */
static void ds18b20_write_cmd (uint8_t data)
{
	gpio_set_output ();   // set as output

	for (int i=0; i<8; i++)
	{

		if ((data & (1<<i))!=0)  // if the bit is high
		{
			// write 1

			gpio_set_output ();  // set as output
			HAL_GPIO_WritePin (COMM_PORT, COMM_PIN, LOW);  // pull the pin LOW
			delayUS_DWT (1);  // wait for  us

			gpio_set_input ();  // set as input
			delayUS_DWT (60);  // wait for 60 us
		}

		else  // if the bit is low
		{
			// write 0

			gpio_set_output ();
			HAL_GPIO_WritePin (COMM_PORT, COMM_PIN, LOW);  // pull the pin LOW
			delayUS_DWT (60);  // wait for 60 us

			gpio_set_input ();
		}
	}
}


/**
 * Funcion de Lectura de Nibble data desde el  Sensor DS18B20.
 *
 * @param None
 * @retval  uint8_t Data from Sensor DS18B20 (Nibble)
 */
static uint8_t ds18b20_read (void)
{
	uint8_t value=0;
	gpio_set_input ();

	for (int i=0;i<8;i++)
	{
		gpio_set_output ();   // set as output

		HAL_GPIO_WritePin (COMM_PORT, COMM_PIN, LOW);  // pull the data pin LOW
		delayUS_DWT (2);  // wait for 2 us

		gpio_set_input ();  // set as input
		if (HAL_GPIO_ReadPin (COMM_PORT, COMM_PIN))  // if the pin is HIGH
		{
			value |= 1<<i;  // read = 1
		}
		delayUS_DWT (60);  // wait for 60 us
	}
	return value;
}



