#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "glist.h"
#include "Persona/persona.h"

#define BUFFER 180

// Dado un nombre de un archivo de entrada, devuelve una lista con sus datos.
// interpretar_archivo: char* -> GList
GList interpretar_archivo (char *nombreArchivoEntrada);



int main (int argc, char **argv){
  assert (argc == 2);

  GList lista = glist_crear ();

  char nombreArchivoEntrada[80] = "Listas/";
  strcat (nombreArchivoEntrada, argv[1]);

  lista = interpretar_archivo (nombreArchivoEntrada);

  glist_ordenar_archivar ("Edad_menor_selection.txt", imprimir_persona_archivo, glist_selection_sort, edad_menor, lista);

  glist_imprimir_archivo (&lista, imprimir_persona_archivo, "Lista original.txt", -1);

  glist_ordenar_archivar ("Edad_menor_insertion.txt", imprimir_persona_archivo, glist_insertion_sort, edad_menor, lista);

  glist_ordenar_archivar ("Edad_menor_mergesort.txt", imprimir_persona_archivo, glist_merge_sort, edad_menor, lista);

  glist_ordenar_archivar ("Largo_nombre_menor_selection.txt", imprimir_persona_archivo, glist_selection_sort, largo_nombre_menor, lista);

  glist_ordenar_archivar ("Largo_nombre_menor_insertion.txt", imprimir_persona_archivo, glist_insertion_sort, largo_nombre_menor, lista);

  glist_ordenar_archivar ("Largo_nombre_menor_mergesort.txt", imprimir_persona_archivo, glist_merge_sort, largo_nombre_menor, lista);



  glist_destruir (&lista,liberar_persona);
}
GList interpretar_archivo (char *nombreArchivoEntrada){
  GList listaInterpretada = glist_crear ();
  FILE *Archivo = fopen (nombreArchivoEntrada, "r");
  if (Archivo != NULL){
    // Archivo abierto con extio.
    Persona *personaAlegre = NULL; // que elagancia la de francia
    char nombre[BUFFER], pais[BUFFER];
    int edad;
    while (fscanf (Archivo, "%[^,], %d, %[^\n]\n", nombre, &edad, pais) != EOF){
      // Creando la persona.
      personaAlegre = crear_persona (nombre, edad, pais);
      // Agreando a persona a la lista.
      glist_agregar_final (&listaInterpretada, personaAlegre);
    }
  }else{
    printf ("Archivo para generar lista fallo.\n");
  }
  fclose (Archivo);
  return listaInterpretada;
}
