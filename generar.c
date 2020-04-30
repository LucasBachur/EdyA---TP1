#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <assert.h>
#include "generacion.h"


#define LONG_ARCHIVO_N 99999
#define LONG_ARCHIVO_P 450


// Al main le vamos a pasar, el nobmre del archivo base, el de salida
// y la cant de elementos a generar.
int main (int argc, char **argv){
  assert (argc == 5);
  int cant = atoi(argv[4]);
  int bandera1 = 1, bandera2 = 2, bandera3 = 3, retorno = 0;

  char **arreglo_nombres = generar_arreglo(argv[1], cant, &bandera1, LONG_ARCHIVO_N);
  // Si no hubo problemas con el archivo...
  if (bandera1 == 0){
    char **arreglo_paises = generar_arreglo(argv[2], cant, &bandera2, LONG_ARCHIVO_P);
    // Si no hubo problemas con el archivo...
    if (bandera2 == 0){
      escribir_archivo (arreglo_nombres, arreglo_paises, cant, argv[3], &bandera3);
      destruir_arraybi (arreglo_paises, cant);
      destruir_arraybi (arreglo_nombres, cant);
      // Si no hubo problemas con el archivo...
      if (bandera3 == 0){
        printf ("Archivo de datos de prueba generado con exito.\n");
      }else{
        retorno = bandera3;
      }
    }else{
      retorno = bandera2;
    }
  }else{
    retorno = bandera1;
  }

  return retorno;
}
