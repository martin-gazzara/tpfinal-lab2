#include "libarbol.h"


///------------------------------------------------------------------------------------------------------------------------------Iniciar arbol

nodoArbol* inicArbol(){

    return NULL;
}

///---------------------------------------------------------------------------------------------------------------------------------Crear nodo

nodoArbol* crearNodo(stPelicula p){

    nodoArbol* nuevo_nodo = (nodoArbol* )malloc(sizeof(nodoArbol));

    nuevo_nodo->p = p;
    nuevo_nodo->izq = NULL;
    nuevo_nodo->der = NULL;
    return nuevo_nodo;
}


///------------------------------------------------------------------------------------------------------------------------------Insertar nodo

nodoArbol* insertar(nodoArbol* arbol, nodoArbol* nuevo_nodo){

    if (arbol == NULL){
        arbol = nuevo_nodo;
    }else{
        if (nuevo_nodo->p.id < arbol->p.id){
            arbol->izq = insertar(arbol->izq, nuevo_nodo);
        }else{
            arbol->der = insertar(arbol->der, nuevo_nodo);
        }
    }
    return arbol;
}

///-----------------------------------------------------------------------------------------------------------------------Mostrar Pelicula

void mostrarPeliDisp(stPelicula peli){
    gotoxy(0,whereY());printf("%i",peli.id);
    gotoxy(5,whereY());printf("%s",peli.nombre);
    gotoxy(45,whereY());printf("%i",peli.anio);
    gotoxy(50,whereY());printf("%s",peli.genero);
    gotoxy(66,whereY());printf("%s",peli.director);
    gotoxy(87,whereY());printf("%s",peli.lenguaje);
    printf("\n");
}

void mostrarPeliAdmin(stPelicula peli){
    gotoxy(0,whereY());printf("%i",peli.id);
    gotoxy(5,whereY());printf("%s",peli.nombre);
    gotoxy(45,whereY());printf("%i",peli.anio);
    gotoxy(50,whereY());printf("%s",peli.genero);
    gotoxy(66,whereY());printf("%s",peli.director);
    gotoxy(87,whereY());printf("%s",peli.lenguaje);
    gotoxy(98,whereY());printf("%i",peli.eliminado);
    printf("\n");
}

///--------------------------------------------------------------------------------------------------------------------------Mostrar pre-order

void preorder(nodoArbol* arbol, stUsuario user){

    if (arbol){
        if(user.admin == 1){
            mostrarPeliAdmin(arbol->p);
        }else{
            mostrarPeliDisp(arbol->p);
        }
        //mostrarPeliDisp(arbol->p);
        preorder(arbol->izq, user);
        preorder(arbol->der, user);
    }
}

///---------------------------------------------------------------------------------------------------------------------------Mostrar in-order

void inorder(nodoArbol* arbol, stUsuario user){

    if (arbol){
        inorder(arbol->izq, user);
        if(user.admin == 1){
            mostrarPeliAdmin(arbol->p);
        }else{
            mostrarPeliDisp(arbol->p);
        }
        inorder(arbol->der, user);
    }
}

///-------------------------------------------------------------------------------------------------------------------------Mostrar post-order

void postorder(nodoArbol* arbol, stUsuario user){

    if (arbol){
        postorder(arbol->izq, user);
        postorder(arbol->der, user);
        if(user.admin == 1){
            mostrarPeliAdmin(arbol->p);
        }else{
            mostrarPeliDisp(arbol->p);
        }
    }
}

///--------------------------------------------------------------------------------------------------------------------------------Buscar nodo

nodoArbol* buscar(nodoArbol* arbol, int id){

    nodoArbol* aux = NULL;

    if (arbol){
        if (id == arbol->p.id){
            aux = arbol;
        }else{
            if (id < arbol->p.id){
                aux = buscar(arbol->izq,id);
            }else{
                aux = buscar(arbol->der,id);
            }
        }
    }
    return aux;
}

///------------------------------------------------------------------------------------------------------------------------------Buscar por nombre

nodoArbol * buscarEnpreorderNombre(nodoArbol * arbol, char nombre[]){
    nodoArbol * rta = NULL;
    if(arbol!=NULL){
        if(strcmp(arbol->p.nombre,nombre)){
            rta=arbol;
        } else {
            rta=buscarEnpreorderNombre(arbol->izq, nombre);
            if(!rta){
                rta=buscarEnpreorderNombre(arbol->der, nombre);
            }
        }
    }
    return rta;
}

