# Archivo para la compilacion del programa, se debe ingresar en la consola en cualquier orden:
# make programa1
# make programa2
# Y se compilaran en cada caso los programas indicados.
# Tambien incluimos la instruccion programas que compilara ambos programas en un solo comando.

programas: generacion.o generar.o listas.o glist.o persona.o
	gcc -o programa1.out generar.o generacion.o
	gcc -o programa2.out listas.o glist.o persona.o

programa1: generacion.o generar.o
	gcc -o programa1.out generar.o generacion.o

programa2: listas.o glist.o persona.o
	gcc -o programa2.out listas.o glist.o persona.o

generar.o: Generacion/generar.c
	gcc -Wall -Werror -Wextra -g -c Generacion/generar.c

generacion.o: Generacion/generacion.c Generacion/generacion.h
	gcc -Wall -Werror -Wextra -g -c Generacion/generacion.c

listas.o: Listas/listas.c
	gcc -Wall -Werror -Wextra -g -c Listas/listas.c

persona.o: Listas/Persona/persona.c Listas/Persona/persona.h
	gcc -Wall -Werror -Wextra -g -c Listas/Persona/persona.c

glist.o: Listas/glist.c Listas/glist.h
	gcc -Wall -Werror -Wextra -g -c Listas/glist.c

clean:
	rm -rf *.out *.o
