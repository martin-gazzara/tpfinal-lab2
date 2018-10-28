#include "encriptacion.h"

///*****************************************************************************
///******************            ENCRIPTACION              *********************
///*****************************************************************************

//Genera el vector clave para generar la matriz clave.
void generarVectorKey(int vkey[]){

        srand(time(NULL));
        int i=0;
        int aux;
        int flag=0;
        while(i<2){
            do{
                aux=rand()%10;
            }while(aux==0);
            vkey[i]=aux;
            i++;
        }
}

//Genera la matriz clave.
int generarMatrizKey(int vKey[], int matKey[f_mkey][c_mkey]){
    matKey[0][0] = vKey[0] ;
    matKey[0][1] = (vKey[0] * vKey[1]) - 1;
    matKey[1][0] = 1;
    matKey[1][1] = vKey[1];
}

//(TINCHO)Completa los campos restantes de una matriz con 0.
void completarMatriz(int filas,int col,int matriz[f][c]){

    while (filas<f){
        while(col<c){
            matriz[filas][col]=0;
            col++;
        }
        filas++;
        col=0;
    }
    return;
}

//Pasa un arreglo de caracteres a una matriz de int.
void stringAMatriz(char arreglo[],int matriz[f][c]){

    int cant_digitos=strlen(arreglo);
    int i=-1,j,index=0;

    while ((i<f)&&(index<cant_digitos)){
        i++;
        j=0;
        while ((j<c)&&(index<cant_digitos)){
            matriz[i][j]=(int)arreglo[index];
            index++;
            j++;
        }

    }
    if (i!=f){
        completarMatriz(i,j,matriz);
    }
    return;
}


//Multiplica dos matrices.
void multiplicarMatrices(int pass[f][c], int matKey[f_mkey][c_mkey], int passEncriptada[f][c]){
    int i, j;
    for(i = 0; i < f; i++){
        for(j = 0; j < c; j++){
            passEncriptada[i][j] = (matKey[i][0] * pass[0][j]) + (matKey[i][1] * pass[1][j]);
        }
    }
}

//Encripta una contraseña.
void encriptarPass(char pass[], int vKey[], int encriptPass[f][c]){
    int matKey[f_mkey][c_mkey];
    int matPass[f][c];
    generarMatrizKey(vKey, matKey);
    stringAMatriz(pass, matPass);
    multiplicarMatrices(matPass, matKey, encriptPass);
}

///*****************************************************************************
///******************           DESENCRIPTACION            *********************
///*****************************************************************************

//Pasa una matriz de int a un arreglo de caracteres.
void matrizAString(int matriz[f][c],char arreglo[]){

    int i,j,index=0;

    for (i=0;i<f;i++){
        for(j=0;j<c;j++){
            if(matriz[i][j]!=0){
                arreglo[index]=(char)matriz[i][j];
                index++;
            }
        }
        j=0;
    }
    arreglo[index]='\0';
    return;
}

//Desencripta una contraseña.
void desecriptarPass(int vKey[], int encriptPass[f][c], char pass[]){
    int matKey[f_mkey][c_mkey];
    int desencriptPass[f][c];
    generarMatrizKey(vKey, matKey);
    inversa_int(2,2,matKey);
    multiplicarMatrices(encriptPass,matKey,desencriptPass);
    matrizAString(desencriptPass, pass);
}
