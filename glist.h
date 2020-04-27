#ifndef __GLIST_H__
#define __GLIST_H__

#define forrapido(lista, iterador) for (GNodo *iterador = lista.inicio; iterador != NULL; iterador = iterador->sig)


typedef struct _GNodo {
  void *dato;
  struct _GNodo *sig;
} GNodo;
typedef struct _GList {
  GNodo *inicio;
  GNodo *final;
} GList;


typedef void (*Destruir) (void *dato);
typedef int (*Compara) (void *dato1, void *dato2);
typedef void (*ImprimeArchivo) (void *dato, FILE *archivo);
typedef GList (*Ordenamiento) (GList lista, Compara comparacion);

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

// Dada una lista, devuelve una nueva lista con nuevos nodos identicos.
// Cabe recalcar, que los punteros a los datos siguen siendo los de la lista
// original. Por lo tanto si se ven alterados en una lista o la otra, los
// cambios se veran reflejados en ambas.
GList glist_copiar_nodos (GList lista);

void glist_intercambiar (GNodo *nodo1, GNodo *nodo2);

void glist_mover (GList *lista, GNodo *antNodo1, GNodo *antNodo2);

void glist_mover_pos0 (GList *lista, GNodo *antNodo2, GNodo *nodoInicial);

void glist_ordenar_archivar (char *nombreArchivoSalida, ImprimeArchivo metodo_impresion, Ordenamiento metodo_ordenamiento,
  Compara comparar, GList lista);

// Dadas dos nodos que representan sublistas, ordenadas, de una lista original,
// la lista original y un metodo para comparar.
// Modifica si es necesario el inicio y/o fin de la lista original.
void glist_merge (GNodo **lista1, GNodo **lista2, Compara comparar);

void glist_dividir (GNodo *listaPrincipal, GNodo **izq, GNodo **der);

// Algoritmo de ordenamiento por insercion, toma una lista y una funcion de comparacion.
// Devuelve la lista ordenada.
GList glist_insertion_sort (GList lista, Compara funcion);

// Algoritmo de ordenamiento por seleccion, toma una lista y una funcion de comparacion.
// Devuelve la lista ordenada.
GList glist_selection_sort (GList lista, Compara funcion);

// Algoritmo de ordenamiento por mezcla, toma una lista y una funcion de comparacion.
// Devuelve la lista ordenada.
GList glist_merge_sort (GList lista, Compara funcion);

// Toma dos listas y las combina de acuerdo a un critero de comparacion.
GList merge (GList left, GList right, Compara funcion);

// Dada una lista enlazada, libera la lista y utiliza una funcion Destruir
// personalizada para liberar tipo de dato que se este llevando en ella.
void glist_destruir (GList *lista, Destruir funcion);

// Esta funcion solo libera los nodos de la lista, no libera los datos que hay
// en cada nodo.
void glist_liberar_nodos (GList *lista);


#endif
