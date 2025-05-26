# Pinout General – Intercambiador GAMMA

Este documento resume la asignación de pines para los tres nodos principales del sistema: Nodo Maestro, Nodo Wheel y Nodo Gripper.

---

## Nodo Maestro

| Pin físico | Nombre en código             | Sensor/Actuador conectado           | Descripción breve                        |
|------------|-----------------------------|-------------------------------------|------------------------------------------|
| 30         | PIN_BTN_SAMPLE_NEXT         | Botón avanzar muestra (Wheel)       | Avanza a la siguiente muestra            |
| 31         | PIN_BTN_SAMPLE_PREV         | Botón retroceder muestra (Wheel)    | Retrocede a la muestra anterior          |
| 32         | PIN_BTN_PLATE_DOWN          | Botón bajar mesa (Wheel)            | Baja la mesa niveladora                  |
| 33         | PIN_BTN_PLATE_UP            | Botón subir mesa (Wheel)            | Sube la mesa niveladora                  |
| 34         | PIN_BTN_SHIELD_OPEN         | Botón abrir blindaje (Wheel)        | Abre la tapa del blindaje                |
| 35         | PIN_BTN_SHIELD_CLOSE        | Botón cerrar blindaje (Wheel)       | Cierra la tapa del blindaje              |
| 36         | PIN_BTN_STOP                | Botón parada de emergencia          | Detiene el ciclo o activa emergencia     |
| 37         | PIN_BTN_GO_POS_1            | Botón ir a posición 1 (Gripper)     | Posición vertical 1 del gripper          |
| 38         | PIN_BTN_GO_POS_2            | Botón ir a posición 2 (Gripper)     | Posición vertical 2 del gripper          |
| 39         | PIN_BTN_GO_POS_3            | Botón ir a posición 3 (Gripper)     | Posición vertical 3 del gripper          |
| 40         | PIN_BTN_GRIPPER_CATCH       | Botón capturar Marinelli (Gripper)  | Cierra el gripper                        |
| 41         | PIN_BTN_GRIPPER_RELEASE     | Botón liberar Marinelli (Gripper)   | Abre el gripper                          |
| 45         | PIN_BTN_SEQUENCE_START      | Botón inicio de secuencia           | Inicia ciclo automático                  |
| Serial1    | SerialNodeWheel             | Comunicación con Nodo Wheel         | UART                                     |
| Serial2    | SerialNodeSpindle/Gripper   | Comunicación con Nodo Gripper       | UART                                     |

---

## Nodo Wheel

| Pin físico | Nombre en código         | Sensor/Actuador conectado           | Descripción breve                |
|------------|-------------------------|-------------------------------------|----------------------------------|
| 2          | MOTOR_PWM               | PWM motor mesa                      | Control velocidad motor mesa     |
| 3          | BTN_NEXT                | Botón avanzar muestra               | Avanza a la siguiente muestra    |
| 4          | BTN_CYCLE               | Botón ciclo muestra                 | Vuelve a posición base/ciclo     |
| 5          | BTN_UP                  | Botón subir mesa                    | Sube la mesa niveladora          |
| 6          | BTN_DOWN                | Botón bajar mesa                    | Baja la mesa niveladora          |
| 7          | SENS_ORANGE             | Sensor adicional (naranja)          | Sensor de avance de muestra      |
| 8          | SENS_VIOLET             | Sensor adicional (violeta)          | Sensor de avance de muestra      |
| 9          | SENS_GREEN              | Sensor blindaje abierto             | Detecta si la tapa está abierta  |
| 10         | SENS_BLUE               | Sensor blindaje cerrado             | Detecta si la tapa está cerrada  |
| 11         | BTN_OPEN                | Botón abrir blindaje                | Abre la tapa del blindaje        |
| 12         | BTN_CLOSE               | Botón cerrar blindaje               | Cierra la tapa del blindaje      |
| 40         | SENSOR_TOP1             | Sensor mesa arriba 1                | Detecta si la mesa está arriba   |
| 41         | SENSOR_TOP2             | Sensor mesa arriba 2                | Detecta si la mesa está arriba   |
| 42         | SENSOR_BOTTOM1          | Sensor mesa abajo 1                 | Detecta si la mesa está abajo    |
| 43         | SENSOR_BOTTOM2          | Sensor mesa abajo 2                 | Detecta si la mesa está abajo    |
| 46         | RLY_DOOR_OPEN           | Relé apertura blindaje              | Activa apertura de la tapa       |
| 47         | RLY_DOOR_CLOSE          | Relé cierre blindaje                | Activa cierre de la tapa         |
| 48         | RLY_SAMPLE_NEXT         | Relé avance muestra                 | Avanza a la siguiente muestra    |
| A0         | DRIVER_IN2              | Driver motor IN2                    | Control dirección motor mesa     |
| A1         | DRIVER_IN1              | Driver motor IN1                    | Control dirección motor mesa     |
| A2         | BUZZER                  | Buzzer                              | Alarma sonora                    |
| Serial1/2  | SerialNodeMaster        | Comunicación Nodo Maestro           | UART                             |

---

## Nodo Gripper

> **Nota:** La asignación de pines puede variar según la versión de hardware. Verifica en `Hardware_NodeGripper.h` para tu versión.

| Pin físico | Nombre en código         | Sensor/Actuador conectado           | Descripción breve                        |
|------------|-------------------------|-------------------------------------|------------------------------------------|
| D2         | GRIPPER_OPEN            | Relé abrir gripper                  | Activa apertura del gripper              |
| D3         | GRIPPER_CLOSE           | Relé cerrar gripper                 | Activa cierre del gripper                |
| D4         | SENS_GRIPPER_OPEN       | Sensor gripper abierto              | Detecta si el gripper está abierto       |
| D5         | SENS_GRIPPER_CLOSED     | Sensor gripper cerrado              | Detecta si el gripper está cerrado       |
| D6         | RLY_GRIPPER_ROTATE_L    | Relé rotación izquierda             | Rota el gripper a la izquierda           |
| D7         | RLY_GRIPPER_ROTATE_R    | Relé rotación derecha               | Rota el gripper a la derecha             |
| D8         | SENS_GRIPPER_LEFT       | Sensor gripper izquierda            | Detecta posición izquierda               |
| D9         | SENS_GRIPPER_RIGHT      | Sensor gripper derecha              | Detecta posición derecha                 |
| RX         | SerialNodeMaster RX     | Comunicación Nodo Maestro           | UART RX                                  |
| TX         | SerialNodeMaster TX     | Comunicación Nodo Maestro           | UART TX                                  |

---

> **Nota:** Los nombres pueden variar según la definición en los archivos `Hardware_NodeMaster.h`, `Hardware_NodeWheel.h` y `Hardware_NodeGripper.h`.  
> Consulta esos archivos para confirmar la correspondencia exacta y posibles cambios de hardware.