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

void sistema_operativo (int *band){
  #ifdef _WIN32
    *band = 0;
    #elif __linux__
      srand (time (NULL));
      *band = 1;
  #endif
}

int numero_random_l (int tope){
  return rand () % (tope + 1);
}

int numero_random_w (int tope){
  unsigned int a = rand ();
  unsigned int b = rand ();
  unsigned long int c =  ((long) a * (long)b) % tope;
  return c;
}

int generar_numero_random (int band, int tope){
  int devolver;
  // Lo hicimos con switch por si se quisieran agreagar mas sistemas operativos.
  switch (band) {
    case 0:
      devolver = numero_random_w (tope);
      break;
    case 1:
      devolver = numero_random_l (tope);
      break;
    default:
      devolver = numero_random_l (tope);
  }
  return devolver;
}

ARandom* posiciones_aleatorias (int cant, int longArchivo){
  ARandom *arregloRand = malloc (sizeof (ARandom) * (cant + 1));
  for (int i = 0; i < cant; ++i){
    arregloRand[i].numLinea = -1;
    arregloRand[i].pos = -1;
  }
  int nRandom;
  int os;
  sistema_operativo (&os);

  // Rellenando el arreglo a devolver.
  for (int j = 1; j <= cant; ++j){
    // Creando numero aleatorio.
    nRandom = generar_numero_random (os, longArchivo);
    // Actualizando el maximo.
    if (arregloRand[0].numLinea < nRandom){
      arregloRand[0].numLinea = nRandom;
      arregloRand[0].pos = -1;
    }
    // Actualizando el arreglo.
    arregloRand[j].numLinea = nRandom;
    arregloRand[j].pos = j - 1;
  }
  return arregloRand;
}

int ARandom_mayor (const void *dato1, const void *dato2){
  int devolver = -1;

  if (((ARandom*)dato1)->numLinea > ((ARandom*)dato2)->numLinea)
    devolver = 1;

  return devolver;
}

char **generar_arreglo (char *nombreArchivoE, int cant, int *bandera, int longArchivo){
  // Creando el arreglo a devolver.
  char **arregloNombres = malloc (sizeof (char*) * cant);
  for (int i = 0; i < cant; ++i)
    arregloNombres[i] = malloc (sizeof (char) * BUFFER);

  // Arreglo que tendra los numeros de lineas.
  ARandom *arrayPos = posiciones_aleatorias(cant, longArchivo);
  // se hace en +1 porque el primero tiene el mas grande repetido y no nos
  // interesa ordenarlo.
  qsort (arrayPos + 1, cant, sizeof(ARandom), ARandom_mayor);
  FILE *Archivo = fopen (nombreArchivoE, "r");
  // si se abrio correctamente...
  if (Archivo != NULL){
    char buffer[BUFFER];
    // colocados comienza desde 1 pues queremos saltear el primer elemento de
    // arrayPos.
    for (int i = 0, colocados = 1; i <= arrayPos[0].numLinea; ++i){
      fscanf (Archivo, "%[^\r\n]\r\n", buffer);
      // Si la linea que almaceno el buffer, es de las que nos interesa
      // entonces la guardamos en el arregloNombres.
      while (colocados < cant + 1 && i == arrayPos[colocados].numLinea){
        strcpy (arregloNombres[arrayPos[colocados].pos], buffer);
        ++colocados;
      }
    }
    // Se modifica la bandera, indicando que el archivo se manipulo bien.
    *bandera = 0;
  }
  else{
    printf ("No se pudo abrir el archivo de extracion de datos.\n");
  }
  free (arrayPos);
  fclose (Archivo);
  return arregloNombres;
}

int generar_edad (){
  return (rand() % 100) + 1;
}

void escribir_archivo (char **arregloNombres, char **arregloPaises, int cantLineas, char *nombreArchivoS, int *bandera){
  FILE *archivoSalida = fopen(nombreArchivoS, "w");
  // Si el archivo se abrio correctamente...
  if (archivoSalida != NULL){
    int edad;
    for (int i = 0; i < cantLineas; ++i){
      edad = generar_edad ();
      fprintf (archivoSalida,"%s, %d, %s\n", arregloNombres[i], edad, arregloPaises[i]);
    }
    // Se modifica la bandera, indicando que el archivo se uso correctamente.
    *bandera = 0;
  }
  else {
    printf("No se pudo abrir el archivo de escritura\n");
  }
  fclose (archivoSalida);
}

void destruir_arraybi (char **array, int longitud){
  for (int i = 0; i < longitud; ++i){
    free (array[i]);
  }
  free (array);
}