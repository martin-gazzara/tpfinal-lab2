#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"

nodoListaPelicula* inicLista();
nodoListaPelicula* crearNodoLista(stPelicula pelicula);
nodoListaPelicula* agregarAlPrincipio(nodoListaPelicula *lista,nodoListaPelicula *nuevoNodo);
nodoListaPelicula* buscarUltimo(nodoListaPelicula *lista);
nodoListaPelicula* agregarAlFinal(nodoListaPelicula *lista,nodoListaPelicula *nuevoNodo);
nodoListaPelicula* agregarEnOrdenPorNombreDePelicula(nodoListaPelicula *lista,nodoListaPelicula *nuevoNodo);
nodoListaPelicula* buscarNodoPorNombre(nodoListaPelicula *lista, char nombre[]);
nodoListaPelicula* buscarNodoPorId(nodoListaPelicula *lista,int id);
void mostrarNodoLista(stPelicula pelicula);
void recorrerYmostrar(nodoListaPelicula *lista);
nodoListaPelicula* borrarNodoPorIdPelicula(nodoListaPelicula *lista,int dato);

