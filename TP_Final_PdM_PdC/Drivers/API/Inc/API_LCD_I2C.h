/*
 * API_LCD_I2C.h
 *
 *  Created on: 7 ago. 2023
 *      Author: CEO
 */

#ifndef API_INC_API_LCD_I2C_H_
#define API_INC_API_LCD_I2C_H_

#include "API_header.h"

/**
  * @brief Inicializacion de Puerto y de LCD
  * @param None
  * @retval None
  */
void lcd_i2c_init (void);
/**
  * @brief I2C1 Initialization Function of I2C port
  * @param None
  * @retval None
  */
void lcd_begin (void);
/**
  * @brief Funcion de envio de Comando al LCD
  * @param Char Commando value
  * @retval None
  */
void lcd_send_cmd (char cmd);
/**
  * @brief Funcion de Inicializacion LCD
  * @param None
  * @param None
  * @retval None
  */
void lcd_init (void);
/**
  * @brief Funcion de envio de Datos al LCD
  * @param Char Data
  * @retval None
  */
void lcd_send_data (char data);
/**
  * @brief Funcion de envio de Cadena de Caracteres al LCD
  * @param char *str
  * @retval None
  */
void lcd_send_string (char *str);
/**
  * @brief Funcion Limpieza de pantalla en LCD
  * @param None
  * @retval None
  */
void lcd_clear (void);
/**
  * @brief Funcion de posicionamiento de cursor en LCD
  * @param int Filas
  * @param int Columnas
  * @retval None
  */
void lcd_put_cur(int row, int col);



#endif /* API_INC_API_LCD_I2C_H_ */
