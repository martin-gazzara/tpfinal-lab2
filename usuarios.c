#include "usuarios.h"

///***************************************************************************************************************************************
/// ****************************                              RECOMENDADAS                                    ****************************
///***************************************************************************************************************************************

// Calcula cuantas peliculas vio de cada genero
void generosVistos(int g[], char gen[]){
    int i = 0;
    if(strcmp(gen, "Drama") == 0){
        g[0] += 1;
    }else if(strcmp(gen, "Comedia") == 0){
        g[1] += 1;
    }else if(strcmp(gen, "Accion") == 0){
        g[2] += 1;
    }else if(strcmp(gen, "Ciencia Ficcion") == 0){
        g[3] += 1;
    }else if(strcmp(gen, "Fantasia") == 0){
        g[4] += 1;
    }else if(strcmp(gen, "Terror") == 0){
        g[5] += 1;
    }else if(strcmp(gen, "Aventura") == 0){
        g[6] += 1;
    }else if(strcmp(gen, "Romance") == 0){
        g[7] += 1;
    }else if(strcmp(gen, "Musical") == 0){
        g[8] += 1;
    }else if(strcmp(gen, "Suspenso") == 0){
        g[9] += 1;
    }
}

// Funcion que se fija que generos de peliculas ve el usuario
void generosHistorial(nodoListaPelicula* lista, int generos[]){
    nodoListaPelicula* temp = lista;
    while(!temp){
        generosVistos(generos, temp->p.genero);
        temp = temp->sig;
    }
}

// Busca cual es el genero mas visto
int buscarMayor(int g[]){
    int i=0;
    int pos=0;
    int mayor = g[i];
    i++;
    pos= i;
    while(i<10){
        if(mayor < g[i]){
            mayor = g[i];
            pos = i;
        }
        i++;
    }
    return pos;
}

// Funcion que retorna la cantidad de peliculas del genero mas visto
int recomendar(char genero[], stPelicula peliGeneros[], nodoListaPelicula* lista){
    nodoListaPelicula* temp = lista;
    int i=0;
    while(!temp){
        if(strcmp(temp->p.genero, genero) == 0){
            peliGeneros[i] = temp->p;
            i++;
        }
        temp = temp->sig;
    }
    return i;
}

// Recomendar peliculas segun los generos más vistos por el usuario
stPelicula recomendarPelisGenero(stCelda user){
    srand(time(NULL));
    int pos, val, cant, random;
    char generos[][20]={{"Drama"}, {"Comedia"}, {"Accion"}, {"Ciencia Ficcion"}, {"Fantasia"}, {"Terror"}, {"Aventura"}, {"Romance"}, {"Musical"}, {"Suspenso"}};
    int g[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    generosHistorial(user.listaPelis, g);
    cant = cantidadNodos(user.listaPelis);
    stPelicula pelis[cant];
    pos = buscarMayor(g);
    val = recomendar(generos[pos], pelis, user.listaPelis);
    random = rand()%val;
    return pelis[random];
}

// Genera un arreglo con las peliculas con una valoracion mayor a 7
int pelisMayorVal(stPelicula pelis[], nodoListaPelicula* lista){
    nodoListaPelicula* temp = lista;
    int i=0;
    while(!temp){
        if(temp->p.valoracion > 7){
            pelis[i] = temp->p;
            i++;
        }
        temp = temp->sig;
    }
    return i;
}

// Recomienda una peli por mayor valoracion
stPelicula recomendarPelisValoracion(stCelda user){
    srand(time(NULL));
    int i, val;
    int cant =cantidadNodos(user.listaPelis);
    stPelicula pelisMayor7[cant];
    val = pelisMayorVal(pelisMayor7, user.listaPelis);
    i= rand()%val;
    return pelisMayor7[i];
}

// Recomienda la ultima peli cargada
stPelicula recomendarPelisNueva(char archivoPeli[]){
    FILE* arch;
    arch = fopen(archivoPeli, "rb");
    stPelicula temp;
    int cant = cantidadRegistros(arch, sizeof(stPelicula));
    fseek(arch, (cant-1)*sizeof(stPelicula), SEEK_SET);
    fread(&temp, sizeof(stPelicula), 1, arch);
    fclose(arch);
    return temp;
}

///***************************************************************************************************************************************
/// ****************************                        REPRODUCCION DE PELICULAS                             ****************************
///***************************************************************************************************************************************

// Calcula anio actual
int calcularAnioActual() {
    int aux;
    char fecha[]={"20"};
    time_t tiempo = time(0);
    struct tm *tlocal = localtime(&tiempo);
    char output[128];
    strftime(output,128,"%y",tlocal);
    strcat(fecha,output);
    int decimal = 0;
    int i = 0;
    for(i=0; i<4; i++){
        decimal *= 10;
        decimal += (int)(fecha[i]-48);
    }
    return decimal;
}

// Calcula la edad del usuario en base a su año de nacimiento paara ver si puede ver "x" pelicula
int calcularEdad(stUsuario usuario){
    int anio1=calcularAnioActual();
    int anio2=usuario.anioNacimiento;
    return(anio1-anio2);
}

///***************************************************************************************************************************************
/// ****************************                             ALTA USUARIOS                                    ****************************
///***************************************************************************************************************************************

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

// Funcion que permite al usuario escribir su password
int tomarDatos(char us[],char pass[]){
    int aux;
    hidecursor(1);
    aux=escribirString(us);
    if (aux!=27){
        gotoxy(39,13);
        aux=escribirPass(pass);
    }
    hidecursor(0);
    return aux;
}

// Verificacion de password
int comprobarPass(char passIngresada[],int pass[][c_pass],int vKey[]){
    char passUser[max_pass];
    desecriptarPass(vKey,pass,passUser);
    return strcmp(passIngresada,passUser);
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
void grabarUser(stCelda adl[], char archivo[], char username[], char pass[]){
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
        agregarUser(user, adl);
    }
    fclose(arch);
}

// Inicio de sesion
void iniciarSesion(char DB_usuarios[],char DB_peliculas[]){
    char nombreUsuario[string_max];
    char password[max_pass+1]={0};
    stUsuario usuario;
    int esc;
    mostrarIniciarSesion();    //   Grafica
    esc=tomarDatos(nombreUsuario,password);    // Se adquieren los datos para el inicio de sesion
    system("cls");
    if (esc!=27){
        gotoxy(0,0);
        usuario=buscarUsuario(DB_usuarios,nombreUsuario);   //  Busqueda del usuario, devuelve el usuario en cuestion
        if (usuario.id>0){                                   // Si id==0, el usuario no existe
            system("cls");
            gotoxy(0,0);
            if (comprobarPass(password,usuario.pass,usuario.vectorKey)==0){    // Se comprueba que la contraseña ingresada sea la correcta
                if (usuario.tipo==0){                        // En caso de un inicio correcto, se ejecuta el modo usuario o modo admin
                    menuUsuario(usuario,DB_usuarios,DB_peliculas);
                }else{
                    menuAdmin(usuario,DB_usuarios,DB_peliculas);
                }
            }else{
                printf("Password incorrecta\n");  /// borrar
                siguiente();
            }
        }else{
            printf("Usuario no encontrado");   /// borrar
        }
    }
    return;
}

//Crea un usuario nuevo
void crearUsuario(char archivo[]){
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
                grabarUser(archivo, tempUser, temp1);
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