///------------------------------------------------------------------------------------------------------------------------------Buscar por genero
nodoArbol* buscarEnpreorderGenero(nodoArbol * arbol, char genero[]){
    nodoArbol * rta = NULL;
    if(arbol!=NULL){
        if(strcmp(arbol->p.genero,genero)){
            rta=arbol;
        } else {
            rta=buscarEnpreorderGenero(arbol->izq, genero);
            if(!rta){
                rta=buscarEnpreorderGenero(arbol->der, genero);
            }
        }
    }
    return rta;
}


///-------------------------------------------------------------------------------------------------------------------------------Mostrar nodo

void mostrarNodo(nodoArbol* nodo, stUsuario user){
    if(user.admin == 1){
        mostrarPeliAdmin(nodo->p);
    }else{
        mostrarPeliDisp(nodo->p);
    }
    printf("Rama izquierda: %p\n",nodo->izq);
    printf("Rama derecha: %p\n",nodo->der);
}


///--------------------------------------------------------------------------------------------------------------------------------Borrar nodo

nodoArbol* borrarNodo(nodoArbol* arbol, int id){

    nodoArbol* aux;

    if (arbol){
        if (id == arbol->p.id){
            if (arbol->izq){
                aux = nmd(arbol->izq);
                arbol->p.id = aux->p.id;
                arbol->izq = borrarNodo(arbol->izq,aux->p.id);
            }else if (arbol->der){
                aux = nmi(arbol->der);
                arbol->p.id = aux->p.id;
                arbol->der = borrarNodo(arbol->der,aux->p.id);
            }else{
                free(arbol);
                arbol = NULL;
            }
        }else{
            if (id< arbol->p.id){
                arbol->izq = borrarNodo(arbol->izq,id);
            }else{
                arbol->der = borrarNodo(arbol->der,id);
            }
        }
    }
    return arbol;
}


///---------------------------------------------------------------------------------------------------------------------------Nodo mas derecho

nodoArbol* nmd(nodoArbol* arbol){

    if ((arbol)&&(arbol->der)){
        arbol = nmd(arbol->der);
    }
    return arbol;
}

///-------------------------------------------------------------------------------------------------------------------------Nodo mas izquierdo

nodoArbol* nmi(nodoArbol* arbol){

    if ((arbol)&&(arbol->izq)){
        arbol = nmi(arbol->izq);
    }
    return arbol;
}

///----------------------------------------------------------------------------------------------------------------------------------Cantidad Nodos
int cantidadNodosArbol(nodoArbol*arbol){
    int i = 0;
    if(arbol!=NULL){
        i = 1 + cantidadNodosArbol(arbol->izq) + cantidadNodosArbol(arbol->der);
    }
    return i;
}

///------------------------------------------------------------------------------------------------------------Generador de arbol


//Pasa las películas de un archivo a un arreglo.
void pasarArreglo(FILE* arch, stPelicula arregloPeliculas[],int cant) {
    fread(arregloPeliculas, sizeof(stPelicula), cant, arch);
}

nodoArbol* leerMitad(nodoArbol* arbol, stPelicula arregloTemporal[] ,int desde, int hasta){

    int index;
    stPelicula pelicula;

    // Se intenta buscar la mitad del segmento que existe entre <desde> y <hasta>
    if ((hasta-desde) > 0){

        // El index, o la pelicula que vamos a leer, dependerá si el segmento es par o impar.
        if ((hasta-desde) % 2 == 0){

            index = (hasta-desde)/2 ;

        }else{
            index = (hasta-desde)/2 + 1;
        }
        // Sumar el valor de <desde> permite hacer las lecturas del segmento de la derecha
        // Index resulta al final, un valor de referencia de cuanto vamos a movernos con el fseek
        index += desde;
        // Como veniamos haciendo, la realidad es que debemos movernos un valor menos al index, para poder hacer la lectura
        // de la pelicula

        arbol = insertar(arbol,crearNodo(arregloTemporal[index]));
        arbol->izq = leerMitad(arbol->izq,arregloTemporal,desde,index-1);
        arbol->der = leerMitad(arbol->der,arregloTemporal,index,hasta);

    }
    return arbol;
}

nodoArbol* generarArbol(char DB_peliculas[]){

    FILE* arch = NULL;
    arch = fopen(DB_peliculas,"rb");
    nodoArbol* arbol = inicArbol();
    int cantPeliculas =  cantidadRegistros(arch,sizeof(stPelicula));

    stPelicula arregloTemporal[cantPeliculas];
    pasarArreglo(arch,arregloTemporal,cantPeliculas);

    fclose(arch);

    arbol = leerMitad(arbol,arregloTemporal,0,cantPeliculas-1);
    return arbol;
}

