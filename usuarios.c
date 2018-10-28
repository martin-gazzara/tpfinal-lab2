#include "usuarios.h"

void bienvenida(){
    char nombreDBUsuarios[]={"usuarios.bin"};
    char nombreDBPeliculas[]={"peliculas.bin"};
    mostrarBienvenida();
    int opcion=0;
    while(opcion!=2){
        opcion=menuPrincipal();
        switch(opcion) {
        case 0:
            iniciarSesion(nombreDBUsuarios,nombreDBPeliculas);
            break;
        case 1:
            crearUsuario(nombreDBUsuarios);
            break;
        }
    }
    cerrarPrograma();
}
