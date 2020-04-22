// Este programa, lee el archivo, y escribe en otro las personas con sus caracteristicas
// de la sigueinte manera:
// Juan Perez, 19, Villa General Belgrano
// Francisco Jose Maria Olviares, 23, Rosario
// Hay un archivo de localidades, uno de nombres y los numeros son de 1 a 100.
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "generacion.h"

#define BUFFER 80


// Dado un archivo contenedor de los nombres, y la cantidad de nombres a extraer
// Genera un arreglo con dichos nombres.
char **generar_arreglo (char *nombre_archivo, int cant, int *bandera, int longitud_archivo){
  // Creando el arreglo a devolver.
  char **arreglo_nombres = malloc (sizeof (char*) * cant);
  for (int i = 0; i < cant; ++i)
    arreglo_nombres[i] = malloc (sizeof (char) * BUFFER);

  // Arreglo que tendra las lineas
  ARandom *array_posiciones = posiciones_aleatorias(cant, longitud_archivo);
  // se hace en +1 porque el primero tiene el mas grande repetido
  qsort (array_posiciones + 1, cant, sizeof(ARandom), mayor);
  FILE *Archivo = fopen (nombre_archivo, "r");
  if (Archivo != NULL){
    // manipular el Archivo
    char buffer[BUFFER];
    //int longitud_linea;
    for (int i = 0, elto = 1; i <= array_posiciones[0].num_linea; ++i){
      fscanf (Archivo, "%[^\n]\n", buffer);
      // Si la linea que almaceno el buffer, es de las que nos interesa
      // entonces la guardamos en el arreglo_nombres.
      while (i == array_posiciones[elto].num_linea){
        strcpy (arreglo_nombres[array_posiciones[elto].pos], buffer);
        ++elto;
      }
    }
    // Se modifica la bandera, indicando que el archivo se manipulo bien.
    *bandera = 0;
  }
  else{
    printf ("No se pudo abrir el archivo de extracion de datos.\n");
  }
  free (array_posiciones);
  fclose (Archivo);
  return arreglo_nombres;
}

int mayor (const void *dato1, const void *dato2){
  int devolver = -1;

  if (((ARandom*)dato1)->num_linea > ((ARandom*)dato2)->num_linea)
    devolver = 1;

  return devolver;
}

// Dada una cantidad, y la longitud del archivo del que se quieren extraer
// datos.
// Devuelve un arreglo del tipo ARandom cuya primer posicion, contiene
// el elemento con el mayor num_linea, y a partir de ahi, los demas elementos,
// se completan con un num_linea aleatorio, y su posicion en orden creciente,
// es decir, se guarda el orden original en el que salieron los aleatorios.
ARandom* posiciones_aleatorias (int cant, int longitud_archivo){
  ARandom *arreglo_rand = malloc (sizeof (ARandom) * (cant + 1));
  for (int i = 0; i < cant; ++i){
    arreglo_rand[i].num_linea = -1;
    arreglo_rand[i].pos = -1;
  }

  int n_random;
  // Rellenando el arreglo a devolver.
  for (int j = 1; j <= cant; ++j){
    // Creando numero aleatorio.
    n_random = rand() % (longitud_archivo + 1);
    // Actualizando el maximo.
    if (arreglo_rand[0].num_linea < n_random){
      arreglo_rand[0].num_linea = n_random;
      arreglo_rand[0].pos = -1;
    }
    // Actualizando el arreglo.
    arreglo_rand[j].num_linea = n_random;
    arreglo_rand[j].pos = j - 1;
  }
  return arreglo_rand;
}

int generar_edad (){
  return (rand() % 100) + 1;
}

void escribir_archivo (char **arreglo_nombres, char **arreglo_paises, int cant_lineas, char *nombre_archivo, int *bandera){
  int edad;
  FILE *Archivo_salida = fopen(nombre_archivo, "w");
  // Si el archivo se abrio correctamente...
  if (Archivo_salida != NULL){
    for (int i = 0; i < cant_lineas; ++i){
      edad = generar_edad ();
      fprintf (Archivo_salida, "%s, %d, %s\n", arreglo_nombres[i], edad, arreglo_paises[i]);
    }
    // Se modifica la bandera, indicando que el archivo se uso correctamente.
    *bandera = 0;
  }
  else {
    printf("No se pudo abrir el archivo de escritura\n");
  }
  fclose (Archivo_salida);
}

void destruir_arraybi (char **array, int longitud){
  for (int i = 0; i < longitud; ++i){
    free (array[i]);
  }
  free (array);
}

/*
Notas:
1-  Alternativas para, dejar el tamano de buffer y usar fscanf vs usar getc y
  asignar precisamente el tamano de los elementos de arreglo_nombres.
  Ver si conviene ajustar el tamano de cada elemento de arreglo_nombres con
  un strlen.

2-  Como deshacernos del printf ("%d", argc);.

3-  Diferencia entre const void y void?

4-  Solucionar errores de valgrind.

5- No tenemos problemas con los caracteres especiales (? (???????
*/
