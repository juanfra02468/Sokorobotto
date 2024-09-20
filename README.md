# Sokorobotto

## Descripción

**Sokorobotto** es una práctica inspirada en el clásico juego de rompecabezas **Sokoban**, donde un robot debe mover cajas a posiciones finales dentro de un tablero hasta que todas las cajas estén en sus objetivos. El proyecto simula un almacén donde el robot organiza las cajas, siguiendo reglas específicas.

## Historia de Sokoban

**Sokoban** es un juego de rompecabezas japonés cuyo nombre significa "encargado de almacén". La misión es empujar cajas hacia objetivos, sin posibilidad de retroceder ni mover más de una caja a la vez. El reto del juego está en la lógica y planificación de movimientos.

## Reglas de Sokorobotto

Las reglas de **Sokorobotto** son similares a las del juego original, con algunas variaciones:

- El tablero es una matriz de **10x10**.
- Se permite un máximo de **3 cajas** y **3 objetivos**.
- Las cajas solo pueden ser empujadas hacia **posiciones vacías**.
- Ni el robot ni las cajas pueden atravesar **muros**.
- No se puede tirar de las cajas, solo empujar.
- Los movimientos permitidos son **horizontales y verticales**.
- El robot puede intercambiar su posición con una caja, pero el máximo permitido es de **tres intercambios** por nivel.
- El objetivo es alcanzar el **estado final** donde todas las cajas están en sus posiciones objetivo.

## Elementos del Tablero

- **Robot**: Se mueve por las casillas vacías o almacenes, empuja las cajas y puede intercambiar su posición con ellas.
- **Cajas**: Deben ser empujadas hacia las casillas objetivo. No pueden moverse solas, ni atravesar muros.
- **Casillas Vacías**: Zonas donde el robot puede moverse y empujar las cajas.
- **Almacenes (Objetivos)**: Posiciones donde deben colocarse las cajas.
- **Muros**: Obstáculos que bloquean el paso del robot y de las cajas.

## Carga de Tableros

El tablero se carga a partir de un fichero bien formado con una matriz de **10x10** posiciones. Se proporcionan ficheros con 10 filas y 10 columnas, separados por comas. Los ficheros contienen un robot, hasta tres cajas y tres posiciones objetivo.

## Resolución del Problema

Para resolver el problema, se emplean **algoritmos heurísticos** debido a la limitación de tiempo. Los algoritmos implementados son:

- **Escalada Simple**.
- **Escalada de Máxima Pendiente**.
- **Búsqueda del Primero Mejor**.
- **Algoritmo A\***.
