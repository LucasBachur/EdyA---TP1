#include <stdio.h>
#include <stdlib.h>
#include "glist.h"
#include <time.h>


GList glist_crear (){
  GList nueva;
  nueva.inicio = NULL;
  nueva.final = NULL;
  return nueva;
}

void glist_agregar_inicio (GList *lista, void *dato){
  // Creando el nodo.
  GNodo *nuevoNodo = malloc (sizeof (GNodo));
  nuevoNodo->dato = dato;
  nuevoNodo->sig = lista->inicio;
  // Si la lista es vacia se cambia el elemento de final de la GList.
  if (lista->inicio == NULL)
    lista->final = nuevoNodo;
  // Se cambia el elemento de inicio de la GList.
  lista->inicio = nuevoNodo;
}

void glist_agregar_final (GList *lista, void *dato){
  // Creando nodo.
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

void glist_imprimir_archivo (GList *lista, ImprimeArchivo funcion,
 char *nombreArchivoSalida, double tiempo){
  FILE *Archivo = fopen (nombreArchivoSalida, "w");
  if (Archivo != NULL){
    // Si se abrio el archivo correctamente...
    if (tiempo != -1) {
      // Si se le paso un tiempo valido lo imprime.
      fprintf (Archivo, "Tiempo de ordenamiento: |%lf|\n\n", tiempo);
    }
    GNodo *iterador = lista->inicio;
    // Aplicamos la funcion de impresion a cada dato de la lista.
    for (; iterador != NULL; iterador = iterador->sig)
      funcion (iterador->dato, Archivo);
  }else{
    printf ("Archivo de escritura fallo.\n");
  }
  fclose (Archivo);
}

GList glist_copiar_nodos (GList lista){
  GList nuevaLista = glist_crear ();
  GNodo *iterador = lista.inicio;
  for (; iterador != NULL; iterador = iterador->sig)
    glist_agregar_final (&nuevaLista, iterador->dato);
  return nuevaLista;
}

void glist_intercambiar (GNodo *nodo1, GNodo *nodo2){
  void *datoAuxiliar = NULL;
  datoAuxiliar = nodo1->dato;
  nodo1->dato = nodo2->dato;
  nodo2->dato = datoAuxiliar;
}

void glist_mover (GList *lista, GNodo *antNodo1, GNodo *antNodo2){
  // Guardando referencia al nodo relevante.
  GNodo *relevante = antNodo2->sig;
  // Haciendo que la lista "saltee" al nodo relevante, y tambien, notese que
  // cuando se llame a la funcion, antNodo2 sera el nodo anterior al que se
  // compara, por lo tanto, este adelantamiento, sumado a que el relevante
  // se colocara al comienzo de la lista, nos deja ya colocado antComparando
  // en la posicion indicada para la proxima iteracion.
  antNodo2->sig = relevante->sig;
  // El siguiente a relevante, es ahora el indicado.
  relevante->sig = antNodo1->sig;
  // Colocando relevante en la lista.
  antNodo1->sig = relevante;
  // Si relevante era el final de la lista.
  if (antNodo2 ->sig == NULL)
    lista->final = antNodo2;
}

void glist_mover_pos0 (GList *lista, GNodo *nodoInicial, GNodo *antNodo2){
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

void glist_ordenar_archivar (char *nombreArchivoSalida,
 ImprimeArchivo metodo_impresion, Ordenamiento metodo_ordenamiento,
 Compara comparar, GList lista){
  // Genera una copia de la lista a ordenar.
  GList listaAOdenar = glist_copiar_nodos (lista);

  // Se cuenta el tiempo de ejecucion del algoritmo de ordenamiento.
  clock_t begin = clock();
  listaAOdenar = metodo_ordenamiento (listaAOdenar, comparar);
  clock_t end = clock();
  double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

  glist_imprimir_archivo (&listaAOdenar, metodo_impresion, nombreArchivoSalida,
   time_spent);
  // Liberando nodos de la copia.
  glist_liberar_nodos (&listaAOdenar);
}

void merge (GNodo **izq, GNodo **der, Compara comparar){
  GNodo *resultado = NULL;
  GNodo *iterador_izq = *izq;
  GNodo *iterador_der = *der;
  // Primero se necesita decidir cual sera el comienzo de resultado.
  if (comparar (iterador_izq->dato, iterador_der->dato) < 0){
    resultado = iterador_izq;
    iterador_izq = iterador_izq->sig;
  }
  else {
    resultado = iterador_der;
    *izq = *der;
    // Asi, lista izquierda sera el comienzo de la lista mergeada total.
    iterador_der = iterador_der->sig;
  }
  // Agregando los nodos que corresponden a la lista mergeada.
  while (iterador_izq != NULL && iterador_der != NULL){
    if (comparar (iterador_izq->dato, iterador_der->dato) < 0){
      resultado->sig = iterador_izq;
      iterador_izq = iterador_izq->sig;
      resultado = resultado->sig;
    }
    else {
      resultado->sig = iterador_der;
      iterador_der = iterador_der->sig;
      resultado = resultado->sig;
    }
  }
  // Agregando la lista sobrante a la lista mergeada.
  if (iterador_izq != NULL){
    resultado->sig = iterador_izq;
  }
  else {
    resultado->sig = iterador_der;
  }
}

void dividir (GNodo *listaPrincipal, GNodo **izq, GNodo **der){
  GNodo *iteradorLento = listaPrincipal;
  // Asi, si la lista tiene un solo elemento, lo sabremos de inmediato.
  GNodo *iteradorRapido = listaPrincipal->sig;
  // El primer iterador avanzara de a una posicion y el segundo de a dos.
  while (iteradorRapido != NULL){
    iteradorRapido = iteradorRapido->sig;
    if (iteradorRapido != NULL){
      iteradorRapido = iteradorRapido->sig;
      iteradorLento = iteradorLento->sig;
    }
  }
  // Guardando las posiciones de las listas divididas.
  *der = iteradorLento->sig;
  *izq = listaPrincipal;
  // Con esta ultima asignacion la lista queda divida.
  iteradorLento->sig = NULL;
}

GList glist_selection_sort (GList lista, Compara funcion){
  GNodo *iterador1 = lista.inicio;
  GNodo *iterador2 = NULL;
  GNodo *relevante = NULL;
  for (; iterador1->sig != NULL; iterador1 = iterador1->sig){
    relevante = iterador1;
    iterador2 = iterador1->sig;
    // Buscando el minimo elemento (segun la funcion que compara)
    // de la parte de la lista no ordenada.
    for (; iterador2 != NULL; iterador2 = iterador2->sig){
      if (funcion (iterador2->dato, relevante->dato) < 0){
        relevante = iterador2;
      }
    }
    // Intercambiando el minimo elemento con la posicion en la que debe quedar.
    glist_intercambiar (relevante, iterador1);
  }
  return lista;
}

GList glist_insertion_sort (GList lista, Compara funcion){
  GNodo *antComparando = lista.inicio;
  GNodo *iterador2 = NULL;
  // Se comienza desde la segunda posicion porque una lista de 1 elemento
  // ya esta ordenada.
  // Se hace a lo sumo un movimiento por iteracion.
  while (antComparando->sig != NULL){
    iterador2 = lista.inicio;
    // Comparando con el primer elemento.
    if (funcion (antComparando->sig->dato, iterador2->dato) < 0){
      glist_mover_pos0 (&lista, iterador2, antComparando);
    }
    else {
      // Se recorre la lista ordenada comparando cada nodo con
      // el elemento relevante.
      while (iterador2 != antComparando && funcion (antComparando->sig->dato,
       iterador2->sig->dato) >= 0){
        iterador2 = iterador2->sig;
      }
      // Si salio del bucle por esto, entonces la lista parcial esta ordenada.
      if (iterador2 == antComparando){
        // Unico caso en el que el iterador avanza de manera "forzada".
        antComparando = antComparando->sig;
      }
      else {
        glist_mover (&lista, iterador2, antComparando);
      }
    }
  }
  return lista;
}

GNodo* merge_sort (GNodo *comienzo, Compara funcion){
  GNodo *izq = NULL;
  GNodo *der = NULL;
  // Si la lista es vacia o tiene un solo elemento ya esta ordenada y
  // cortamos la recursion.
  if (comienzo != NULL && comienzo->sig != NULL){
    // Dividimos la lista en 2 listas mas chicas.
    dividir (comienzo, &izq, &der);

    // Ordenamos por separado esas 2 listas.
    izq = merge_sort (izq, funcion);
    der = merge_sort (der, funcion);

    // Unimos las 2 listas ordenadas en otra lista tambien ordenada.
    merge (&izq, &der, funcion);
    comienzo = izq;
  }
  return comienzo;
}

void glist_destruir (GList *lista, Destruir funcion){
  GNodo *iterador = lista->inicio;
  GNodo *libertador;

  for (; iterador != NULL; ){
    libertador = iterador;
    iterador = iterador->sig;
    // Libera cada dato de acuerdo al metodo dado.
    funcion (libertador->dato);
    // Libera cada nodo.
    free (libertador);
  }
}

GList glist_merge_sort (GList lista, Compara funcion){
  // Llama al algoritmo de ordenamiento y cambia la GList.
  lista.inicio = merge_sort (lista.inicio, funcion);
  GNodo *iterador = lista.inicio;
  for (; iterador->sig != NULL; iterador = iterador->sig);
  lista.final = iterador;
  return lista;
}

void glist_liberar_nodos (GList *lista){
  GNodo *iterador = lista->inicio;
  GNodo *libertador;

  for (; iterador != NULL; ){
    libertador = iterador;
    iterador = iterador->sig;
    // Libera cada nodo.
    free (libertador);
  }
}
