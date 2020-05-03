#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "glist.h"


#define BUFFER 180

typedef struct {
char *nombre;
int edad;
char *lugarDeNacimiento; // pais o capital
} Persona;

// Dado un puntero a void, lo interpreta
// como persona, y libera los atributos 'nombre' y 'lugarDeNacimiento'.
// liberar_persona: void* ->
void liberar_persona (void *persona){
  free (((Persona*)persona)->nombre);
  free (((Persona*)persona)->lugarDeNacimiento);
  free (persona);
}

// Dados dos punteros a void,
// los interpreta como personas y compara sus atributos 'edad'.
// edad_menor: void* void* -> int
int edad_menor (void *dato1, void *dato2){
  int edad1 = ((Persona*)dato1)->edad;
  int edad2 = ((Persona*)dato2)->edad;

  return edad1 - edad2;
}

// Dados dos punteros a void,
// los interpreta como personas y compara el largo de sus nombres.
// largo_nombre_menor: void* void* -> int
int largo_nombre_menor (void *dato1, void *dato2){
  int largo1 = strlen (((Persona*)dato1)->nombre);
  int largo2 = strlen (((Persona*)dato2)->nombre);

  return largo1 - largo2;
}

// Dado un dato como puntero a void, y un archivo abierto en modo de escritura,
// escribe el dato interpretandolo como persona.
// imprimir_persona_archivo: void* FILE* ->
void imprimir_persona_archivo (void *dato, FILE *Archivo){
  fprintf (Archivo, "%s, %d, %s\n", ((Persona*)dato)->nombre,
   ((Persona*)dato)->edad, ((Persona*)dato)->lugarDeNacimiento);
}

// Dado un nombre, una edad, y un pais. Devuelve un puntero a Persona que tiene
// un solo elemento y sus datos son los que se pasaron a la funcion.
// crear_persona: char* int char* -> Persona*
Persona* crear_persona (char *nombre, int edad, char *pais){
  Persona *nuevaPersona = malloc (sizeof (Persona));
  nuevaPersona->nombre = malloc (sizeof (char) * 80);
  nuevaPersona->lugarDeNacimiento =  malloc (sizeof (char) * 80);

  strcpy (nuevaPersona->nombre, nombre);
  nuevaPersona->edad = edad;
  strcpy (nuevaPersona->lugarDeNacimiento, pais);

  return nuevaPersona;
}

// Dado un nombre de un archivo de entrada, devuelve una lista con sus datos.
// interpretar_archivo: char* -> GList
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



int main (int argc, char **argv){
  assert (argc == 2);

  GList lista = glist_crear ();

  char nombreArchivoEntrada[80] = "Listas/";
  strcat (nombreArchivoEntrada, argv[1]);

  lista = interpretar_archivo (nombreArchivoEntrada);

  glist_ordenar_archivar ("Edad_menor_selection", imprimir_persona_archivo, glist_selection_sort, edad_menor, lista);

  glist_ordenar_archivar ("Edad_menor_insertion", imprimir_persona_archivo, glist_insertion_sort, edad_menor, lista);

  glist_ordenar_archivar ("Edad_menor_mergesort", imprimir_persona_archivo, glist_merge_sort, edad_menor, lista);

  glist_ordenar_archivar ("Largo_nombre_menor_selection", imprimir_persona_archivo, glist_selection_sort, largo_nombre_menor, lista);

  glist_ordenar_archivar ("Largo_nombre_menor_insertion", imprimir_persona_archivo, glist_insertion_sort, largo_nombre_menor, lista);

  glist_ordenar_archivar ("Largo_nombre_menor_mergesort", imprimir_persona_archivo, glist_merge_sort, largo_nombre_menor, lista);



  glist_destruir (&lista,liberar_persona);
}
