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
            mostrarPeliAdmin(arbol.p);
        }else{
            mostrarPeli(arbol.p);
        }
        mostrarPeliDisp(arbol.p);
        preorder(arbol->izq);
        preorder(arbol->der);
    }
}

///---------------------------------------------------------------------------------------------------------------------------Mostrar in-order

void inorder(nodoArbol* arbol, stUsuario user){

    if (arbol){
        inorder(arbol->izq);
        if(user.admin == 1){
            mostrarPeliAdmin(arbol.p);
        }else{
            mostrarPeli(arbol.p);
        }
        inorder(arbol->der);
    }
}

///-------------------------------------------------------------------------------------------------------------------------Mostrar post-order

void postorder(nodoArbol* arbol, stUsuario user){

    if (arbol){
        postorder(arbol->izq);
        postorder(arbol->der);
        if(user.admin == 1){
            mostrarPeliAdmin(arbol.p);
        }else{
            mostrarPeli(arbol.p);
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
            rta=buscarEnpreorder(arbol->izq, nombre);
            if(!rta){
                rta=buscarEnpreorder(arbol->der, nombre);
            }
        }
    }
    return rta;
}

///------------------------------------------------------------------------------------------------------------------------------Buscar por genero
nodoArbol * buscarEnpreorderNombre(nodoArbol * arbol, char genero[]){
    nodoArbol * rta = NULL;
    if(arbol!=NULL){
        if(strcmp(arbol->p.genero,genero)){
            rta=arbol;
        } else {
            rta=buscarEnpreorder(arbol->izq, genero);
            if(!rta){
                rta=buscarEnpreorder(arbol->der, genero);
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
        mostrarPeli(nodo->p);
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
