#ifndef __GENERACION_H__
#define __GENERACION_H__

typedef struct _random{
  int num_linea;
  int pos;
} ARandom;

char **generar_arreglo (char *nombre_archivo, int cant, int *bandera, int longitud_archivo);

int mayor (const void *dato1, const void *dato2);

ARandom* posiciones_aleatorias (int cant, int longitud_archivo);

int generar_edad ();

void escribir_archivo (char **arreglo_nombres, char **arreglo_paises, int cant_lineas, char *nombre_archivo, int *bandera);

void destruir_arraybi (char **array, int longitud);

#endif
