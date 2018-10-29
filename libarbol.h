#include <stdlib.h>
#include "structs.h"



///------------------------------------------------------------------------------------------------------------------------------Iniciar arbol
nodoArbol* inicArbol();

///---------------------------------------------------------------------------------------------------------------------------------Crear nodo
nodoArbol* crearNodo(stPelicula p);

///------------------------------------------------------------------------------------------------------------------------------Insertar nodo
nodoArbol* insertar(nodoArbol* arbol, nodoArbol* nuevo_nodo);

///--------------------------------------------------------------------------------------------------------------------------Mostrar pre-order
void preorder(nodoArbol* arbol);

///---------------------------------------------------------------------------------------------------------------------------Mostrar in-order
void inorder(nodoArbol* arbol);

///-------------------------------------------------------------------------------------------------------------------------Mostrar post-order
void postorder(nodoArbol* arbol);

///--------------------------------------------------------------------------------------------------------------------------------Buscar nodo
nodoArbol* buscar(nodoArbol* arbol, int id);

///-------------------------------------------------------------------------------------------------------------------------------Mostrar nodo
void mostrarNodo(nodoArbol* nodo);

///--------------------------------------------------------------------------------------------------------------------------------Borrar nodo
nodoArbol* borrarNodo(nodoArbol* arbol, int id);

///---------------------------------------------------------------------------------------------------------------------------Nodo mas derecho
nodoArbol* nmd(nodoArbol* arbol);

///-------------------------------------------------------------------------------------------------------------------------Nodo mas izquierdo
nodoArbol* nmi(nodoArbol* arbol);
