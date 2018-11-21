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
void cargarArregloUsuarios(char DB_usuarios[], stCelda adl[]){

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
    fclose(arch);
}

//Agrega las peliculas vista al adl
void agregarPeliVista(int id, stPelicula p, int val, stCelda adl[]){
    int index = 0;
    while((index < val) && (id != adl[index].usr.id)){
        index+=1;
    }
    if(id == adl[index].usr.id){
        adl[index].listaPelis = agregarAlFinal(adl[index].listaPelis, crearNodo(p));
    }
}

//Carga el arreglo con las peliculas vistas de cada usuario
void cargarArregloPelisVistas(char DB_peliculasVistas[], nodoArbol* arbol, stCelda adl[], int cantActivos){
    FILE* arch = fopen(DB_peliculasVistas, "rb");
    stPelisVistas p;
    nodoListaPelicula* peli;
    int index = 0;
    while(fread(&p, sizeof(stPelisVistas), 1, arch)>0){
        peli= buscar(arbol, p.idPelicula);
        if (peli){
            agregarPeliVista(p.idUsuario, peli->p, cantActivos, adl);
        }
    }
    fclose(arch);
}

//Agregar usuario al adl
int agregarUsuario(stCelda* adl, int val, stUsuario user){
    adl = (stCelda*)realloc(adl, sizeof(stCelda) * (val+1));
    adl[val].usr = user;
    adl[val].listaPelis = NULL;
    val+=1;
    return val;
}

//Crea el arreglo de listas
 stCelda* pasarDeArchivoToADL(char DB_usuarios[],char DB_peliculasVistas[], int cantActivos, nodoArbol* arbol){

    stCelda* adl = (stCelda*)malloc(sizeof(stCelda) * cantActivos);
    cargarArregloUsuarios(DB_usuarios, adl);
    cargarArregloPelisVistas(DB_peliculasVistas, arbol, adl, cantActivos);
    return adl;
 }

 //Borrar logicamente el elemento del adl en base al id
 void borrarUsuarioADL(stCelda adl[], int val ,int id){
    int index;
    while((index<val) && (adl[index].usr.id != id)){
        index++;
    }
    if(adl[index].usr.id == id){
        adl[index].usr.eliminado = 1;
    }
 }

//Persiste los datos de las peliculas vistas
void actualizarPeliculasVistas(stCelda adl[], int val, char DB_peliculasVistas[]) {
    FILE* arch = fopen(DB_peliculasVistas, 'wb');
    int index = 0;
    int id = 0;
    stPelisVistas pv;
    nodoListaPelicula* aux;
    while(index<val){
        aux = adl[index].listaPelis;
        while(aux){
            pv.idAutoincremental = id;
            pv.idUsuario = adl[index].usr.id;
            pv.idPelicula = aux->p.id;
            fwrite(&pv, sizeof(stPelisVistas), 1, arch);
            aux = aux -> sig;
            id += 1;
        }
            index += 1;
    }
    fclose(arch);
}

//Borrar peli de historial
void borrarPeliVistaADL(stCelda adl[], int val, int idPeli, int idUsuario){
    int index = 0;
    while((index<val) && (adl[index].usr.id != idUsuario)){
        index += 1;
    }
    if(adl[index].usr.id == idUsuario){
        adl[index].listaPelis = borrarNodoPorIdPelicula(adl[index].listaPelis, idPeli);
    }
}

//Persiste los datos de los usuarios
void actualizarUsuarios(stCelda adl[], int val, char DB_usuarios[]){
    FILE* arch = fopen(DB_usuarios, "wb");
    int index = 0;
    stUsuario user;
    while(index<val){
        user = adl[index].usr;
        fwrite(&user, sizeof(stUsuario), 1, arch);
        index += 1;
    }
    fclose(arch);
}

int buscarUsuarioPorNombre(stCelda adl[], int val, char nombre[]){
    int i = 0;
    while((i<val) && (strcmp(adl[i].usr.nombre, nombre)!=0)){
        i+=1;
    }
    if(strcmp(adl[i].usr.nombre, nombre)!=0){
        i = -1;
    }
    return i;
}

int buscarUsuarioPorId(stCelda adl[], int val, int id){
    int i = 0;
    while((i<val) && (adl[i].usr.id != id)) {
        i+=1;
    }
    if(adl[i].usr.id != id) {
        i = -1;
    }
    return i;
}
