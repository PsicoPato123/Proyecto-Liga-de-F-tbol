# Proyecto-Liga-de-F-tbol
Nombre de liga: Liga huevito ^w^ Creada por: Lucia Valencia

Descripción del programa 
Liga Huevito es un programa en C++ que permite gestionar una liga de fútbol entre patitos. El sistema lee los equipos desde un archivo, registra partidos creados por el usuario, guarda resultados y muestra una tabla de posiciones ordenada automáticamente según los puntos que correspondan en cada partido. Además, se puede obtener un ganador de liga en el momento que el usuario desee obtenerlo.

¿Cómo compilar?
1. Abres tu terminal de preferencia
2. Busca donde está el proyecto y toma la ruta de entrada hasta "liga-futbol" y copias
3. En la terminal escribes "cd" seguido de la ruta del enlace y oprimes enter
4. Escribes g++ src/main.cpp (si no lee agregas -o liga)
   Así debe ir, por ejemplo:
   <img width="724" height="84" alt="image" src="https://github.com/user-attachments/assets/fc9d8e83-9cb7-4bd2-836d-db9ba3ee1ebb" />

5. Continúa al paso de ejecución 

¿Cómo ejecutar?
Para brindar la ejecución total del programa en la terminal, debes escribir ".\liga" y oprimir entres, consiguiente a esto se dará inicio al programa
<img width="657" height="62" alt="image" src="https://github.com/user-attachments/assets/57398a3e-3aff-4525-9038-0f0891cbaa4f" />


Formato de Config.txt
El archivo contiene el nombre de la liga, a cuantos puntos equivale la victoria, empate y perdida  y la lista de equipos, cada uno por línea.

Ejemplo:
<img width="256" height="119" alt="image" src="https://github.com/user-attachments/assets/512caffd-f6c2-4519-89eb-9349edf4d209" />

La primera línea es el nombre de la liga y las siguientes líneas son lospuntos seguidos de los equipos. 
#No se deben usar símbolos como : o =.

Descripción del diseño
Se dividió el programa en funciones como lectura, registro, cálculo y visualización para mantener el código ordenado, además de esto encontramos diferentes factores que mejoran la estructura, contando:
Uso de archivos: Se usan archivos de texto como: config.txt, partidos.txt, fechas.txt y tabla.txt para guardar la información de forma continua.
Cálculos de la tabla: La tabla de posiciones se genera a partir de los partidos registrados, en lugar de guardarla directamente.
Ordenamiento automático: Los equipos se ordenan por puntos (arriba mayoría y va descendiendo según la cantidad de puntos). Para esto se usan: Puntos (P), diferencia de gol (DG) y goles a favor o en contra (GF o GC)
Uso de punteros/referencias: Se actualizan estadísticas directamente sobre los equipos para optimizar memoria y cumplir requisitos.
Colores: Se presentan algunos cambios de color en las letras de la terminal para hacer más dinámica la experiencia en el programa.
