#include "listasSimplesPeliculas.h"
//inicializa una lista
nodoListaPelicula *inicLista()
{
    return NULL;
}
//Crea un nodo de Lista
nodoListaPelicula *crearNodoLista(stPelicula pelicula)
{
    nodoListaPelicula *nuevoNodo;
    nuevoNodo->p = pelicula;
    nuevoNodo->sig = NULL;

    return nuevoNodo;
}

//Agrega un nodo al inicio de la lista
nodoListaPelicula *agregarAlPrincipio(nodoListaPelicula *lista,nodoListaPelicula *nuevoNodo)
{
    if(!lista)
    {
        lista = nuevoNodo;
    }
    else
    {
        nuevoNodo->sig = lista;
        lista = nuevoNodo;
    }
    return lista;
}

//Busca el ultimo de la lista
nodoListaPelicula *buscarUltimo(nodoListaPelicula *lista)
{
    nodoListaPelicula *ultimo;
    if(lista->sig != NULL)
    {
        ultimo = buscarUltimo(lista->sig);
    }
    return ultimo;
}

//Agrega un nodo al final de la Lista
nodoListaPelicula *agregarAlFinal(nodoListaPelicula *lista,nodoListaPelicula *nuevoNodo)
{
    nodoListaPelicula *ultimo;
    if(!lista)
    {
        lista = nuevoNodo;
    }
    else
    {
        ultimo  = buscarUltimo(lista);
        ultimo->sig = nuevoNodo;
    }
    return lista;
}

//Agrega en orden a la Lista
nodoListaPelicula *agregarEnOrdenPorNombreDePelicula(nodoListaPelicula *lista,nodoListaPelicula *nuevoNodo){
    if(lista){
        lista = nuevoNodo;
    }else{
        if(nuevoNodo->p.id < lista->p.id){
            agregarAlPrincipio(lista,nuevoNodo);
        }else{
            nodoListaPelicula *ante = lista;
            nodoListaPelicula *sig = lista->sig;
            while(sig != NULL && sig->p.id,nuevoNodo->p.id>=0){
                ante = sig;
                sig =sig->sig;
            }
            nuevoNodo->sig = sig;
            ante->sig = nuevoNodo;
        }
    }
    return lista;

}

//busca un nodo por nombre
nodoListaPelicula *buscarNodoPorNombre(nodoListaPelicula *lista, char nombre[]){
    nodoListaPelicula *aux;
    aux = lista;
        while(aux !=NULL && strcmp(aux->p.nombre,nombre)!=0){
                aux = aux->sig;
        }
    return aux;
}

//Busca un nodo por id
nodoListaPelicula *buscarNodoPorId(nodoListaPelicula *lista,int id){
    nodoListaPelicula *aux;
    aux = lista;
    while(aux !=NULL && aux->p.id != id){
        aux = aux->sig;
    }
    return aux;
}





void mostrarNodoLista(stPelicula pelicula){
    printf("idPelicula: %i\n",pelicula.id);
    printf("Nombre: %s\n",pelicula.nombre);
    printf("Director: %s\n",pelicula.director);
    printf("Genero: %s\n",pelicula.genero);
    printf("Pais: %s\n",pelicula.pais);
    printf("Anio: %i\n",pelicula.anio);
    printf("Valoracion: %i\n",pelicula.valoracion);
    printf("PM: %i\n",pelicula.pm);
}
void recorrerYmostrar(nodoListaPelicula *lista){
    nodoListaPelicula *aux = lista;
    while(aux !=NULL){
        mostrarNodo(aux->p);
        aux = aux->sig;
    }
}
nodoListaPelicula *borrarNodoPorIdPelicula(nodoListaPelicula *lista,int dato){
    nodoListaPelicula * ante;
    nodoListaPelicula * sig;
    if(lista != NULL && lista->p.id==dato){
        nodoListaPelicula * aux = lista;
        lista = lista->sig;
        free(aux);
    }else{
        sig = lista;
        while(sig != NULL && sig->p.id==dato){
         ante = sig;
         sig = sig->sig;
        }
        if(sig !=NULL){
            ante->sig = sig->sig;
            free(sig);
        }
    }
    return lista;
}

