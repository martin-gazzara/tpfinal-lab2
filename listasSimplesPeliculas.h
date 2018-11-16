#ifndef LISTASSIMPLESPELICULAS_H_INCLUDED
#define LISTASSIMPLESPELICULAS_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

nodoListaPelicula *inicLista();
nodoListaPelicula *crearNodoLista(stPelicula pelicula);
nodoListaPelicula *agregarAlPrincipio(nodoListaPelicula *lista,nodoListaPelicula *nuevoNodo);
nodoListaPelicula *buscarUltimo(nodoListaPelicula *lista);
nodoListaPelicula *agregarAlFinal(nodoListaPelicula *lista,nodoListaPelicula *nuevoNodo);
nodoListaPelicula *agregarEnOrdenPorNombreDePelicula(nodoListaPelicula *lista,nodoListaPelicula *nuevoNodo);
nodoListaPelicula *buscarNodoPorNombre(nodoListaPelicula *lista, char nombre[]);
nodoListaPelicula *buscarNodoPorId(nodoListaPelicula *lista,int id);
void mostrarNodo(stPelicula pelicula);
void recorrerYmostrar(nodoListaPelicula *lista);
nodoListaPelicula *borrarNodoPorIdPelicula(nodoListaPelicula *lista,int dato);

#endif // LISTASSIMPLESPELICULAS_H_INCLUDED
