#ifndef __GLIST_H__
#define __GLIST_H__

#define forrapido(lista, iterador) for (GNodo *iterador = lista.inicio; iterador != NULL; iterador = iterador->sig)


// La estructura GNodo representa un nodo de una lista enlazada.
// Su primer elemento es un puntero al dato que esta almacenando y
// el segundo es un puntero al nodo que le sigue en la lista.

typedef struct _GNodo {
  void *dato;
  struct _GNodo *sig;
} GNodo;

// La estructura GList representa una lista enlazada.
// Su primer elemento es un puntero al primer nodo de la lista y
// el segundo es un puntero al ultimo nodo de la lista.

typedef struct _GList {
  GNodo *inicio;
  GNodo *final;
} GList;


typedef void (*Destruir) (void *dato);
typedef int (*Compara) (void *dato1, void *dato2);
typedef void (*ImprimeArchivo) (void *dato, FILE *archivo);
typedef GList (*Ordenamiento) (GList lista, Compara comparacion);

// glist_crear devuelve una nueva estructura del tipo GList vacia.
// glist_crear: -> GList
GList glist_crear ();

// Toma un puntero a GList y un dato.
// Crea un nuevo nodo que contiene el dato argumento y lo agrega
// al comienzo de la lista.
// glist_agregar_inicio: GList* void* ->
void glist_agregar_inicio (GList *lista, void* dato);

// Toma un puntero a GList y un dato.
// Crea un nuevo nodo que contiene el dato argumento y lo agrega
// al final de la lista.
void glist_agregar_final (GList *lista, void* dato);

void glist_imprimir_archivo (GList *lista, ImprimeArchivo funcion, char *nombreArchivoSalida, double tiempo);

// Dada una lista, devuelve una nueva lista con nuevos nodos identicos.
// Cabe recalcar, que los punteros a los datos siguen siendo los de la lista
// original. Por lo tanto si se ven alterados en una lista o la otra, los
// cambios se veran reflejados en ambas.
GList glist_copiar_nodos (GList lista);

// Funciona intercambiando datos.
void glist_intercambiar (GNodo *nodo1, GNodo *nodo2);

void glist_mover (GList *lista, GNodo *antNodo1, GNodo *antNodo2);

void glist_mover_pos0 (GList *lista, GNodo *antNodo2, GNodo *nodoInicial);

void glist_ordenar_archivar (char *nombreArchivoSalida, ImprimeArchivo metodo_impresion, Ordenamiento metodo_ordenamiento,
  Compara comparar, GList lista);

// Dadas dos nodos que representan sublistas, ordenadas, de una lista original,
// la lista original y un metodo para comparar.
// Modifica si es necesario el inicio y/o fin de la lista original.
void merge (GNodo **lista1, GNodo **lista2, Compara comparar);

void dividir (GNodo *listaPrincipal, GNodo **izq, GNodo **der);

// Algoritmo de ordenamiento por seleccion, toma una lista y una funcion de comparacion.
// Devuelve la lista ordenada.
GList glist_selection_sort (GList lista, Compara funcion);

// Algoritmo de ordenamiento por insercion, toma una lista y una funcion de comparacion.
// Devuelve la lista ordenada.
GList glist_insertion_sort (GList lista, Compara funcion);

GNodo* merge_sort (GNodo *comienzo, Compara funcion);

// Algoritmo de ordenamiento por mezcla, toma una lista y una funcion de comparacion.
// Devuelve la lista ordenada.
GList glist_merge_sort (GList lista, Compara funcion);

// Dada una lista enlazada, libera la lista y utiliza una funcion Destruir
// personalizada para liberar tipo de dato que se este llevando en ella.
void glist_destruir (GList *lista, Destruir funcion);

// Esta funcion solo libera los nodos de la lista, no libera los datos que hay
// en cada nodo.
void glist_liberar_nodos (GList *lista);


#endif
