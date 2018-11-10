#include "usuarios.h"

//Delimita cantidad de caracteres a ingresar
int escribirString(char arreglo[]){
    int aux,i=0;
    while ((aux!=13)&&(aux!=27)){
        fflush(stdin);
        aux=getch();
        if ((aux!=13)&&(((aux<123)&&(aux>64))||((aux>47)&&(aux<58)))&&(i<string_max-1)){
            arreglo[i]=(char)aux;
            printf("%c",arreglo[i]);
            i++;
        }else if((aux==8)&&(i>0)){
            gotoxy(whereX()-1,whereY());
            printf(" ");
            gotoxy(whereX()-1,whereY());
            i--;
        }
    }
    arreglo[i]='\0';
    return aux;
}

//Oculta caracteres al ingresar contraseña
int escribirPass(char pass[]){
    int aux,i=0;
    while ((aux!=13)&&(aux!=27)){
        fflush(stdin);
        aux=getch();
        if ((aux!=13)&&(((aux<123)&&(aux>64))||((aux>47)&&(aux<58)))&&(i<max_pass)){
            pass[i]=(char)aux;
            printf("*");
            i++;
        }else if((aux==8)&&(i>0)){
            gotoxy(whereX()-1,whereY());
            printf(" ");
            gotoxy(whereX()-1,whereY());
            i--;
        }
    }
    pass[i]='\0';
    return aux;
}

//Verifica si las contraseñas ingresadas son iguales.
int verificarPass(char pass1[],char pass2[]){
    return strcmp(pass1,pass2);
}

//Verifica si el username está en uso.
int verificarDatos(char archivo[], char username[]){
    FILE* arch;
    arch = fopen(archivo, "rb");
    stUsuario user;
    int flag=0;
    while(fread(&user, sizeof(stUsuario), 1, arch)>0){
        if(strcmp(user.nombre, username)==0){
            flag=1;
        }
    }
    fclose(arch);
    return flag;
}

//Verifica los datos a escenciales para registrar al usuario.
// 0: correcto 1: Contraseñas incorrectas 2: Usuario existente
int verificarCrearUser(char user[], char pass1[], char pass2[], char archivo[]){
    int flag = 0;
    int i;
    int vDatos = verificarDatos(archivo, user);
    int vPass = verificarPass(pass1, pass2);
    if(vDatos == 1){
        flag = 2;
    }else if(vPass!=0){
        flag = 1;
    }
    return flag;
}

// Calcula el id del nuevo usuario
int calcularIdU(FILE* arch){
    int id;
    if(!feof(arch)){
        id = cantidadRegistros(arch, sizeof(stUsuario))+1;
    }else{
        id=1;
    }
    return id;
}

// Graba un usuario al archivo.
void grabarUser(stCelda adl[], int val, char archivo[], char username[], char pass[]){
    FILE* arch = fopen(archivo, "a+b");
    stUsuario user;
    if (arch!=NULL){
        user.id=calcularIdU(arch);
        generarVectorKey(user.vectorKey);
        strcpy(user.nombre, username);
        encriptarPass(pass,user.vectorKey,user.pass);
        user.eliminado = 0;
        pedirInformacionPersonal(&user);
        if (user.id!=1){
            user.tipo = 0;
        }else{
            rewind(arch);
            user.tipo = 1;
        }
        fwrite(&user, sizeof(stUsuario), 1, arch);
        agregarUser(adl, val, user);
    }
    fclose(arch);
}

//Crea un usuario nuevo
void crearUsuario(char archivo[], stCelda adl[], int val){
    char temp1[max_pass+1];
    char temp2[max_pass+1];
    char tempUser[string_max];
    int ok=0,esc;
    do{
        system("cls");
        mostrarCrearUsuario();
        hidecursor(1);
        gotoxy(47,9);
        esc=escribirString(tempUser);
        if(esc!=27){
            gotoxy(53,13);
            esc=escribirPass(temp1);
            if(esc!=27){
                gotoxy(56,17);
                esc=escribirPass(temp2);
            }
        }
        hidecursor(0);
        if(esc!=27){
            ok = verificarCrearUser(tempUser, temp1, temp2, archivo);
            if(ok == 0){
                grabarUser(adl, val, archivo, tempUser, temp1);
                system("cls");
                gotoxy(37,8);printf("Cuenta creada exitosamente!");
                gotoxy(37,10);printf("Inicia sesion para comenzar");
                Sleep(1500);
            }else if(ok==1){
                gotoxy(38,19);printf("Las passwords no coinciden");
                siguiente();
            }else{
                gotoxy(36,11);printf("El nombre de usuario ya existe");
                siguiente();
            }
        }
    }while((ok!=0)&&(esc!=27));
}

//Funcion de bienvenida
void bienvenida(){
    char nombreDBUsuarios[]={"usuarios.bin"};
    char nombreDBPeliculas[]={"peliculas.bin"};
    char nombreDBPeliculasVistas[]={"peliculasVistas.bin"}
    nodoArbol* arbol = ;//crear arbol
    int acctivos = //calcular activos
    stCelda adl = pasarDeArchivoPelisVistasToADL(nombreDBUsuarios, nombreDBPeliculasVistas, activos, arbol);
    mostrarBienvenida();
    int opcion=0;
    while(opcion!=2){
        opcion=menuPrincipal();
        switch(opcion) {
        case 0:
            iniciarSesion(nombreDBUsuarios,nombreDBPeliculas);
            break;
        case 1:
            crearUsuario(adl, val, nombreDBUsuarios);
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
