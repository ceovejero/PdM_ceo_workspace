# Práctica 2

## Objetivo:
Implementar un módulo de software para trabajar con retardos no bloqueantes. 

## Punto 1
Implementar las funciones auxiliares necesarias para usar retardos no bloqueantes en un archivo fuente `main.c` con su correspondiente archivo de cabecera `main.h`.

En `main.h` se deben ubicar los prototipos de las siguientes funciones y las declaraciones

```
typedef uint32_t tick_t; // Qué biblioteca se debe incluir para que esto compile?
typedef bool bool_t;	  // Qué biblioteca se debe incluir para que esto compile?
typedef struct{
   tick_t startTime;
   tick_t duration;
   bool_t running;
} delay_t;
void delayInit( delay_t * delay, tick_t duration );
bool_t delayRead( delay_t * delay );
void delayWrite( delay_t * delay, tick_t duration );
```

En `main.c` se deben ubicar la implementación de todas las funciones:
Consideraciones para la implementación:
