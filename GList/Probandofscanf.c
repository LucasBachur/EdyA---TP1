#include <stdio.h>
#include <stdlib.h>

#define BUFFER 80

int main (){
  char str1[BUFFER], str2[BUFFER];
  printf ("hola");
  FILE *fp1 = fopen ("/home/scalbi/Programacion/Estructuras de datos y algoritmos/Trabajo/EdyA---TP1-master/EdyA---TP1/Generacion/salidas1.txt", "r");
  // fprintf (fp1,"MARIA VIRGINIA CALDERON, 25, Damasco\nMARCOS DAVID BLANCO, 83, Uzbekistán\n");
  // rewind (fp1);
  printf ("hola");
  if (fp1 != NULL){
    printf ("hola");
    fscanf (fp1, "%[^\n]\n", str1);
    fscanf (fp1, "%[^\n]\n", str2);
    printf ("%s", str1);
    printf ("%s", str2);
  }else{
    printf ("no se abrio");
  }
  fclose (fp1);
  return 0;

}
