#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "persona.h"


Persona* crear_persona (char *nombre, int edad, char *pais){
  Persona *nuevaPersona = malloc (sizeof (Persona));
  nuevaPersona->nombre = malloc (sizeof (char) * 80);
  nuevaPersona->lugarDeNacimiento =  malloc (sizeof (char) * 80);

  strcpy (nuevaPersona->nombre, nombre);
  nuevaPersona->edad = edad;
  strcpy (nuevaPersona->lugarDeNacimiento, pais);

  return nuevaPersona;
}

int edad_menor (void *dato1, void *dato2){
  int edad1 = ((Persona*)dato1)->edad;
  int edad2 = ((Persona*)dato2)->edad;

  return edad1 - edad2;
}

int largo_nombre_menor (void *dato1, void *dato2){
  int largo1 = strlen (((Persona*)dato1)->nombre);
  int largo2 = strlen (((Persona*)dato2)->nombre);

  return largo1 - largo2;
}

void imprimir_persona_archivo (void *dato, FILE *Archivo){
  fprintf (Archivo, "%s, %d, %s\n", ((Persona*)dato)->nombre,
   ((Persona*)dato)->edad, ((Persona*)dato)->lugarDeNacimiento);
}

void liberar_persona (void *persona){
  free (((Persona*)persona)->nombre);
  free (((Persona*)persona)->lugarDeNacimiento);
  free (persona);
}
