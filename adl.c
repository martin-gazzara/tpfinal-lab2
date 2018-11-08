#include "adl.h"
//Retorna la cantidad de usuarios activos que tiene el archivo
int usuariosActivos(char DB_usuarios[]) {
    FILE* arch = fopen(DB_usuarios, "rb");
    stUsuario user;
    int count = 0;
    while(fread(&user, sizeof(stUsuario), 1, arch)>0){
        if(user.eliminado==0){
            count += 1;
        }
    }
    fclose(arch);
    return count;
}

//Carga el arreglo con usuarios
void cargarArregloUsuarios(char DB_usuarios, stCelda adl[]){
    FILE* arch = fopen(DB_usuarios, "rb");
    stUsuario user;
    int index = 0;
    while(fread(&user, sizeof(stUsuario), 1, arch)>0){
        if(user.eliminado == 0){
            adl[index].usr = user;
            adl[index].listaPelis = NULL;
            index += 1;
        }
    }
}

//hacer funcion que en base a un id te retorne una pelicula

//ARBOLLLLLLLLLLLL
/*stPelicula peliculaVista(char DB_peliculas[], int id){
    FILE* arch = fopen(DB_peliculas, "rb");
    stPelicula temp;
    stPelicula p;
    int flag = 0;
    while(fread(&temp, sizeof(stPelicula), 1, arch)>0 && !flag){
        if(temp.id == id){
            flag = 1;
            p = temp;
        }
    }
    return p;
}*/

/*
//Carga la lista de peliculas vistas a cada usuario del arreglo
void cargarArregloPelisVistas(char DB_peliculasVistas[], stCelda adl[], int cantActivos){
    FILE* arch = fopen(DB_peliculasVistas, "rb");
    stPelisVistas p;
    int index = 0;
    while(index<cantActivos){
        rewind(arch);
        nodoListaPelicula* list = inicLista();
        while((fread(&p, sizeof(stPelisVistas), 1, arch)>0) && (p.idUsuario == adl[index].usr.id){
            adl[index].listaPelis = agregarAlFinal( list, crearNodoLista(peliculaVista(p.idPelicula)));
        }
        i+=1;
    }
    fclose(arch);
}
*/

//Carga el arreglo con las peliculas vistas de cada usuario
void cargarArregloPelisVistas(char DB_peliculasVistas[], arbol, adl, int cantActivos){
    FILE* arch = fopen(DB_peliculasVistas, "rb");
    stPelisVistas p;
    int index = 0;
    while(index<cantActivos){
        rewind(arch);
        nodoListaPelicula* list = inicLista();
        while((fread(&p, sizeof(stPelisVistas), 1, arch)>0) && (p.idUsuario == adl[index].usr.id){
            adl[index].listaPelis = agregarAlFinal( list, crearNodoLista(peliculaVista(p.idPelicula)));
        }
        i+=1;
    }
    fclose(arch);
}

//Agregar usuario a la lista
int agregarUsuario(stCelda adl[], int val, stUsuario user){
    stCelda* adl = (stCelda*)realloc(adl, sizeof(stCelda) * (val+1));
    adl[val].usr = user;
    adl[val].listaPelis = NULL;
    return val++;
}

//Crea el arreglo de listas
 stCelda* crearArreglo(char DB_usuarios[], DB_peliculasVistas[], int cantActivos){
    stCelda* adl = (stCelda*)malloc(sizeof(stCelda) * cantActivos);
    cargarArregloUsuarios(DB_usuarios, adl);
    cargarArregloPelisVistas(DB_peliculasVistas, adl);
    return adl;
 }

 //borrar elemento del adl en base al id
 int borrarUsuario(stCelda adl[] ,int id){

    while(index<val){

    }
 }

//
void pasarDeArchivoPelisVistasToADL() {

}

//Persiste los datos de las peliculas vistas
void actualizarPeliculasVistas() {
    //agregar nodo a lista
    //agregar elemento a archivo peliculas vistas
}
