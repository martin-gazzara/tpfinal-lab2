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


///--------------------------------------------------------------------------------------------------------------------------Mostrar pre-order

void preorder(nodoArbol* arbol){

    if (arbol){
        // Mostrar pelicula
        preorder(arbol->izq);
        preorder(arbol->der);
    }
}


///---------------------------------------------------------------------------------------------------------------------------Mostrar in-order

void inorder(nodoArbol* arbol){

    if (arbol){
        inorder(arbol->izq);
        // Mostrar pelicula
        inorder(arbol->der);
    }
}


///-------------------------------------------------------------------------------------------------------------------------Mostrar post-order

void postorder(nodoArbol* arbol){

    if (arbol){
        postorder(arbol->izq);
        postorder(arbol->der);
        // Mostrar pelicula
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


///-------------------------------------------------------------------------------------------------------------------------------Mostrar nodo

void mostrarNodo(nodoArbol* nodo){

    //Mostrar pelicula
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
