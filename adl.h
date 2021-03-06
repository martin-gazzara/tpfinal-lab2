#include <stdlib.h>
#include <stdio.h>
#include "listasSimplesPeliculas.h"
#include "structs.h"


#ifndef ADL_H
#define ADL_H


//Devuelve cant de usuarios activos
int usuariosActivos(char DB_usuarios[]);

//Crea el arreglo de listas (USAR AL PRINCIPIO DEL PROGRAMA)
 stCelda* pasarDeArchivoToADL(char DB_usuarios[],char DB_peliculasVistas[], int cantActivos, nodoArbol* arbol);

//Agrega las peliculas vista al adl (USAR CUANDO SE VE UNA PELICULA)
void agregarPeliVista(int id, stPelicula p, int val, stCelda adl[]);

//Agregar usuario al adl (USAR EN ALTA)
int agregarUsuario(stCelda* adl, int val, stUsuario user);

 //Borrar logicamente el elemento del adl en base al id (USAR EN BAJA USUARIOS)
 void borrarUsuarioADL(stCelda adl[], int val ,int id);

 //Borrar peli de historial (USAR EN BAJA PELIS VISTAS)
void borrarPeliVistaADL(stCelda adl[], int val, int idPeli, int idUsuario);

 //Persiste los datos de las peliculas vistas (BACKUP PELIS VISTAS)
void actualizarPeliculasVistas(stCelda adl[], int val, char DB_peliculasVistas[]);

//Persiste los datos de los usuarios (BACKUP USUARIOS)
void actualizarUsuarios(stCelda adl[], int val, char DB_usuarios[]);

#endif // ADL_H
