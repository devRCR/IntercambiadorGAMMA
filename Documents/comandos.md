# Comandos del Nodo Maestro al Nodo Wheel (Protocolo Serial)

## Tabla de comandos y respuestas

| Comando | Acción esperada                        | ACK esperado              | Timeout (ms) |
|---------|----------------------------------------|---------------------------|--------------|
| P0    | Subir la mesa niveladora               | K350 – STATE_PLATE_UP | 10,000       |
| P1    | Bajar la mesa niveladora               | K300 – STATE_PLATE_DOWN | 10,000     |
| H0    | Abrir la tapa del blindaje             | K250 – STATE_SHIELD_OPEN | 10,000   |
| H1    | Cerrar la tapa del blindaje            | K200 – STATE_SHIELD_CLOSE | 10,000  |
| S0    | Volver a posición base (ciclo)         | K150 – STATE_SAMPLE_CYCLE | 10,000 |
| S1    | Avanzar a siguiente muestra            | K100 – STATE_SAMPLE_NEXT | 10,000   |
| T0    | Parada de emergencia (sin acción física) | K499 – STATE_EMERGENCY_STOP | —      |

## Códigos de error (ERROR)

| Código | Descripción del error                         | Aplica a       |
|--------|-----------------------------------------------|----------------|
| E0   | Comando no reconocido o inválido              | Todos          |
| E1   | Timeout en movimiento de la mesa              | P0, P1     |
| E2   | Mesa no está abajo (bloqueo de seguridad)     | H0, H1     |
| E3   | Timeout en blindaje (abrir o cerrar)          | H0, H1     |
| E4   | Timeout en avance de muestra                  | S0, S1     |

## Notas técnicas

- **ACK (K\<estado\>)** se emite únicamente al finalizar con éxito el proceso físico (confirmado por sensores).
- **ERROR (E\<code\>)** se emite si falla una condición de seguridad o se excede el timeout.
- **Si el sistema ya está en el estado solicitado (ej. mesa arriba al recibir P0), igualmente se emite el ACK correspondiente.**

---

## Condiciones de ejecución de comandos

Cada comando recibido por el Nodo Wheel se ejecuta bajo las siguientes condiciones generales:

- El comando debe recibirse correctamente desde el Nodo Maestro o desde el PC local.
- El comando debe estar correctamente parseado (analizado) y reconocido por el sistema.
- La ejecución del comando depende del estado actual de los mecanismos y sensores asociados. Por ejemplo:
  - **Comandos de la mesa niveladora (P0, P1)**: Se ejecutan si la mesa no está ya en la posición solicitada y no hay un movimiento en curso.  
    - **Nota:** Si la mesa ya está en la posición solicitada, igualmente se emite el ACK correspondiente.
  - **Comandos de la tapa del blindaje (H0, H1)**:  
    - Solo se ejecutan si la mesa niveladora está completamente abajo (ambos sensores SENSOR_BOTTOM1 y SENSOR_BOTTOM2 activos).
    - Si la mesa no está abajo, se responde con error E2 y no se ejecuta la acción.
    - Además, solo se ejecutan si la tapa no está ya en la posición solicitada y no hay una acción de tapa en curso.  
    - **Nota:** Si la tapa ya está en la posición solicitada, igualmente se emite el ACK correspondiente.
  - **Comandos de avance de muestra (S0, S1)**: Se ejecutan si no hay un avance de muestra en curso y la posición es válida.  
    - **Nota:** Si la muestra ya está en la posición solicitada, igualmente se emite el ACK correspondiente.
  - **Comando de parada de emergencia (T0)**: Se ejecuta inmediatamente, deteniendo cualquier acción en curso.

### Flujo general de ejecución

1. El sistema revisa continuamente si hay comandos nuevos desde el Maestro o el PC.
2. Si hay un comando válido, se ejecuta la función correspondiente según el tipo de comando y valor recibido.
3. Cada controlador modular (mesa, tapa, muestra) verifica internamente si puede ejecutar la acción solicitada, considerando el estado de sensores y movimientos previos.
4. Si la acción no es posible (por ejemplo, por error de sensor o condición de seguridad), se responde con un código de error.

### Ejemplo de ejecución

- Si se recibe P0 (subir mesa) y la mesa ya está arriba, **se emite el ACK correspondiente**.
- Si se recibe H1 (cerrar tapa) mientras la tapa ya está cerrada, **se emite el ACK correspondiente**.
- Si se recibe S1 (avanzar muestra) y la muestra ya está en la posición solicitada, **se emite el ACK correspondiente**.
- Si se recibe un comando y el mecanismo está ocupado o hay un error de sensor, se responde con error.

Consulta la documentación de cada controlador para detalles específicos de las condiciones internas.