# -*- MakeFile -*-

programa1: generacion.o generar.c
	gcc -o programa1 generar.c generacion.o

generacion.o: generacion.c generacion.h
	gcc -Wall -Werror -Wextra -g -c generacion.c




glist.o: glist.c glist.h
	gcc -Wall -Werror -Wextra -g -c glist.c
	
