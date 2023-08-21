/*
 * API_LCD_I2C.h
 *
 *  Created on: 7 ago. 2023
 *      Author: Contrucción del código usando varias fuentes de internet
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


void lcd_write_row_col(char *str, int row, int col);


#endif /* API_INC_API_LCD_I2C_H_ */
