#include <stdio.h>
#include <stdlib.h>
#include "glist.h"


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

GList glist_cpy (GList lista){
  GList nuevaLista = glist_crear ();
  forrapido (lista, iterador){
    glist_agregar_final (&nuevaLista, iterador->dato);
  }
  return nuevaLista;
}

// Funciona intercambiando datos.
void glist_intercambiar (GNodo *nodo1, GNodo *nodo2){
  void *datoAuxiliar = NULL;
  datoAuxiliar = nodo1->dato;
  nodo1->dato = nodo2->dato;
  nodo2->dato = datoAuxiliar;
}

void glist_mover (GList *lista, GNodo *antNodo1, GNodo *antNodo2){
  // Guardando referencia al nodo relevante.
  GNodo *relevante = antNodo2->sig;
  // Haciendo que la lista "saltee" al nodo relevante.
  antNodo2->sig = relevante->sig;
  // El siguiente a relevante, es ahora el indicado.
  relevante->sig = antNodo1->sig;
  // Colocando relevante en la lista.
  antNodo1->sig = relevante;
  // Si relevante era el final de la lista..
  if (antNodo2 ->sig == NULL)
    lista->final = antNodo2;
}

void glist_mover_pos0 (GList *lista, GNodo *antNodo2, GNodo *nodoInicial){
  // Guardando referencia al nodo relevante.
  GNodo *relevante = antNodo2->sig;
  // Haciendo que la lista "saltee" al nodo relevante, y tambien, notese que
  // cuando se llame a la funcion, antNodo2 sera el nodo anterior al que se
  // compara, por lo tanto, este adelantamiento, sumado a que el relevante
  // se colocara al comienzo de la lista, nos deja ya colocado antComparando
  // en la posicion indicada para la proxima iteracion.
  antNodo2->sig = relevante->sig;
  // Estableciendo relevante como el nuevo comienzo de la lista.
  relevante->sig = nodoInicial;
  lista->inicio = relevante;
  // Si relevante era el final de la lista..
  if (antNodo2->sig == NULL)
    lista->final = antNodo2;
}

void glist_ordenar_archivar (char *nombreArchivoSalida, ImprimeArchivo metodo_impresion, Ordenamiento metodo_ordenamiento, Compara comparar, GList lista){
  GList listaAOdenar = glist_cpy (lista);
  listaAOdenar = metodo_ordenamiento (listaAOdenar, comparar);
  glist_imprimir_archivo (&listaAOdenar, metodo_impresion, nombreArchivoSalida);
  glist_destruir (&listaAOdenar, nada);
}

GList glist_selection_sort (GList lista, Compara funcion){
  GNodo *iterador1 = lista.inicio;
  GNodo *iterador2 = NULL;
  GNodo *relevante = NULL;
  for (; iterador1->sig != NULL; iterador1 = iterador1->sig){
    relevante = iterador1;
    iterador2 = iterador1->sig;
    for (; iterador2 != NULL; iterador2 = iterador2->sig){
      if (funcion (iterador2->dato, relevante->dato)){
        relevante = iterador2;
      }
    }
    glist_intercambiar (relevante, iterador1);
  }
  return lista;
}

GList glist_insertion_sort (GList lista, Compara funcion){
  // Se comienza desde el segundo puesto que una lista de 1 elmeento esta ordenada.
  GNodo *antComparando = lista.inicio;
  GNodo *iterador2 = NULL;

  while (antComparando->sig != NULL){
    iterador2 = lista.inicio;
    if (funcion (antComparando->sig->dato, iterador2->dato)){
      glist_mover_pos0 (&lista, antComparando, iterador2);
    }
    else {
      while (iterador2 != antComparando && !funcion (antComparando->sig->dato, iterador2->sig->dato)){
        iterador2 = iterador2->sig;
      } // Si salio del bucle por esto, entonces la lista parcial esta ordenada.
      if (iterador2 == antComparando){
        antComparando = antComparando->sig;
      }
      else {
        glist_mover (&lista, iterador2, antComparando);
      }
    }
  }
  return lista;
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

void nada (void *dato){
  dato = dato + 1;
  dato = dato - 1;
}
