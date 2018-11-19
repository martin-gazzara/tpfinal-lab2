#include "grafica.h"
#include "libarbol.h"
#include "structs.h"



#ifndef PELICULAS_H
#define PELICULAS_H

//Calcula la cantidad de Registros que tiene un Archivo.
int cantidadRegistros(FILE* arch, size_t tamanioDeTipo);

 //Habilita nuevamente una Pel�cula eliminada.
void habilitarPelicula(nodoArbol* arbol, char DB_peliculas[]);

 //Da de baja una pel�cula
void bajaPelicula(char DB_peliculas[], nodoArbol* arbol);

 //Ingresa una Pel�cula.
void ingresarPeliculas(char DB_peliculas[], nodoArbol** arbol);


#endif // PELICULAS_H
