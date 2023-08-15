# Trabajo Final

## Objetivo
El trabajo consiste en interconectar a la placa NÚCLEO de STM a un sensor de temperatura DS18B20 y un LCD con comunicación por I2C.
La aplicación prevé mostrar las mediciones de temperatura a través de la pantalla LCD y también transmitir los datos de las mediciones a través del puerto UART hacia una PC.

Cada vez que el usuario presiona un pulsador, el algoritmo alterna entre 2 estados:
•	uno que envía los datos de las mediciones de temperatura, a través de la UART, en una TERMINAL SERIE.
•	otro que envía los datos, por UART, para ser graficados en un “SERIAL PLOT”. 

## Periféricos utilizados:

GPIO, UART, I2C


### Diagrama de estado de MEF con una breve descripción de cada estado



## Descripción de los estados:

Inicialización.
En este estado, la aplicación inicializa todos los módulos que intervienen. GPIO para el sensor de temperatura y pulsador, UART para la comunicación con la PC, I2C para la comunicación con LCD. Se presenta vía LCD y Termial Serie en la PC un mensaje con la información de inicialización. Luego de 2 segundos se cambia de estado, hacia la Transmisión – Visualización de los datos de mediciones de temperatura.
Transmisión – Visualización.
En este estado se realiza las mediciones de temperatura para ser mostrados en LCD y en terminal serie a través de la UART (utilizando un formato amigable al usuario).
Al presionar un pulsador, la aplicación cambia al estado siguiente: Transmisión – Plot.
Transmisión – Plot.
En este estado se realiza las mediciones de temperatura para ser mostrados en LCD y en terminal serie a través de la UART, pero se utiliza un formato de datos más apropiado para ser graficados por un SERIAL PLOT.
Al presionar un pulsador, la aplicación cambia al estado siguiente: Transmisión – Visualización

## Definir los módulos de software (archivos) que va implementar para cada periférico.

Los módulos de software, archivos, correspondientes a cada periférico, se almacenarán en las carpetas Src en Inc, ubicados en la ruta perteneciente al proyecto en STM CUBE IDE: Drivers\API.
•	Módulo de Software para Sensor DS18B20: API_18b20.c y API_18b20.h
•	Módulo de Software para Pulsador GPIO: API_pb.c y API_pb.h Incluirá la implementación antirebote para mejorar la interacción con los pulsadores.
•	Módulo de Software para UART: API_uart.c y API_uart.h
•	Módulo de Software para LCD_I2C: API_lcd_i2c.c y API_lcd_i2c.h
•	Módulo de Software para Máquina de Estados: API_fsm.c y API_fsm.h

## Principales funciones públicas y privadas de cada módulo.

API_18b20
void init18b20(void) // Inicializa el GPIO y los parámetros de la comunicación con el dispositivo
uint8_t read18b20(void) // Realiza la captura de datos y los procesa para obtener una medición.

API_pb
void initPb(void) // Inicializa el GPIO y la máquina de estados para el anti rebote.
bool_t readKey(void); // devuelve true o false según se produjo la acción sobre el pulsador.

API_uart
bool_t uartInit(void)  //   Inicializa los parámetros del módulo UART de la placa NUCLEO.
void uartSendString(uint8_t * pstring)  //   envía una cadena de caracteres a través de UART.

API_lcd_i2c
void lcdInit(void)  //   Inicializa el módulo I2C de la placa NUCLEO para la comunicación con LCD
void lcdWriteString (char *str)  //  Escribe una cadena de caracteres en LCD a través de I2C.

API_fsm
void initFsm(void)  //   Inicializa la máquina de estados para la aplicación.
void updateFsm(void)  //   Actualiza la máquina de estados según los cambios de tiempo o acciones sobre el pulsador.
