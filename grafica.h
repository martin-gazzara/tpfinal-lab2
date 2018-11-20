#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <ctype.h>
#include "gotoxy.h"
#include "structs.h"



#ifndef GRAFICA_H
#define GRAFICA_H



#define t2 50

///__________________________________________///
// Linea doble

///  El espacio de toda la vida
#define espacio 32

///     ╔
#define d_esq_si 201
///     ╗
#define d_esq_sd 187
///     ╚
#define d_esq_ii 200
///     ╝
#define d_esq_id 188
///     ═
#define d_linea_h 205
///     ║
#define d_linea_v 186

//   Linea simple


///     ┌
#define s_esq_si 218
///     ┐
#define s_esq_sd 191
///     └
#define s_esq_ii 192
///     ┘
#define s_esq_id 217
///     ─
#define s_linea_h 196
///     │
#define s_linea_v 179

///_____________________________________________///

/**
 * @brief Muestra intro del programa.
*/
void intro();

void reiniciarColores(int colores[],int num);
void mostrarOpcionesV(char opciones[][21],int colores[],int num);
int elegirOpcionV(char formato[],char opc[][21],int num);
void mostrarOpcionesH(char opciones[][21],int colores[],int num);
int elegirOpcionH(char formato[],char opc[][21],int num);
void pausa();
void siguiente();
void mostrarBienvenida();
int menuPrincipal();
void mostrarCrearUsuario();
void mostrarIniciarSesion();
void insertarTexto(char formato[],char texto[]);
void generarRecuadro(stPelicula peli);
void mostrarRecomendadas(stPelicula recom[]);
int mostrarMenuUsuario(char nombreUsuario[],stPelicula recom[]);
int mostrarElegirPelicula();
void mostrarIngresarID();
void mostrarIngresarNombre();
int mostrarVerPelicula();
int mostrarMenuHistorial();
int mostrarEditarPerfil(char nombreUser[],int id);
int mostrarMenuAdmin();
int mostrarGestionUsuarios();
int mostrarBackUp();
int mostrarGestionPeliculas();
int mostrarMenuListadoDisp();
int mostrarMenuListadoU();
int mostrarMenuListadoP();
int mostrarMenuFiltroDisp();
int mostrarMenuFiltro();
int mostrarDarAltaPeliculas();
int mostrarDarAltaUsuarios();
int mostrarModificarUsuario();
void cerrarPrograma();
void mensaje_passIncorrecto();
void mostrarBajaUsuario(char nombre[]);
void mostrarBajaPelicula(char nombre[]);
void mostrarAltaUsuario(char nombre[]);
void mostrarAltaPelicula(char nombre[]);
int mostrarListarPorP();
int mostrarListarPorU();
void presionarEsc();
void presionarNum();
void presionarContinuar();
void proximamente();
void mostrarFormularioPeliculas();
int mostrarModificarPelicula();
int evaluarPelicula(int filtrosAplicados[], stPelicula peliculaFiltro, stPelicula temp);
void mostrarListadoPeliculas(char archivo[],int filtroActivado, int filtrosAplicados[], stPelicula peliculaFiltro);
int mostrarFiltroDePeliculas();
int evaluarUsuario(int filtrosAplicados[], stUsuario userFiltro, stUsuario temp);
void mostrarListadoUsuarios(char archivo[],int filtroActivado, int filtrosAplicados[], stUsuario userFiltro);
int mostrarFiltroDeUsuarios();
int mostrarMenuOpcionArbol();

#endif // GRAFICA_H
