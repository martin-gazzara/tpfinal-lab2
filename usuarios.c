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

void editarNombre(stUsuario* user, char[] DB_usuarios){

    int existe;
    char nuevo_nombre[];

    do{
        system("cls");
        printf("MODIFICAR NOMBRE DE USUARIO\n\n");
        printf("Valor actual: %i\n",user->nombre);
        printf("Nuevo valor: ");
        gets(nuevo_nombre);
        ok = verificarDatos(DB_usuarios,nuevo_nombre)
        if(existe){
            printf("Ese nombre ya esta en uso.");
        }
    }while((existe) || (!strcmp(nuevo_nombre,user->nombre)));                 // Considerar para futuras correcciones.
    if(!existe){
        strcpy(user->nombre,nuevo_nombre);
    }
}

void editarEliminado(stUsuario* user){

    int aux;

    do{
        system("cls");
        printf("MODIFICAR ELIMINACION LOGICA (1-Eliminado / 0-Activo)\n\n");
        printf("Valor actual: %i\n",user->eliminado);
        printf("Nuevo valor: ");
        scanf("%i",&aux);
    }while((aux!=1) || (aux!=0));
    user->eliminado = aux;
}

void editarAdmin(stUsuario* user){

    int aux;

    do{
        system("cls");
        printf("MODIFICAR PERMISOS DE ADMINISTRADOR (1-Admin / 0-Usuario)\n\n");
        printf("Valor actual: %i\n",user->admin);
        printf("Nuevo valor: ");
        scanf("%i",&aux);
    }while((aux!=1) || (aux!=0));
    user->admin = aux;
}

void modificarUsuario(stUsuario* user,char[] DB_usuarios){

    char pass[max_pass+1];
    int opcion;

    desencriptar(user->vectorKey,user->pass,pass);
    system("cls");
    do{
        gotoxy(0,7);
        printf("       Nombre       : %s",user->nombre);
        printf("      Password      : %s",pass);
        printf("        Anio        : %i",user->anioNacimiento);
        printf("        Pais        : %s",user->pais);
        printf("       Genero       : %s",user->genero);
        printf("       Admin        : %i (1-Si/0-No)",user->admin);
        printf("      Eliminado     : %i (1-Si/0-No)",user->eliminado);
        printf("       SALIR        ");
        opcion = mostrarModificarUsuario();
        switch (opcion){
            case 0:
                editarNombre(user,DB_usuarios);
                break;
            case 1:
                editarPass(user,pass);
                break;
            case 2:
                editarAnio(user);
                break;
            case 3:
                editarPais(user);
                break;
            case 4:
                editarGenero(user);
                break;
            case 5:
                editarAdmin(user);
                break;
            case 6:
                editarEliminado(user);
                break;
        }
    }while(opcion!=7);
}
