/*
 * API_uart.c
 *
 *  Created on: 28 jul. 2023
 *      Author: CEO
 */

#include "API_header.h"
#include "API_uart.h"

#define UART_INIT_OK "\r\nInicializacion correcta\r\n"
#define UART_INIT_FAIL "Fallo de inicializacion\r\n"
#define INIT_MSG "Comunic UART 9600, 8N1\r\n HWC_OFF, Tx-Rx, OS_16\r\n"

// from Carmine Noviello - pag 185
UART_HandleTypeDef uartHandle;
static uint32_t uartDelay = HAL_MAX_DELAY;
//static char pstring[100]={0};

const bool_t uartInit()
{
	uartHandle.Instance = USART3;
	uartHandle.Init.BaudRate = 9600;
	uartHandle.Init.WordLength = UART_WORDLENGTH_8B;
	uartHandle.Init.StopBits = UART_STOPBITS_1;
	uartHandle.Init.Parity = UART_PARITY_NONE;
	uartHandle.Init.Mode = UART_MODE_TX_RX;
	uartHandle.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	uartHandle.Init.OverSampling = UART_OVERSAMPLING_16;

	if (HAL_UART_Init(&uartHandle) != HAL_OK)
		{
			uartSendString((uint8_t *) UART_INIT_FAIL);
			return false;
		}
	else
		{
			uartSendString((uint8_t *) UART_INIT_OK);
			uartSendString((uint8_t *) INIT_MSG);
			return true;
		}

	//return true;
}


void uartSendString(uint8_t * pstring)
{
	uint16_t len = (uint16_t) strlen((const char *)pstring);
	HAL_UART_Transmit(&uartHandle, pstring, len, uartDelay);
}

void uartSendStringSize(uint8_t * pstring, uint16_t size)
{
	HAL_UART_Transmit(&uartHandle, pstring, size, uartDelay);
}

void uartReceiveStringSize(uint8_t * pstring, uint16_t size)
{
	HAL_UART_Receive(&uartHandle, pstring, size, uartDelay);
}
