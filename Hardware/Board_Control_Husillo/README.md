# Husillo Board – Intercambiador Gamma

Este documento describe la placa electrónica utilizada para el control del **módulo de husillo** en el sistema de automatización del intercambiador Gamma, desarrollado por el **Laboratorio de Desarrollo Electrónico – IPEN**.

## 📷 Diagrama de la Placa

![Diagrama de la Placa del Husillo](board_husillo.png)

## 🔧 Descripción Técnica

La placa está diseñada para:

- Controlar un **motor paso a paso** mediante señales `STEP` y `DIR`.
- Alimentar y conmutar un **relé de captura** para el sistema Marinelli.
- Leer múltiples **sensores de posición** (ópticos o magnéticos).
- Integrar un **buzzer** para notificación acústica.
- Interfaz directa con **Arduino Mega 2560** a través de conectores macho/hembra.
- Soporte de comunicación serial (TTL) para control distribuido.

## 🧩 Interfaces

| Señal          | Función                          |
|----------------|----------------------------------|
| `M_EN`         | Habilitación de motor            |
| `M_STEP`       | Pulso de avance                  |
| `M_DIR`        | Dirección de movimiento          |
| `RELAY`        | Activación del sistema Marinelli |
| `SENS_POS1-3`  | Sensores de posición del husillo |
| `SENS_MARx`    | Sensores de estado de Marinelli  |
| `BUZZER`       | Alarma sonora                    |
| `LCD`          | Salida para pantalla LCD 16x2    |

## 🛠️ Fabricación

- PCB de doble cara
- Conectores tipo Molex o bornes atornillables
- Compatible con montaje en riel DIN o chasis metálico

## 📄 Licencia

Este diseño se distribuye bajo **Creative Commons Atribución-NoComercial 4.0 Internacional (CC BY-NC 4.0)**. Su uso y modificación están permitidos únicamente para fines no comerciales, con la debida atribución a los autores.

## 👤 Autores

- O. Baltuano  
- R. Chan  
**Laboratorio de Desarrollo Electrónico – IPEN**
