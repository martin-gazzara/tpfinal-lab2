#include "matrices_int.h"
#include <time.h>

void mostrarMatriz_int(int f,int c,int matriz[][c]){

    int i,j;
    for(i=0;i<f;i++){
        for(j=0;j<c;j++){
            printf(" %i ",matriz[i][j]);
        }
        printf("\n");
    }
    return;
}

void sumarMatrices_int(int f,int c,int matrizA[][c],int matrizB[][c],int matrizC[][c]){

    int i,j;

    for(i=0;i<f;i++){
        for(j=0;j<c;j++){
            matrizC[i][j]=matrizA[i][j]+matrizB[i][j];
            i++;
        }
        j++;
    }
    return;
}

void restarMatrices_int(int f,int c,int matrizA[][c],int matrizB[][c],int matrizC[][c]){

    int i,j;

    for(i=0;i<f;i++){
        for(j=0;j<c;j++){
            matrizC[i][j]=matrizA[i][j]-matrizB[i][j];
        }
    }
    return;
}

void divisionMatriz_int(int f,int c,int matriz[][c],int num){

    int i,j;

    for(i=0;i<f;i++){
        for(j=0;j<c;j++){
            matriz[i][j]=matriz[i][j]/num;
        }
    }
    return;
}

int orden_int(int f,int c){

    int ord;

    if (f>c){
        ord=c;
    }else{
        ord=f;
    }
    return ord;
}

int determinante_int(int f,int c,int matriz[][c]){

    int det=0,i,j;

    if (f==c){
        switch (orden_int(f,c)){
            case 2:
                det=matriz[0][0]*matriz[1][1]-matriz[0][1]*matriz[1][0];
                break;
            case 3:
                printf("%i\n",det);
                det=matriz[0][0]*matriz[1][1]*matriz[2][2];
                printf("%i\n",det);
                det+=matriz[0][1]*matriz[1][2]*matriz[2][0];
                printf("%i\n",det);
                det+=matriz[0][2]*matriz[1][0]*matriz[2][1];
                printf("%i\n",det);
                det-=matriz[0][2]*matriz[1][1]*matriz[2][0];
                printf("%i\n",det);
                det-=matriz[0][1]*matriz[1][0]*matriz[2][2];
                printf("%i\n",det);
                det-=matriz[0][0]*matriz[1][2]*matriz[2][1];
                printf("%i\n",det);
                break;
            default:
                printf("Aun no disponible para este orden.");
        }
    }else{
        det=0;
    }
    return det;
}

void traspuesta_int(int* f,int* c,int matriz[][*c]){

    int i=0,j;
    int aux;

    while(i<*f){
        j=i+1;
        while (j<*c){
            intercambiar_int(&matriz[i][j],&matriz[j][i]);
            j++;
        }
        i++;
    }
    intercambiar_int(f,c);
    return;
}

void adjunta_int(int f,int c,int matriz[][c]){

    if (f==c){
        if (f==2){
            intercambiar_int(&matriz[0][0],&matriz[1][1]);
            intercambiar_int(&matriz[1][0],&matriz[0][1]);
            matriz[1][0]=(-1)*matriz[1][0];
            matriz[0][1]=(-1)*matriz[0][1];
        }
    }
    return;
}

void inversa_int(int f,int c,int matriz[][c]){

    int det=determinante_int(f,c,matriz);

    traspuesta_int(&f,&c,matriz);
    adjunta_int(f,c,matriz);
    divisionMatriz_int(f,c,matriz,det);
    return;
}

void intercambiar_int(int* a,int* b){

    int aux;

    aux=*a;
    *a=*b;
    *b=aux;

    return;
}

