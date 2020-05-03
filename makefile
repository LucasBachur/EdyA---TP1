# Archivo para la compilacion del programa, se debe ingresar en la consola en cualquier orden:
# make programa1
# make programa2
# Y se compilaran en cada caso los programas indicados.
# Tambien incluimos la instruccion programas que compilara ambos programas en un solo comando.

flags = -Wall -Werror -Wextra -g
objetosLista = listas.o glist.o persona.o
objetosGen = generacion.o generar.o
listas = Listas/listas.c
persona = Listas/Persona/persona
glist = Listas/glist
generacion = Generacion/generacion
generar = Generacion/generar

programas: $(objetosGen) $(objetosLista)
	gcc -o programa1.out $(objetosGen)
	gcc -o programa2.out $(objetosLista)


programa1: $(objetosGen)
	gcc -o programa1.out $(objetosGen)

generar.o: $(generar).c
	gcc $(flags) -c $(generar).c

generacion.o: $(generacion).c $(generacion).h
	gcc $(flags) -c $(generacion).c


programa2: $(objetosLista)
	gcc -o programa2.out $(objetosLista)

listas.o: $(listas)
	gcc $(flags) -c $(listas)

persona.o: $(persona).c $(persona).h
	gcc $(flags) -c $(persona).c

glist.o: $(glist).c $(glist).h
	gcc $(flags) -c $(glist).c

clean:
	rm -rf *.out *.o *txt
