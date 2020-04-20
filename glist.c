#include <stdio.h>
#include <stdlib.h>
#include "glist.h"

GList glist_crear (){
  return NULL;
}

void glist_agregar_inicio (GList *lista, void *dato){
  GNodo *nuevoNodo = malloc (sizeof (GNodo));
  nuevoNodo->dato = dato;
  nuevoNodo->sig = lista;
  lista = nuevoNodo;
}

void glist_agregar_final (GList *lista, void *dato){
  // creando Nodo.
  GNodo *nuevoNodo = malloc (sizeof (GNodo));
  nuevoNodo->dato = dato;
  nuevoNodo->sig = NULL;

  if (lista == NULL)
    lista = nuevoNodo;
  else {
    GNodo *iterador = lista;
    // iterando hasta el final de la lista.
    for (; iterador->sig != NULL ; iterador = iterador->sig);
    // haciendo que el ultimo elemento de la lista apunte al nuevo Nodo.
    iterador->sig = nuevoNodo;
  }
}

void glist_destruir (GList lista, Destruir funcion){
  GNodo *iterador = lista;
  GNodo *libertador;

  for (; iterador != NULL ; ){
    libertador = iterador;
    iterador = iterador->sig;
    funcion (libertador);
    free (libertador);
  }
}
