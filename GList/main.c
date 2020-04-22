#include <stdio.h>
#include <stdlib.h>
#include "glist.h"

void liberar(void *numero){
    free(numero);
}

int main (){
    GList prueba = glist_crear();
    int array[20] = {1,2,3,4,5,6,7,8,9,10};
    for(int i=0;i<10;++i)
        glist_agregar_final (&prueba, (array+i));
    printf("%d %d",*(int*)(first(prueba).inicio->dato),*(int*)(last(prueba).inicio->dato));
    glist_destruir(&prueba,liberar);
}