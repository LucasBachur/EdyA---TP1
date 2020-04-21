// Este programa, lee el archivo, y escribe en otro las personas con sus caracteristicas
// de la sigueinte manera:
// Juan Perez, 19, Villa General Belgrano
// Francisco Jose Maria Olviares, 23, Rosario
// Hay un archivo de localidades, uno de nombres y los numeros son de 1 a 100.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define LONG_ARCHIVO_N 99999
#define LONG_ARCHIVO_P 450
#define BUFFER 80

typedef struct {
  char * nombre;
  int edad;
  char * lugardenacimiento; // pais o capital
} Persona;

typedef struct _random{
  int num_linea;
  int pos;
} ARandom;

ARandom* posiciones_aleatorias (int cant, int longitud_archivo);
char **generar_arreglo_nombres (char *nombre_archivo, int cant, int *bandera);
int mayor (const void *dato1, const void *dato2);
int generar_edad ();
void print_array (ARandom *array, int longitud);
void print_array_charpointers (char **array, int longitud);
int generar_edad (){
  return (rand() % 100) + 1;
}

// Dado un archivo contenedor de los nombres, y la cantidad de nombres a extraer
// Genera un arreglo con dichos nombres.
char **generar_arreglo_nombres (char *nombre_archivo, int cant, int *bandera){
  FILE *Archivo = fopen (nombre_archivo, "r");
  char **arreglo_nombres = malloc (sizeof (char*) * cant);

  for (int i = 0; i < cant; ++i)
    arreglo_nombres[i] = malloc (sizeof (char) * BUFFER);

  if (Archivo != NULL){
    // manipular el Archivo
    char buffer[BUFFER];
    ARandom *array_posiciones = posiciones_aleatorias(cant, LONG_ARCHIVO_N);
    // se hace en +1 porque el primero tiene el mas grande repetido
    qsort (array_posiciones + 1, cant, sizeof (ARandom), mayor);

    for (int i = 0, elto = 1; i <= array_posiciones[0].num_linea; ++i){
      fscanf (Archivo, "%[^\n]\n", buffer);

      // Si la linea que almaceno el buffer, es de las que nos interesa
      // entonces la guardamos en el arreglo_nombres.
      if (i == array_posiciones[elto].num_linea){
        strcpy (arreglo_nombres[array_posiciones[elto].pos], buffer);
        ++elto;
      }
    }


  }
  else{
    printf ("Se rompio el archivo.. \n");
    *bandera = 1; // Valor que indica que la funcion no funciono porque no habrio el archivo.
  }
  fclose (Archivo);
  return arreglo_nombres;
}
// Alternativas para, dejar el tamano de buffer y usar fscanf vs usar getc y
// asignar precisamente el tamano de los elementos de arreglo_nombres.
// Ver si conviene ajustar el tamano de cada elemento de arreglo_nombres con
// un strlen.


// char** generar_arreglo_localidades (char *nombre_archivo, int cant){}

// Tambien devuelve el maximo para saber hasta donde recorrer del archivo.
// Los randoms no tienen que repetidos.
// Arreglar palomar.
ARandom* posiciones_aleatorias (int cant, int longitud_archivo){
  // Cambiando la semilla de generacion.
  srand (time(NULL));

  ARandom *arreglo_rand = malloc (sizeof (ARandom) * cant + 1);
  int *arreglo_auxiliar = malloc (sizeof (int) * longitud_archivo);

  // Inicializando arreglo en -1, que representara las posiciones no usadas.
  for (int i = 0; i < longitud_archivo; ++i){
    arreglo_auxiliar[i] = -1;
  }

  int n_random;
  // Rellenando el arreglo a devolver.
  for (int j = 1; j <= cant;){
    // Creando numero aleatorio.
    n_random = rand() % longitud_archivo;
    // Si el numero no fue utilizado, actualiza y se agrega al array a devolver.
    if (arreglo_auxiliar[n_random] == -1){
      if (arreglo_rand[0].num_linea < n_random){
        arreglo_rand[0].num_linea = n_random;
        arreglo_rand[0].pos = -1;
      }
      arreglo_auxiliar[n_random] = 0;
      arreglo_rand[j].num_linea = n_random;
      arreglo_rand[j].pos = j - 1;
      ++j;
    }
  }
  return arreglo_rand;
}


// Averiguar bien que es const void?
int mayor (const void *dato1, const void *dato2){
  int devolver = -1;

  if (((ARandom*)dato1)->num_linea > ((ARandom*)dato2)->num_linea)
    devolver = 1;

  return devolver;
}


// Al main le vamos a pasar, el nobmre del archivo base, el de salida
// y la cant de elementos a generar.
int main (int argc, char **argv){
  printf ("%d", argc);
  int cant = atoi(argv[3]);
  int bandera1 = 0, retorno = 0;
  FILE *Archivo_salida = fopen(argv[2], "w");
  char **arreglo_nombres = generar_arreglo_nombres(argv[1], cant, &bandera1);

  for (int i = 0; i < cant; ++i){
    fprintf (Archivo_salida, "%s\n", arreglo_nombres[i]);
  }
  return retorno;
}
