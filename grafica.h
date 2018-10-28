#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <ctype.h>
#include "gotoxy.h"
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
