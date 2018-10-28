#include <stdlib.h>
#include <stdio.h>
#include <time.h>



void mostrarMatriz_int(int f,int c,int matriz[][c]);
void sumarMatrices_int(int f,int c,int matrizA[][c],int matrizB[][c],int matrizC[][c]);
void restarMatrices_int(int f,int c,int matrizA[][c],int matrizB[][c],int matrizC[][c]);
void divisionMatriz_int(int f,int c,int matriz[][c],int num);
int determinante_int(int f,int c,int matriz[][c]);
int orden_int(int f,int c);
void traspuesta_int(int* f,int* c,int matriz[][*c]);
void adjunta_int(int f,int c,int matriz[][c]);
void inversa_int(int f,int c,int matriz[][c]);
void intercambiar_int(int* a,int* b);
