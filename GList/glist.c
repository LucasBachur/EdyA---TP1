#include <stdio.h>
#include <stdlib.h>
#include "glist.h"

typedef struct {
char *nombre;
int edad;
char *lugarDeNacimiento; // pais o capital
} Persona;


GList glist_crear (){
  GList nueva;
  nueva.inicio = NULL;
  nueva.final = NULL;
  return nueva;
}

void glist_agregar_inicio (GList *lista, void *dato){
  GNodo *nuevoNodo = malloc (sizeof (GNodo));
  nuevoNodo->dato = dato;
  nuevoNodo->sig = lista->inicio;
  if (lista->inicio == NULL)
    lista->final = nuevoNodo;
  lista->inicio = nuevoNodo;
}

void glist_agregar_final (GList *lista, void *dato){
  // creando Nodo.
  GNodo *nuevoNodo = malloc (sizeof (GNodo));
  nuevoNodo->dato = dato;
  nuevoNodo->sig = NULL;

  if (lista->inicio == NULL){
    lista->final = nuevoNodo;
    lista->inicio = nuevoNodo;
  }
  else {
    lista->final->sig = nuevoNodo;
    lista->final = nuevoNodo;
  }
}

void glist_imprimir_archivo (GList *lista, ImprimeArchivo funcion, char *nombreArchivoSalida){
  FILE *Archivo = fopen (nombreArchivoSalida, "w");
  printf ("\nComienzo de funcion ImprimirArchivo\n");
  if (Archivo != NULL){
    GNodo *iterador = lista->inicio;

    while (iterador != NULL){
      funcion (iterador->dato, Archivo);
      iterador = iterador->sig;
    }
  }else{
    printf ("Archivo de escritura fallo.\n");
  }
  fclose (Archivo);
}

GList first (GList lista){
  GList nuevo = glist_crear();
  glist_agregar_inicio (&nuevo, lista.inicio->dato);
  return nuevo;
}

void rest (GList lista){
  GNodo *aux = lista.inicio;
  lista.inicio = lista.inicio->sig;
  free(aux);
}

GList last (GList lista){
  GList nuevo = glist_crear();
  glist_agregar_inicio (&nuevo, lista.final->dato);
  return nuevo;
}

void glist_destruir (GList *lista, Destruir funcion){
  GNodo *iterador = lista->inicio;
  GNodo *libertador;

  for (; iterador != NULL; ){
    libertador = iterador;
    iterador = iterador->sig;
    funcion (libertador->dato);
    free (libertador);
  }
}
