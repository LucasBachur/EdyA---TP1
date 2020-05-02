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
// glist_agregar_inicio: GList* void* ->
void glist_agregar_final (GList *lista, void* dato);

// Toma un puntero a GList, una funcion que indica como imprimir, el nombre del
// archivo de salida y el tiempo que queremos que se imprima en el arhivo 
// junto con la lista.
// glist_imprimir_archivo: GList* ImprimeArchivo char* double ->
void glist_imprimir_archivo (GList *lista, ImprimeArchivo funcion,
 char *nombreArchivoSalida, double tiempo);

// Dada una lista, devuelve una nueva lista con nuevos nodos identicos.
// Cabe recalcar, que los punteros a los datos siguen siendo los de la lista
// original. Por lo tanto si se ven alterados en una u otra lista, los
// cambios se veran reflejados en ambas.
// glist_copiar_nodos: GList -> GList
GList glist_copiar_nodos (GList lista);

// Dados dos nodos cualesquiera, intercambia los datos que contienen.
// glist_intercambiar: GNodo* GNodo* ->
void glist_intercambiar (GNodo *nodo1, GNodo *nodo2);

// Dados un puntero a GList y dos nodos de esta, mueve el siguiente al segundo
// a la posicion posterior al primero (eliminandolo de de su posicion original)
// y cambia la GList si es necesario.
// glist_mover: GList* GNodo* GNodo* ->
void glist_mover (GList *lista, GNodo *antNodo1, GNodo *antNodo2);

// Dados un puntero a GList y dos nodos de esta (siendo el primero el nodo 
// inicial), mueve el segundo al comienzo de la lista (eliminandolo de 
// su posicion original) y cambia la GList.
// glist_mover_pos0: GList* GNodo* GNodo* ->
void glist_mover_pos0 (GList *lista, GNodo *nodoInicial, GNodo *antNodo2);

// La funcion toma el nombre de un archivo, un metodo de impresion, un metodo
// de ordenamiento, una funcion comparacion y una GList.
// Luego ordena la lista segun el metodo provisto de acuerdo a la funcion de 
// comparacion dada y lo imprime en el con el metodo otorgado, agregando
// el tiempo que tardo en realizarse el algoritmo de ordenamiento.
// glist_ordenar_archivar: char* ImprimeArchivo Ordenamiento Compara GList ->
void glist_ordenar_archivar (char *nombreArchivoSalida, 
  ImprimeArchivo metodo_impresion, Ordenamiento metodo_ordenamiento,
  Compara comparar, GList lista);

// Toma dos nodos que representan sublistas, ordenadas, de una lista original,
// la lista original y un metodo para comparar.
// Luego, combina estas listas en una lista ordenada.
// merge: GNodo** GNodo** Compara ->
void merge (GNodo **lista1, GNodo **lista2, Compara comparar);

// Toma el nodo inicial de la lista que se quiere dividir, y dos punteros que
// van a indicar donde van a quedar las listas divididas. Luego, las divide.
// dividir: GNodo* GNodo** GNodo** ->
void dividir (GNodo *listaPrincipal, GNodo **izq, GNodo **der);

// Algoritmo de ordenamiento por seleccion, toma una lista y una funcion de 
// comparacion.
// Devuelve la lista ordenada.
// glist_selection_sort: GList Compara -> GList
GList glist_selection_sort (GList lista, Compara funcion);

// Algoritmo de ordenamiento por insercion, toma una lista y una funcion de 
// comparacion.
// Devuelve la lista ordenada.
// glist_insertion_sort: GList Compara -> GList
GList glist_insertion_sort (GList lista, Compara funcion);

GNodo* merge_sort (GNodo *comienzo, Compara funcion);

// Algoritmo de ordenamiento por mezcla, toma una lista y una funcion de 
// comparacion.
// Devuelve la lista ordenada.
// glist_merge_sort: GList Compara -> GList
GList glist_merge_sort (GList lista, Compara funcion);

// Dada una lista enlazada, libera la lista y utiliza una funcion Destruir
// personalizada para liberar tipo de dato que se este llevando en ella.
// glist_destruir: GList* Destruir ->
void glist_destruir (GList *lista, Destruir funcion);

// Esta funcion toma una GList y libera solo los nodos de la lista, no
// los datos que hay en cada nodo.
// glist_liberar_nodos: GList* ->
void glist_liberar_nodos (GList *lista);


#endif
