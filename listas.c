#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "glist.h"

#define BUFFER 180

typedef struct {
char *nombre;
int edad;
char *lugarDeNacimiento; // pais o capital
} Persona;

// Dado un puntero a void.
// Lo interpreta como persona, y libera los atributos 'nombre' y 'lugarDeNacimiento'
void liberar_persona (void *persona){
  free (((Persona*)persona)->nombre);
  free (((Persona*)persona)->lugarDeNacimiento);
  free (persona);
}

// Dados dos punteros a void.
// Los interpreta como personas y compara sus atributos 'edad'.
int edad_menor (void *dato1, void *dato2){
  int edad1 = ((Persona*)dato1)->edad;
  int edad2 = ((Persona*)dato2)->edad;

  return edad1 <= edad2;
}
// Dados dos punteros a void.
// Los interpreta como personas y compara sus atributos 'edad'.
int edad_mayor (void *dato1, void *dato2){
  int edad1 = ((Persona*)dato1)->edad;
  int edad2 = ((Persona*)dato2)->edad;
  return edad1 >= edad2;
}

// Dado un dato como puntero a void, y un archivo abirto en modo de escritura.
// Escribe el dato interpretandolo como persona.
void imprimir_persona_archivo (void *dato, FILE *Archivo){
  fprintf (Archivo, "%s, %d, %s\n", ((Persona*)dato)->nombre, ((Persona*)dato)->edad, ((Persona*)dato)->lugarDeNacimiento);
}

// Dado un nombre, una edad, y un pais. Devuelve un puntero a Persona que tiene
// un solo elemento y sus datos son los que se pasaron a la funcion.
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
    if (feof(Archivo)){
      printf ("Se leyo correctamente el archivo.\n");
    }
  }else{
    printf ("Archivo para generar lista fallo.\n");
  }
  fclose (Archivo);
  printf ("Archivo cerrado, lista creada.\n");
  return listaInterpretada;
}





int main (){
  GList prueba = glist_crear ();

  char *nombreArchivoEntrada = "salidas1.txt";
  // char *nombreArchivoSalida1 = "AAinsercion.txt";
  // char *nombreArchivoSalida2 = "AAselection.txt";
  char *nombreArchivoSalida3 = "AAmergesort.txt";

  prueba = interpretar_archivo (nombreArchivoEntrada);
  printf ("Luego de interpretar archivo.\n");

  clock_t begin = clock();
  glist_ordenar_archivar (nombreArchivoSalida3, imprimir_persona_archivo, glist_merge_sort, edad_menor, prueba);
  clock_t end = clock();
  double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  printf ("Merge: |%lf|\n", time_spent);


  // begin = clock();
  // glist_ordenar_archivar (nombreArchivoSalida1, imprimir_persona_archivo, glist_insertion_sort, edad_menor, prueba);
  // end = clock();
  // time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  // printf ("Insertion: |%lf|\n", time_spent);



  // begin = clock();
  // glist_ordenar_archivar (nombreArchivoSalida2, imprimir_persona_archivo, glist_selection_sort, edad_menor, prueba);
  // end = clock();
  // time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  // printf ("Selection: |%lf|\n", time_spent);




  // printf("%d %d",*(int*)(first(prueba).inicio->dato),*(int*)(last(prueba).inicio->dato));
  glist_destruir (&prueba,liberar_persona);
}

/*
FALTA:
  1) Comentar codigo.
  2) Errores de valgrind de generacion.
  3) Informe.
  4) Revisar algoritmos.
  5) Probar en la compu de bachur.
  6) Convenciones de codigo.
  7) Archivo de persona?
  8) Hacer carpetas para embellecer.

*/
