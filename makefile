# -*- MakeFile -*-

programa1: generacion.o generar.o
	gcc -o programa1.out generar.o generacion.o

programa2: listas.o glist.o 
	gcc -o programa2.out listas.o glist.o

generar.o: generar.c
	gcc -Wall -Werror -Wextra -g -c generar.c

generacion.o: generacion.c generacion.h
	gcc -Wall -Werror -Wextra -g -c generacion.c


listas.o: listas.c
	gcc -Wall -Werror -Wextra -g -c listas.c

glist.o: glist.c glist.h
	gcc -Wall -Werror -Wextra -g -c glist.c
	
