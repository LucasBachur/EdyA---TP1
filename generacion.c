// Este programa, lee el archivo, y escribe en otro las personas con sus caracteristicas
// de la sigueinte manera:
// Juan Perez, 19, Villa General Belgrano
// Francisco Jose Maria Olviares, 23, Rosario
// Hay un archivo de localidades, uno de nombres y los numeros son de 1 a 100.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LONG_ARCHIVO_N 99999
#define LONG_ARCHIVO_P 450
#define BUFFER 80

typedef struct {
  char * nombre;
  int edad;
  char * lugardenacimiento; // pais o capital
} Persona;

typedef struct _random{
  int dato;
  int pos;
} ARandom;

// Al main le vamos a pasar, el nobmre del archivo base, el de salida
// y la cant de elementos a generar.
int main (int argc, char *argv[]){
  int cant = atoi(argv[3]);
  char **arreglo_nombres = generar_arreglo_nombres(argv[0], argv[])
}

int generar_edad (){
  return (rand() % 100) + 1;
}

// Dado un archivo contenedor de los nombres, y la cantidad de nombres a extraer
// Genera un arreglo con dichos nombres.
char **generar_arreglo_nombres (char *nombre_archivo, int cant){
  FILE *Archivo = fopen (nombre_archivo, "r");
  char **arreglo_nombres = malloc (sizeof (char*) * cant);

  if (Archivo != NULL){
    // manipular el Archivo
    char buffer[BUFFER];
    int *array_posiciones = posiciones_aleatorias(cant, LONG_ARCHIVO_N);
    int max = array_posiciones[0];

    for (int i = 0; i <= max; ++i){
      fscanf (Archivo, "%^[\n]", buffer);
      // Si la linea que almaceno el buffer, es de las que nos interesa
      // entonces la guardamos en el arreglo_nombres.
      if (contiene (array_posiciones, i)){
        arreglo_nombres[posiciones_aleatorias[i]] = malloc (sizeof (char) * BUFFER);
        arreglo_nombres[posiciones_aleatorias[i]] = buffer;
      }
    }
  }
  else{
    printf ("Se rompio el archivo.. \n");
  }
  fclose (Archivo);
  return arreglo_nombres;
}
// Alternativas para, dejar el tamano de buffer y usar fscanf vs usar getc y
// asignar precisamente el tamano de los elementos de arreglo_nombres.
// Ver si conviene ajustar el tamano de cada elemento de arreglo_nombres con
// un strlen.


char** generar_arreglo_localidades (char *nombre_archivo, int cant){}

// Tambien devuelve el maximo para saber hasta donde recorrer del archivo.
// Los randoms no tienen que repetidos.
ARandom* posiciones_aleatorias (int cant, int longitud_archivo){
  ARandom *arreglo_rand = malloc (sizeof (ARandom) * cant);
  int i = 0;
  // Inicializando arreglo en -1, que representara las posiciones no usadas.
  for (; i < cant; ++i){
    arreglo_rand[i].dato = -1;
  }
  int random;
  i = 0;
  while (i < cant){
    random = (rand () % longitud_archivo) + 1;
    if (arreglo_rand[random].dato == -1)
      arreglo_rand[random].dato = random;
      arreglo_rand[random].pos = i;
      ++i
  }
}


/*
crear una estructura que tenga dos enteros, ordenamos en base al primer numero,
y el segundo representa su posicion final en el arreglo.

ordeanr en base al primer numero, esto con qsort. Que es el mas rapido.
*/
