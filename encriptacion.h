#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "matrices_int.h"
#define f_mkey 2
#define c_mkey 2
#define c 5
#define f 2


/**
 * @brief Genera el vector key con el cual despues se generan las matrices claves para encriptar o desencriptar las contrase�as.
 *
 * @param vKey Arreglo en el cual se guardaran los dos numeros para generar la matriz clave.
 */
void generarVectorKey(int vkey[]);


/**
 * @brief Encripta una contrase�a.
 *
 * @param pass Arreglo con la contrase�a.
 * @param vKey Arreglo vector key del usuario.
 * @param encriptPass Matriz a devolver con la contrase�a encriptada.
 */
void encriptarPass(char pass[], int vKey[], int encriptPass[f][c]);


/**
 * @brief Desencripta una contrase�a.
 *
 * @param vKey Arreglo vector key del usuario.
 * @param encriptPass Matriz con la contrase�a encriptada.
 * @param pass Arreglo en el cual se va a devolver la contrase�a desencriptada.
 */
void desecriptarPass(int vKey[], int encriptPass[f][c], char pass[]);
