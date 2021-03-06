#include <stdlib.h>
#include <stdio.h>
#include "structs.h"

#ifndef LIBARBOL_H
#define LIBARBOL_H

///------------------------------------------------------------------------------------------------------------------------------Iniciar arbol
nodoArbol* inicArbol();

///---------------------------------------------------------------------------------------------------------------------------------Crear nodo
nodoArbol* crearNodo(stPelicula p);

///------------------------------------------------------------------------------------------------------------------------------Insertar nodo
nodoArbol* insertar(nodoArbol* arbol, nodoArbol* nuevo_nodo);

///--------------------------------------------------------------------------------------------------------------------------Mostrar pre-order
void preorder(nodoArbol* arbol, stPelicula peliDisFiltro, int filtrosAplicados[], int filtroActivado);

///---------------------------------------------------------------------------------------------------------------------------Mostrar in-order
void inorder(nodoArbol* arbol, stPelicula peliDisFiltro, int filtrosAplicados[], int filtroActivado);

///-------------------------------------------------------------------------------------------------------------------------Mostrar post-order
void postorder(nodoArbol* arbol, stPelicula peliDisFiltro, int filtrosAplicados[], int filtroActivado);

///--------------------------------------------------------------------------------------------------------------------------------Buscar nodo
nodoArbol* buscar(nodoArbol* arbol, int id);

///-------------------------------------------------------------------------------------------------------------------------------Mostrar nodo
void mostrarNodo(nodoArbol* nodo, stUsuario user);

///--------------------------------------------------------------------------------------------------------------------------------Borrar nodo
nodoArbol* borrarNodo(nodoArbol* arbol, int id);

///---------------------------------------------------------------------------------------------------------------------------Nodo mas derecho
nodoArbol* nmd(nodoArbol* arbol);

///-------------------------------------------------------------------------------------------------------------------------Nodo mas izquierdo
nodoArbol* nmi(nodoArbol* arbol);

///----------------------------------------------------------------------------------------------------------------------------Cantidad Nodos
int cantidadNodosArbol(nodoArbol* arbol);

///------------------------------------------------------------------------------------------------------------------------------Buscar por nombre
nodoArbol * buscarEnpreorderNombre(nodoArbol * arbol, char nombre[]);

///------------------------------------------------------------------------------------------------------------------------------Buscar por genero
nodoArbol* buscarEnpreorderGenero(nodoArbol * arbol, char genero[]);

#endif // LIBARBOL_H
