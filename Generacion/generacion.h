#ifndef __GENERACION_H__
#define __GENERACION_H__

typedef struct _random{
  int numLinea;
  int pos;
} ARandom;


// Dado un puntero a enteros, de una bandera, devuelve:
// 0 si se esta en windows.
// 1 si se esta en linux.
void sistema_operativo (int *band);

// En linux, genera un numero random entre 0 y el tope.
int numero_random_l (int tope);

// En windows, genera un numero random entre 0 y el tope.
int numero_random_w (int tope);

// Dada una bandera, que indica en que sistema operativo nos encontramos,
// y un tope, genera un numero random entre 0 y el tope.
int generar_numero_random (int band, int tope);

// Dada una cantidad, y la longitud del archivo del que se quieren extraer
// datos.
// Devuelve un puntero a ARandom que tiene espacio para cant + 1 elementos.
// Este cada elemento tendra un numero aleatorio de linea, y la posicion en la
// que salio este elemento. El primer elemento tiene el maximo numero de linea.
ARandom* posiciones_aleatorias (int cant, int longArchivo);

// Funcion especifica para el qsort.
// Dados 2 datos ARandom, devuelve 1 si el num_linea del primero es mayor que el
// del segundo, caso contrario devuelve -1.
int ARandom_mayor (const void *dato1, const void *dato2);

// Dado un archivo contenedor de los nombres, y la cantidad de nombres a extraer
// Genera un arreglo con dichos nombres.
char **generar_arreglo (char *nombreArchivoE, int cant, int *bandera, int longArchivo);

// Genera un numero aleatorio entre 1 y 100 y lo devuelve.
int generar_edad ();

// Dados, dos puntero a punteros a char, que representan "listas" de nombres y
// paises respectivamente, la cantidad de lineas a escribir, un nombre de
// archivo de salida, y una bandera.
// Escribe en el archivo de salida una linea estructurada:
// arregloNombres[i], edad, arregloPaises[i]
// Si no hubo problemas al abrir el archivo de escritura, la bandera cambiara a
// 0. Caso contrario mantendra su valor original, indicando que no se abrio.
void escribir_archivo (char **arregloNombres, char **arregloPaises, int cantLineas, char *nombreArchivoS, int *bandera);

// Dado un puntero a punteros a char, y un entero representando la cantidad de
// punteros a char.
// Libera todos los punteros.
void destruir_arraybi (char **array, int longitud);

#endif
