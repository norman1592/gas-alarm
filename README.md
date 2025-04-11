# Proyecto: Sistema de Monitoreo y Control con PIC16F676 (Gas-Alarm)

Este proyecto implementa un sistema embebido basado en el microcontrolador PIC16F676 para monitorear condiciones ambientales (posiblemente niveles de CO y punto de rocío) y controlar actuadores (válvulas) basado en lecturas de sensores y lógica temporizada.

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT) <!-- Ejemplo de Badge, ajusta o elimina si no aplica -->

## Descripción General

El sistema lee continuamente dos sensores analógicos y dos señales digitales. Utiliza los valores analógicos para establecer umbrales de tiempo dinámicos. Si una señal digital permanece activa durante el tiempo definido por su sensor analógico asociado, se activan las salidas de control principales. El sistema también proporciona señales de estado visual.

## Características

*   Monitoreo de 2 canales analógicos (0-5V, resolución 8 bits).
*   Monitoreo de 2 canales digitales.
*   Control de 4 salidas digitales (incluyendo indicadores y actuadores).
*   Lógica de temporización ajustable basada en sensores analógicos.
*   Indicador de sistema encendido.
*   Diseñado para el microcontrolador PIC16F676.
*   Código escrito en C para compilador CCS C (inferido por la sintaxis).

## Hardware

*   **Microcontrolador:** Microchip PIC16F676
*   **Oscilador:** Interno de 4MHz
*   **Entradas:**
    *   `RA0/AN0`: Sensor Analógico 1 (Ej. Sensor de CO)
    *   `RA1/AN1`: Sensor Analógico 2 (Ej. Sensor de Punto de Rocío)
    *   `RA4`: Señal Digital 1 (Ej. Estado/Alarma CO)
    *   `RA5`: Señal Digital 2 (Ej. Estado/Alarma Rocío)
    *   `RA3/MCLR`: Configurado como entrada digital (si no se usa para reset).
*   **Salidas:**
    *   `RC0`: Indicador/Actuador 1 (Relacionado con Rocío)
    *   `RC1`: Indicador de Sistema Encendido (AC Presente)
    *   `RC2`: Actuador 1 (Ej. Válvula Manifold)
    *   `RC3`: Indicador/Actuador 2 (Relacionado con CO)
    *   `RC4`: Actuador 2 (Ej. Válvula Principal)
*   **Alimentación:** VDD y VSS según datasheet del PIC16F676.

*(Nota: Se requiere un programador de PIC compatible, como PICKit 3/4, para cargar el firmware).*

## Software

*   **Lenguaje:** C
*   **Compilador:** CCS C (requiere las directivas `#include <16F676.h>`, `#use delay`, etc.)
*   **Archivo Fuente:** `Gases (1).c` (Se recomienda renombrar a algo más descriptivo, ej. `main.c` o `gas_alarm_firmware.c`)

## Configuración y Compilación

1.  **Instalar Compilador:** Asegúrate de tener instalado el compilador CCS C.
2.  **Crear Proyecto:** Crea un nuevo proyecto en el IDE de CCS C para el dispositivo PIC16F676.
3.  **Añadir Fuente:** Agrega el archivo `Gases (1).c` (o el nombre que le des) al proyecto.
4.  **Configurar Fuses:** Verifica que los fuses en el código (`#fuses INTRC_IO,NOWDT,PROTECT,NOMCLR`) sean los adecuados para tu hardware y aplicación.
5.  **Compilar:** Compila el proyecto para generar el archivo `.hex`.

## Programación del Dispositivo

Utiliza un programador de PIC (como PICKit 3, PICKit 4, ICD, etc.) y el software de programación asociado (como MPLAB IPE) para cargar el archivo `.hex` generado en el microcontrolador PIC16F676. Asegúrate de conectar correctamente los pines de programación (VDD, VSS, MCLR, PGD, PGC).

## Uso

1.  Conecta los sensores y actuadores a los pines correspondientes del PIC16F676 según la sección de Hardware.
2.  Alimenta el circuito.
3.  El LED/Indicador conectado a `RC1` debería encenderse, indicando que el sistema está operativo.
4.  El sistema comenzará a leer los sensores y a monitorear las entradas digitales.
5.  Las salidas `RC0` y `RC3` indicarán el estado (inverso) de las entradas digitales `RA5` y `RA4` respectivamente, o si el sistema está esperando a que se cumpla el tiempo.
6.  Las salidas `RC4` y `RC2` se activarán si la condición de entrada digital activa + tiempo cumplido (basado en el sensor analógico) se satisface para cualquiera de los dos canales (CO o Rocío).

## Contribución

Las contribuciones son bienvenidas. Si deseas mejorar este proyecto:

1.  Haz un Fork del repositorio.
2.  Crea una nueva rama (`git checkout -b mejora/nueva-caracteristica`).
3.  Realiza tus cambios y haz commit (`git commit -am 'Añade nueva característica'`). Asegúrate de comentar tu código.
4.  Haz Push a la rama (`git push origin mejora/nueva-caracteristica`).
5.  Abre un Pull Request.

Por favor, sigue las buenas prácticas de codificación y comenta tus cambios adecuadamente.

## Licencia

Este proyecto está bajo la Licencia MIT. Consulta el archivo `LICENSE` para más detalles (si aplica, crea un archivo LICENSE).

## Contacto

Norman - nramos72@gmail.com

Link del Proyecto: [https://github.com/norman1592/gas-alarm.git](https://github.com/norman1592/gas-alarm.git)
