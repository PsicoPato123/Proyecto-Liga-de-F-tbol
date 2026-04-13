# Proyecto-Liga-de-F-tbol
Nombre de liga: Liga huevito ^w^ Creada por: Lucia Valencia

Descripción del programa Liga Huevito es un programa en C++ que permite gestionar una liga de fútbol entre patos 🦆⚽. El sistema lee los equipos desde un archivo, registra partidos creados por el usuario, guarda resultados y muestra una tabla de posiciones ordenada automáticamente según los puntos que correspondan en cada partido. Además, se puede obtener un ganador de liga en el momento que el usuario desee

¿Cómo compilar?

¿Cómo ejecutar?

Formato de Config El archivo contiene el nombre de la liga y la lista de equipos, uno por línea.

Ejemplo:

image
Para tener en cuenta:
La primera línea es el nombre de la liga y las siguientes líneas son los equipos. No se deben usar símbolos como : o =.

Descripción del diseño

Separación de funciones: Se dividió el programa en funciones como lectura, registro, cálculo y visualización para mantener el código ordenado.
Uso de archivos: Se usan archivos de texto como: config.txt, partidos.txt, fechas.txt y tabla.txt para guardar la información de forma continua.
Cálculo dinámico de la tabla: La tabla de posiciones se genera a partir de los partidos registrados, en lugar de guardarla directamente.
Ordenamiento automático: Los equipos se ordenan por puntos (arriba mayoría y va descendiendo según la cantidad de puntos). Para esto se usan: Puntos (P), diferencia de gol (DG) y goles a favor o en contra (GF o GC)
Uso de punteros/referencias: Se actualizan estadísticas directamente sobre los equipos para optimizar memoria y cumplir requisitos.
Colores: Se presentan algunos cambios de color en las letras de la terminal para hacer más dinámica la experiencia en el programa.
