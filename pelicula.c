#include "pelicula.h"


//Modifica una película.
void modificarPelicula(char archivo[],nodoArbol* arbolPeliculas){

    int id, opcion = 0;
    FILE* arch = NULL;
    stPelicula pelicula;
    nodoArbol* nodoPelicula;

    system("cls");
    presionarNum();
    mostrarIngresarID();
    scanf("%i",&id);
    nodoPelicula = buscar(arbolPeliculas,id);
    if (nodoPelicula){
        pelicula = nodoPelicula->p;
        while (opcion!=10){
            system("cls");
            opcion = mostrarModificarPelicula(pelicula);
            system("cls")
            gotoxy(0,7);
            switch (opcion){
                case 0:
                    printf("Nombre actual: %s\n",pelicula.nombre);
                    printf("Ingrese nuevo nombre: ");
                    fflush(stdin);
                    gets(&pelicula.nombre);
                    break;
                case 1:
                    printf("Director actual: %s\n",pelicula.director);
                    printf("Ingrese nuevo director: ");
                    fflush(stdin);
                    gets(&pelicula.director);
                    break;
                case 2:
                    printf("Anio actual: %i\n",pelicula.anio);
                    printf("Ingrese anio nuevo: ");
                    scanf("%i",&pelicula.anio);
                    break;
                case 3:
                    printf("Genero actual: %s\n",pelicula.genero);
                    printf("Ingrese nuevo genero: ");
                    fflush(stdin);
                    gets(&pelicula.genero);
                    break;
                case 4:
                    printf("Lenguaje actual: %s\n",pelicula.lenguaje);
                    printf("Ingrese nuevo lenguaje: ");
                    fflush(stdin);
                    gets(&pelicula.lenguaje);
                    break;
                case 5:
                    printf("Pais actual: %s\n",pelicula.pais);
                    printf("Ingrese nuevo pais: ");
                    fflush(stdin);
                    gets(&pelicula.pais);
                    break;
                case 6:
                    printf("PM actual: %i\n",pelicula.pm);
                    printf("Ingrese PM nuevo: ");
                    scanf("%i",&pelicula.pm);
                    break;
                case 7:
                    printf("Subtitulo actual (1-Si 0-No): %i\n",pelicula.subtitulo);
                    printf("Ingrese subtitulo nuevo: ");
                    do{
                        scanf("%i",&pelicula.pm);
                    }while((pelicula.pm != 0) && (pelicula.pm != 1));
                    break;
                case 8:
                    printf("Valoracion actual: %i\n",pelicula.valoracion);
                    printf("Ingrese valoracion nueva: ");
                    do{
                        scanf("%i",&pelicula.pm);
                    }while((pelicula.pm < 1) && (pelicula.pm > 10));
                    break;
                case 9:
                    printf("Ingrese nueva sinopsis: \n");
                    fflush(stdin);
                    gets(&pelicula.sinopsis);
                    break;
            }
        }
    }else{
        printf("No se encuentra la pelicula");
        siguiente();
    }

}
