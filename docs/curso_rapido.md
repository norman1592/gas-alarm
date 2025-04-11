# Curso Rápido: Sistema de Monitoreo y Control con PIC16F676

## Índice

1.  Introducción
2.  Motivación
3.  Objetivo del Proyecto
4.  Hardware Requerido (Inferido)
5.  Análisis del Código (`Gases (1).c`)
    *   Configuración Inicial (Fuses, Includes, I/O)
    *   Configuración de Periféricos (ADC, Puertos)
    *   Lógica Principal (Bucle `while(true)`)
    *   Lectura de Sensores Analógicos
    *   Procesamiento de Señales Digitales y Temporización
    *   Activación de Salidas (Válvulas)
6.  Diagrama de Flujo (Conceptual)
7.  Buenas Prácticas y Colaboración
8.  Posibles Mejoras
9.  Referencias (Platzhalter)

---

## 1. Introducción

Bienvenido a este curso rápido sobre un sistema embebido desarrollado para el microcontrolador PIC16F676. Este sistema está diseñado para monitorear condiciones ambientales (posiblemente niveles de gases como CO y punto de rocío) y activar actuadores (como válvulas) basándose en lecturas de sensores analógicos y señales digitales, incorporando una lógica de temporización.

---

## 2. Motivación

La necesidad de monitorear y controlar ambientes específicos es crucial en muchas aplicaciones industriales y de seguridad. Detectar condiciones anómalas, como la presencia de gases peligrosos o niveles de humedad críticos (punto de rocío), y actuar en consecuencia (por ejemplo, cerrando válvulas o activando alarmas) puede prevenir accidentes y asegurar la integridad de procesos. Este proyecto surge como una solución compacta y eficiente utilizando un microcontrolador de bajo costo.

---

## 3. Objetivo del Proyecto

El objetivo principal es implementar un firmware para el PIC16F676 que:

*   Lea continuamente dos sensores analógicos.
*   Monitoree dos señales de entrada digitales.
*   Implemente una lógica de temporización basada en las lecturas analógicas.
*   Active salidas digitales (posiblemente para controlar válvulas) cuando se cumplan ciertas condiciones de tiempo y estado de las entradas digitales.
*   Proporcione indicaciones visuales o de estado a través de otras salidas digitales.

---

## 4. Hardware Requerido (Inferido)

*   Microcontrolador PIC16F676.
*   Oscilador interno de 4MHz (configurado en el código).
*   Sensor analógico conectado a `RA0/AN0` (¿Sensor de CO?).
*   Sensor analógico conectado a `RA1/AN1` (¿Sensor de Punto de Rocío?).
*   Fuente de señal digital conectada a `RA4` (¿Señal de alarma/estado CO?).
*   Fuente de señal digital conectada a `RA5` (¿Señal de alarma/estado Rocío?).
*   Indicador/Actuador conectado a `RC0` (¿Indicador estado Rocío?).
*   Indicador conectado a `RC1` (¿Indicador de Sistema Encendido/AC?).
*   Actuador (Válvula Manifold?) conectado a `RC2`.
*   Indicador/Actuador conectado a `RC3` (¿Indicador estado CO?).
*   Actuador (Válvula Principal?) conectado a `RC4`.
*   Fuente de alimentación adecuada para el PIC y los periféricos.

---

## 5. Análisis del Código (`Gases (1).c`)

### Configuración Inicial

```c
#include <16F676.h>          // Librería específica para el PIC16F676
#device ADC=8               // Configura el ADC para 8 bits de resolución
#fuses INTRC_IO,NOWDT,PROTECT,NOMCLR // Configuración de fuses:
                            // INTRC_IO: Oscilador interno, pines RA4/RA5 como I/O
                            // NOWDT: Watchdog Timer desactivado
                            // PROTECT: Código protegido contra lectura
                            // NOMCLR: Pin MCLR como entrada digital (RA3)
#use delay(clock=4M)        // Define la velocidad del reloj para la función delay()
#use fast_io(a)             // Configura el puerto A para acceso rápido
#use fast_io(c)             // Configura el puerto C para acceso rápido

int cont_CO = 0, cont_ROCIO = 0, set_CO = 0, set_ROCIO = 0; // Variables globales
