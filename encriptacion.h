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
 * @brief Genera el vector key con el cual despues se generan las matrices claves para encriptar o desencriptar las contraseñas.
 *
 * @param vKey Arreglo en el cual se guardaran los dos numeros para generar la matriz clave.
 */
void generarVectorKey(int vkey[]);


/**
 * @brief Encripta una contraseña.
 *
 * @param pass Arreglo con la contraseña.
 * @param vKey Arreglo vector key del usuario.
 * @param encriptPass Matriz a devolver con la contraseña encriptada.
 */
void encriptarPass(char pass[], int vKey[], int encriptPass[f][c]);


/**
 * @brief Desencripta una contraseña.
 *
 * @param vKey Arreglo vector key del usuario.
 * @param encriptPass Matriz con la contraseña encriptada.
 * @param pass Arreglo en el cual se va a devolver la contraseña desencriptada.
 */
void desecriptarPass(int vKey[], int encriptPass[f][c], char pass[]);
