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



// Dada una lista, devuelve una nueva lista con nuevos nodos identicos.
// Cabe recalcar, que los punteros a los datos siguen siendo los de la lista
// original. Por lo tanto si se ven alterados en una lista o la otra, los
// cambios se veran reflejados en ambas.
GList glist_copiar_nodos (GList lista){
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


void glist_merge (GNodo **izq, GNodo **der, Compara comparar){
  GNodo *resultado = NULL;
  GNodo *iterador_izq = *izq;
  GNodo *iterador_der = *der;
  // Primero se necesita decidir cual sera el comienzo de resultado.
  if (comparar (iterador_izq->dato, iterador_der->dato)){
    printf ("El nodo inicial es el de la izq\n");
    resultado = iterador_izq;
    iterador_izq = iterador_izq->sig;
  }
  else {
    printf ("El nodo inicial es el de la der\n");
    resultado = iterador_der;
    *izq = *der; // De esta forma, lista 1 sera el comienzo de la lista mergeada total.
    iterador_der = iterador_der->sig;
  }

  while (iterador_izq != NULL && iterador_der != NULL){
    if (comparar (iterador_izq->dato, iterador_der->dato)){
      printf ("El nodo siguiente es el de la izq\n");
      resultado->sig = iterador_izq;
      iterador_izq = iterador_izq->sig;
      resultado = resultado->sig;
    }
    else {
      printf ("El nodo siguiente es el de la der\n");
      resultado->sig = iterador_der;
      iterador_der = iterador_der->sig;
      resultado = resultado->sig;
    }
  }

  if (iterador_izq != NULL){
    printf ("Sobraron nodos de la izq\n");
    resultado->sig = iterador_izq;
  }
  else {
    printf ("Sobraron nodos de la der\n");
    resultado->sig = iterador_der;
  }
}

void glist_dividir (GNodo *listaPrincipal, GNodo **izq, GNodo **der){
  GNodo *iteradorLento = listaPrincipal;
  // De esta forma, si la lista tiene un solo elemento, lo sabremos de inmediato
  GNodo *iteradorRapido = listaPrincipal->sig;

  while (iteradorRapido != NULL){
    iteradorRapido = iteradorRapido->sig;
    if (iteradorRapido != NULL){
      iteradorRapido = iteradorRapido->sig;
      iteradorLento = iteradorLento->sig;
    }
  }

  *der = iteradorLento->sig;
  *izq = listaPrincipal;
  iteradorLento->sig = NULL;
}

void glist_ordenar_archivar (char *nombreArchivoSalida, ImprimeArchivo metodo_impresion, Ordenamiento metodo_ordenamiento, Compara comparar, GList lista){
  GList listaAOdenar = glist_copiar_nodos (lista);
  listaAOdenar = metodo_ordenamiento (listaAOdenar, comparar);
  glist_imprimir_archivo (&listaAOdenar, metodo_impresion, nombreArchivoSalida);
  glist_liberar_nodos (&listaAOdenar);
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


void glist_liberar_nodos (GList *lista){
  GNodo *iterador = lista->inicio;
  GNodo *libertador;

  for (; iterador != NULL; ){
    libertador = iterador;
    iterador = iterador->sig;
    free (libertador);
  }
}
