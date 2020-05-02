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
  srand (time (NULL));
  assert (argc == 5);
  int cant = atoi(argv[4]);
  int bandera1 = 1, bandera2 = 2, bandera3 = 3, retorno = 0;

  // Si bien se podrian hacer en un solo buffer, preferimos dejarlo asi por
  // claridad.
    char nombreANombres[200] = "Generacion/";
    strcat (nombreANombres, argv[1]);
    char nombreAPaises[200] = "Generacion/";
    strcat (nombreAPaises, argv[2]);
    char nombreASalida[200] = "Listas/";
    strcat (nombreASalida, argv[3]);

  char **arreglo_nombres = generar_arreglo(nombreANombres, cant, &bandera1, LONG_ARCHIVO_N);
  // Si no hubo problemas con el archivo...
  if (bandera1 == 0){
    char **arreglo_paises = generar_arreglo(nombreAPaises, cant, &bandera2, LONG_ARCHIVO_P);
    // Si no hubo problemas con el archivo...
    if (bandera2 == 0){
      escribir_archivo (arreglo_nombres, arreglo_paises, cant, nombreASalida, &bandera3);
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

// Todas las funciones del .h comentadas (done).
// Todas las funciones del .c explicadas ().
// Ver en windows si funciona lo de rand (consulta hecha a la catedra, esperar respuesta).
