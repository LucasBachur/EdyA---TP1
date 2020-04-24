#ifndef __GLIST_H__
#define __GLIST_H__

#define forrapido(lista, iterador) for (GNodo *iterador = lista; iterador != NULL; iterador = iterador->sig)

typedef struct _GNodo {
  void *dato;
  struct _GNodo *sig;
} GNodo;
typedef struct _GList {
  GNodo *inicio;
  GNodo *final;
} GList;

typedef void (*Destruir) (void *dato);
typedef int (*Comparar) (void *dato1, void *dato2);
typedef void (*ImprimeArchivo) (void *dato, FILE *archivo);
typedef GList (*Ordenamiento) (void *GList, Comparar comparacion);

// Crea una glist.
GList glist_crear ();

// Dado un puntero a GList y un dato.
// Crea un nuevo nodo cuyo puntero, apunta al primer nodo de la lista.
// Luego se iguala el comienzo al nuevo nodo
void glist_agregar_inicio (GList *lista, void* dato);

// Dado un puntero a GList, y un dato.
// Crea un nuevo nodo cuyo puntero apunta a NULL, y es el siguiente
// al anterior puntero de la lista.
void glist_agregar_final (GList *lista, void* dato);

void glist_imprimir_archivo (GList *lista, ImprimeArchivo funcion, char *nombreArchivoSalida);

// Devuelve el primer elemento de una lista.
GList first (GList lista);

// Devuelve una lista sin su primer elemento.
void rest (GList lista);

// Devuelve el ultimo elemento de una lista.
GList last (GList lista);

// Dada una lista enlazada, libera la lista y utiliza una funcion Destruir
// personalizada para liberar tipo de dato que se este llevando en ella.
void glist_destruir (GList *lista, Destruir funcion);

// Algoritmo de ordenamiento por insercion, toma una lista y una funcion de comparacion.
// Devuelve la lista ordenada.
GList glist_insertion_sort (GList lista, Comparar funcion);

// Algoritmo de ordenamiento por seleccion, toma una lista y una funcion de comparacion.
// Devuelve la lista ordenada.
GList glist_selection_sort (GList lista, Comparar funcion);

// Algoritmo de ordenamiento por mezcla, toma una lista y una funcion de comparacion.
// Devuelve la lista ordenada.
GList glist_merge_sort (GList lista, Comparar funcion);

// Toma dos listas y las combina de acuerdo a un critero de comparacion.
GList merge (GList left, GList right, Comparar funcion);

#endif