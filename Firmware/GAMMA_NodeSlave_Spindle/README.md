# Nodo Esclavo Spindle – Intercambiador Gamma

Este módulo forma parte del sistema de control distribuido para un **intercambiador Gamma**, desarrollado en el Laboratorio de Desarrollo Electrónico del **INSTITUTO PERUANO DE ENERGÍA NUCLEAR (IPEN)**. 

## Descripción General
El **Nodo Esclavo Spindle** controla el movimiento vertical de un husillo que posiciona recipientes tipo Marinelli en un sistema de mediciones radiológicas automatizadas. Opera mediante comandos seriales recibidos del **Nodo Maestro** o desde una PC, y realiza acciones sobre el motor paso a paso, el relé, y otros periféricos asociados.

## Características del Sistema
- Microcontrolador objetivo: **Arduino Mega 2560 (ATmega2560)**
- Control de motor paso a paso con dirección y pulso
- Lectura de sensores de posición y sensores de Marinelli
- Recepción de comandos seriales por `Serial` y `Serial1`
- Interfaz de usuario con **pantalla LCD** y **zumbador (buzzer)**
- Múltiples botones para control manual en modo seguro
- Lógica por bandera de ejecución (`RUNNING_MODE`) y validación

## Estructura del Código
El código está estructurado en:

- **setup()**: Inicialización de periféricos, LCD, sensores, botones.
- **loop()**:
  - Procesamiento de comandos seriales.
  - Lógica de control según modo de operación.
  - Movimientos seguros controlados por sensores.

## Comandos Seriales Implementados
| Comando | Descripción              | Fuente           |
|---------|---------------------------|------------------|
| `T`     | Detener                   | PC / Maestro     |
| `G1`    | Ir a Posición 1           | PC / Maestro     |
| `G2`    | Ir a Posición 2           | PC / Maestro     |
| `?`     | Identificación del nodo   | PC / Maestro     |

## Licencia
Este proyecto está licenciado bajo **Creative Commons Attribution-NonCommercial 4.0 International (CC BY-NC 4.0)**. 

- Libre uso y modificación con fines **no comerciales**, incluyendo atribución a los autores.
- Prohibida su distribución comercial sin autorización expresa.

## Autores
- O. Baltuano  
- R. Chan  
**Laboratorio de Desarrollo Electrónico – IPEN**

## Requisitos
- Arduino IDE o PlatformIO
- Placa Arduino Mega 2560
- Librería `LiquidCrystal`

---
Para más información sobre licencias y colaboraciones, contactar con el equipo del laboratorio a través de los canales institucionales del IPEN.
