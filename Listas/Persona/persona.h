#ifndef __PERSONA_H__
#define __PERSONA_H__

typedef struct {
char *nombre;
int edad;
char *lugarDeNacimiento; // pais o capital
} Persona;

// Dado un nombre, una edad, y un pais. Devuelve un puntero a Persona que tiene
// un solo elemento y sus datos son los que se pasaron a la funcion.
// crear_persona: char* int char* -> Persona*
Persona* crear_persona (char *nombre, int edad, char *pais);

// Dados dos punteros a void,
// los interpreta como personas y compara sus atributos 'edad'.
// edad_menor: void* void* -> int
int edad_menor (void *dato1, void *dato2);


// Dados dos punteros a void,
// los interpreta como personas y compara el largo de sus nombres.
// largo_nombre_menor: void* void* -> int
int largo_nombre_menor (void *dato1, void *dato2);


// Dado un dato como puntero a void, y un archivo abierto en modo de escritura,
// escribe el dato interpretandolo como persona.
// imprimir_persona_archivo: void* FILE* ->
void imprimir_persona_archivo (void *dato, FILE *Archivo);

// Dado un puntero a void, lo interpreta
// como persona, y libera los atributos 'nombre' y 'lugarDeNacimiento'.
// liberar_persona: void* ->
void liberar_persona (void *persona);

#endif
