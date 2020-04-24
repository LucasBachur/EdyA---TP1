#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "glist.h"

#define BUFFER 180

typedef struct {
char *nombre;
int edad;
char *lugarDeNacimiento; // pais o capital
} Persona;




// Adaptar a nuestro caso particular.
void liberar_persona (void *persona){
  free (((Persona*)persona)->nombre);
  free (((Persona*)persona)->lugarDeNacimiento);
  free (persona);
}

void imprimir_persona_archivo (void *dato, FILE *Archivo){
  fprintf (Archivo, "%s, %d, %s\n", ((Persona*)dato)->nombre, ((Persona*)dato)->edad, ((Persona*)dato)->lugarDeNacimiento);
  printf ("%s, %d, %s\n", ((Persona*)dato)->nombre, ((Persona*)dato)->edad, ((Persona*)dato)->lugarDeNacimiento);
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

  char *nombreArchivoEntrada = "/home/scalbi/Programacion/Estructuras de datos y algoritmos/Trabajo/EdyA---TP1-master/EdyA---TP1/Generacion/salidas1.txt";
  char *nombreArchivoSalida = "prueba.txt";

  prueba = interpretar_archivo (nombreArchivoEntrada);
  printf ("Luego de interpretar archivo.\n");
  glist_imprimir_archivo (&prueba, imprimir_persona_archivo, nombreArchivoSalida);


  // printf("%d %d",*(int*)(first(prueba).inicio->dato),*(int*)(last(prueba).inicio->dato));
  glist_destruir(&prueba,liberar_persona);
}