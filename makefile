# -*- MakeFile -*-

programa1: generacion.o generar.o
	gcc -o programa1.out generar.o generacion.o

programa2: listas.o glist.o 
	gcc -o programa2.out listas.o glist.o

generar.o: Generacion/generar.c
	gcc -Wall -Werror -Wextra -g -c Generacion/generar.c

generacion.o: Generacion/generacion.c Generacion/generacion.h
	gcc -Wall -Werror -Wextra -g -c Generacion/generacion.c

listas.o: Listas/listas.c
	gcc -Wall -Werror -Wextra -g -c Listas/listas.c

glist.o: Listas/glist.c Listas/glist.h
	gcc -Wall -Werror -Wextra -g -c Listas/glist.c
	
