#include "usuarios.h"

void TOOL_MOSTRAR_ADL(stCelda adl[], int val,char place[]){

    int i = 0;

    system("cls");
    printf("In %s\n",place);
    while( i < val){
        printf("%i %s\n", adl[i].usr.id, adl[i].usr.nombre);
        i++;
    }
    siguiente();
    system("cls");

}



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
    //cant = cantidadNodos(user.listaPelis);
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
/*
// Recomienda una peli por mayor valoracion
stPelicula recomendarPelisValoracion(nodoArbol* arbol){
    srand(time(NULL));
    int i, val;
    int cant = cantidadNodos(arbol);
    stPelicula pelisMayor7[cant];
    val = pelisMayorVal(pelisMayor7, user.listaPelis);
    i= rand()%val;
    return pelisMayor7[i];
}
*/

// Recomienda la ultima peli cargada
stPelicula recomendarPelisNueva(nodoArbol* arbol){
    nodoArbol* ultimaPeli = nmi(arbol);
    stPelicula temp = ultimaPeli->p;
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
    desencriptarPass(vKey,pass,passUser);
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

// Solicita informacion personal a la hora de crear un usuario.

void pedirInformacionPersonal(stUsuario* user){
    system("cls");
    char gen;
    int esc,anioActual,anioBase=1900,condicion;
    anioActual=calcularAnioActual();
    mostrarPedirInformacion();
    gotoxy(55,9);
    do{
        hidecursor(1);
        scanf("%i",&user->anioNacimiento);
        condicion=(user->anioNacimiento>=anioActual)||(user->anioNacimiento<1900);
        if (condicion){
            hidecursor(0);
            gotoxy(34,11);printf("El anio debe ser entre %i y %i",anioBase,anioActual);
            siguiente();
            gotoxy(34,11);printf("                                  ");
            gotoxy(55,9);printf("           ");
            gotoxy(55,9);
        }
    }while(condicion);
    gotoxy(41,13);
    esc=escribirString(&user->pais);
    gotoxy(48,17);
    do{
        fflush(stdin);
        scanf("%c",&user->genero);
        user->genero=tolower(user->genero);
    }while((user->genero!='m')&&(user->genero!='f'));
    hidecursor(0);
}

// Graba un usuario al archivo.
int grabarUser(stCelda adl[], int val, char archivo[], char username[], char pass[]){
    FILE* arch = fopen(archivo, "a+b");
    stUsuario user;
    if (arch!=NULL){
        user.id=calcularIdU(arch);
        generarVectorKey(user.vectorKey);
        strcpy(user.nombre, username);
        encriptarPass(pass,user.vectorKey,user.pass);
        user.eliminado = 0;
        pedirInformacionPersonal(&user);
        if (user.id>1){
            user.admin = 0;
        }else{
            rewind(arch);
            user.admin = 1;
        }
        fwrite(&user, sizeof(stUsuario), 1, arch);
        val = agregarUsuario(adl, val, user);
    }
    fclose(arch);
    return val;
}


///****************************************************************************************************************************************
///                                               INICIO DE PROGRAMA
///****************************************************************************************************************************************
//Funcion de bienvenida
void bienvenida(){

    char nombreDBUsuarios[]={"usuarios.bin"};
    char nombreDBPeliculas[]={"peliculas.bin"};
    char nombreDBPeliculasVistas[]={"peliculasVistas.bin"};
    nodoArbol* arbol = generarArbol(nombreDBPeliculas);
    stCelda* adl = NULL;
    int val;


    val = usuariosActivos(nombreDBUsuarios);
        if (val>0){
            adl = pasarDeArchivoPelisVistasToADL(nombreDBUsuarios, nombreDBPeliculasVistas, val, arbol);
        }else{
            adl = (stCelda*)malloc(0);
        }
    mostrarBienvenida();
    int opcion=0;
    while(opcion!=2){

        opcion=menuPrincipal();
        switch(opcion) {
        case 0:
            iniciarSesion(adl, val, arbol, nombreDBUsuarios, nombreDBPeliculas);
            break;
        case 1:
            val = crearUsuario(adl, val, nombreDBUsuarios);
            break;
        }
    }
    cerrarPrograma();
}

///****************************************************************************************************************************************
///                                                INICIO DE SESION
///****************************************************************************************************************************************
// Inicio de sesion
void iniciarSesion(stCelda adl[], int val, nodoArbol* arbol, char DB_usuarios[], char DB_peliculas[]){
    // Variables que adquirirán los datos ingresados
    char nombreUsuario[string_max];
    char password[max_pass+1]={0};
    // Variable que adquiere el usuario en caso de haberse encontrado. Caso contrario adquiere un id=0
    int esc, index;
    mostrarIniciarSesion();    //   Grafica
    esc=tomarDatos(nombreUsuario,password);    // Se adquieren los datos para el inicio de sesion
    system("cls");
    if (esc!=27){
        gotoxy(0,0);
        index=buscarUsuarioPorNombre(adl, val, nombreUsuario);   //  Busqueda del usuario, devuelve el usuario en cuestion
        if ((index > -1) && (adl[index].usr.eliminado==0)){                                   // Si id==0, el usuario no existe
            system("cls");
            gotoxy(0,0);
            if (comprobarPass(password, adl[index].usr.pass, adl[index].usr.vectorKey)==0){    // Se comprueba que la contraseña ingresada sea la correcta
                if (adl[index].usr.admin==0){                        // En caso de un inicio correcto, se ejecuta el modo usuario o modo admin
                    menuUsuario(adl, index, DB_usuarios, DB_peliculas);
                }else{
                    menuAdmin(arbol, adl, val, DB_usuarios,DB_peliculas);
                }
            }else{
                printf("Password incorrecta\n");  /// borrar
                siguiente();
            }
        }else{
            printf("Usuario no encontrado");   /// borrar
            siguiente();
        }
    }
    return;
}
///****************************************************************************************************************************************
///                                                 MENU USUARIO
///****************************************************************************************************************************************
///    **  A MODIFICAR
void menuUsuario(stCelda usuarios[], int index, nodoArbol* arbol, char DB_usuarios[], char DB_peliculas[]){

    int i=0;
    stPelicula pelicula;
    int resp,edad,opcionArbol;
    stPelicula recomendadas[3];;
    while (i!=4){
        //recomendadas[0]=recomendarPelisGenero(usuarios[index]);
        //recomendadas[1]=recomendarPelisNueva(arbol);
        //recomendadas[2]=recomendarPelisValoracion(DB_peliculas);      ///  MODIFICAR
        i=mostrarMenuUsuario(usuarios[index].usr.nombre,recomendadas);
        switch (i){
        //Ver una pelicula
        case 0:
            do{
               // pelicula = buscarPelicula(DB_peliculas);              /// stPelicula = buscarPelicula(nodoArbol arbol)   MODIFICAR
                if (pelicula.id==0){
                     system("cls");
                        printf("La pelicula no esta disponible o no existe.");
                        presionarContinuar();
                        siguiente();
                }else if(pelicula.id>0){
                    system("cls");
                        mostrarPelicula(pelicula);
                        resp=mostrarVerPelicula();
                        if(resp==0){
                            edad=calcularEdad(usuarios[index].usr);
                            if(edad>=pelicula.pm){
                                verPelicula(usuarios[index],pelicula);          ///   verPelicula()  .. Puede ser una nueva funcion que irá solo en grafica
                                system("cls");
                                printf("Pelicula vista!!");
                                presionarContinuar();
                                siguiente();
                            }else{
                                system("cls");
                                printf("La pelicula que deseas ver no es apta para tu edad.");
                                presionarContinuar();
                                siguiente();
                            }
                        }
                }
            }while(pelicula.id!=-1);
            break;
        //Lista todas las peliculas disponibles
        case 1:
            system("cls");
            printf("Ingrese opcion para mostrar el arbol");
            scanf("%i",&opcionArbol);
            mostrarListadoPDis(arbol,opcionArbol,usuarios[index].usr);                   /// MODIFICAR     void listarPeliculasDisponibles(nodoArbol arbol)
            break;
        //Ver historial
        case 2:
            system("cls");
            mostrarHistorial(usuarios[index]);
            break;
        //Editar perfil
        case 3:
            //usuarios[index].usr = editarPerfil(usuarios[index].usr);
            break;
        //Cerrar sesion
        case 4:
            system("cls");
            break;
        }
    }
    return;
}

///***************************************************************************************************************************************
///                                                FUNCIONES DEL MENU USUARIO
///***************************************************************************************************************************************

///---------------------------------------------------------------------------------------------------------------------------------------
///                                                   Reproducir una pelicula
// Cuando un usuario elige ver una pelicula. La misma se "reproduce" y se incorpora a la lista de pelis vistas por el usuario.

void verPelicula(stCelda usuario, stPelicula pelicula){

    system("cls");
    printf("REPRODUCIENDO PELICULA...");
    //  Funcion para agregar una pelicula a la lista
    return;
}

///---------------------------------------------------------------------------------------------------------------------------------------
///                                                         Ver historial
// Muestra cada pelicula existente en el historial, de forma recursiva

void generarHistorial(nodoListaPelicula* historial){

    if (historial){
        printf("%i  %s %i %s  %s \n", historial->p.id, historial->p.nombre, historial->p.anio, historial->p.genero, historial->p.director);
        generarHistorial(historial->sig);
    }
}

// Mostrar el historial

void mostrarHistorial(stCelda usuario){

    int i;

    if (!usuario.listaPelis){
        system("cls");
            printf("No hay historial disponible. Presione una tecla para continuar...\n");
            siguiente();
    }else{
        gotoxy(0,3);                ///   Mover a una posicion adecuada, para empezar a imprimir cada pelicula
        generarHistorial(usuario.listaPelis);
        i=mostrarMenuHistorial();
        if (i==0){
            //borrar Historial               /// Debería retornar NULL ??
        }
    }
}

///---------------------------------------------------------------------------------------------------------------------------------------
///                                                      Editar perfil

stUsuario editarPerfil(stUsuario user){

    int campo;
    char pass[max_pass+1];
    do{
        system("cls");
        desencriptarPass(user.vectorKey,user.pass,pass);
        gotoxy(0,7);
        printf("      Password      : %s\n",pass);
        printf("        Anio        : %i\n",user.anioNacimiento);
        printf("       Genero       : %c\n",user.genero);
        printf("        Pais        : %s\n",user.pais);
        campo=mostrarEditarPerfil(user.nombre,user.id);
        switch (campo)
        {
        case 0:
            editarPass(&user,pass);
            break;
        case 1:
            editarAnio(&user);
            break;
        case 2:
            editarGenero(&user);
            break;
        case 3:
            editarPais(&user);
            break;
        }
    }while(campo!=4);

    return user;
}

// Editar pass

void editarPass(stUsuario* user,char passActual[]){


    int passNueva1[max_pass+1],passNueva2[max_pass+1];
    int esc,ok=-1;
    do{
    system("cls");
    presionarEsc();
    gotoxy(0,2);
    printf("Valor actual: %s\n",passActual);
    printf("Valor nuevo: ");
    esc=escribirPass(passNueva1);
    if (esc!=27){
        printf("\nRepita password: ");
        esc=escribirPass(passNueva2);
        if(esc!=27){
            ok=verificarPass(passNueva1,passNueva2);
            if (ok==1){
            system("cls");
            gotoxy(38,6);
            printf("\nLas passwords no coinciden.");
            presionarContinuar();
            siguiente();
            }
        }
    }
    }while((ok==1)&&(esc!=27));
    if(ok==0){
        encriptarPass(passNueva2,user->vectorKey,user->pass);
    }
}

// Editar año

void editarAnio(stUsuario* user){

    int aux;
    system("cls");
    presionarNum();
    gotoxy(0,2);
    printf("Valor actual: %i\n", user->anioNacimiento);
    printf("Valor nuevo: ");
    scanf("%i",&aux);
    if(aux!=-1){
        user->anioNacimiento=aux;
    }
}

//Editar genero

void editarGenero(stUsuario* user){

    char aux;

    system("cls");
    presionarEsc();
    gotoxy(0,2);
    printf("Valor actual: %c\n",user->genero);
    printf("Valor nuevo: ");
    do{
        fflush(stdin);
        aux=getch();
    }while((aux!='m')&&(aux!='f')&&(aux!=27));
    if (aux!=27){
        user->genero=aux;
    }
}

// Editar Pais

void editarPais(stUsuario* user){

    int esc;
    char aux[string_max];
    system("cls");
    presionarEsc();
    gotoxy(0,2);
    printf("Valor actual: %s\n",user->pais);
    printf("Valor nuevo: ");
    esc=escribirString(aux);
    if (esc!=27){
        strcpy(user->pais,aux);
    }
}

///****************************************************************************************************************************************
///                                                      CREAR UN USUARIO
///****************************************************************************************************************************************


///000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
///000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
///000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000



///************************************************************************************************************************************************
///                                                      MENU ADMIN
///************************************************************************************************************************************************

void menuAdmin(nodoArbol* arbol, stCelda adl[],int val, char DB_usuarios[], char DB_peliculas[]){

    int opcion_elegida;

    do{
        opcion_elegida=mostrarMenuAdmin();   // Grafica
        switch (opcion_elegida){
            case 0:
                val = gestionUsuarios(adl, val, DB_usuarios);
                break;
            case 1:
                gestionPeliculas(arbol, DB_peliculas);
                break;
        }
    }while (opcion_elegida!=2);

}


///**************************************************************************************************************************************************
///                                                  Gestion de usuarios
///**************************************************************************************************************************************************

int gestionUsuarios(stCelda adl[], int val, char DB_usuarios[]){

    int opcion_elegida;
    do{
        opcion_elegida=mostrarGestionUsuarios();
        switch(opcion_elegida){
            case 0:
                val = menuAltaUsuarios(adl, val, DB_usuarios);
                break;
            case 1:
                bajaUsuario(adl,val,DB_usuarios);
                break;
            case 2:
                listarUsuarios(adl, val, DB_usuarios);
                break;
            case 3:
                system("cls");
                menuBackUpU(DB_usuarios);
                break;

        }
    }while(opcion_elegida!=4);
    return val;
}

///-----------------------------------------------------------------------------------------------------------------------------
///                                                 Menu alta de usuarios
///-----------------------------------------------------------------------------------------------------------------------------

int menuAltaUsuarios(stCelda adl[], int val, char DB_usuarios[]){

    int opcion_elegida;
    do{
        opcion_elegida=mostrarDarAltaUsuarios();
        switch(opcion_elegida){
            case 0:
                val = crearUsuario(adl, val, DB_usuarios);
                break;
            case 1:
                val = habilitarUsuario(adl, val, DB_usuarios);
                break;
        }
    }while(opcion_elegida!=2);
    return val;
}

//----------------------------------------------------------------------------------------------------------------------------------------
//                                                      Crear usuario
//----------------------------------------------------------------------------------------------------------------------------------------

int crearUsuario(stCelda adl[], int val, char archivo[]){

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
                val = grabarUser(adl, val, archivo, tempUser, temp1);
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
    return val;
}

//--------------------------------------------------------------------------------------------------------------------------------
//                                                    Habilitar usuario
//--------------------------------------------------------------------------------------------------------------------------------

// Habilitar usuario en adl.

int habilitarUsuarioAdl(stCelda adl[],int val,stUsuario usuario){

    int i=0;

    while (( i < val ) && ( adl[i].usr.id != usuario.id )){
        i++;
    }
    if ( adl[i].usr.id == usuario.id ){
        adl[i].usr.eliminado = 0;
    }else{
        val = agregarUsuario(adl, val, usuario);
    }
    return val;
}

// Habilitar usuario en archivo.

int habilitarUsuario(stCelda adl[], int val, char DB_usuario[]){

    FILE* arch;
    stUsuario temp;
    int id;

    system("cls");
    presionarNum();
    mostrarIngresarID();
    scanf(" %i",&id);
    hidecursor(0);
    if(id!=-1){
        if ((arch = fopen(DB_usuario,"r+b"))!=NULL){
            fseek(arch, (id-1)*sizeof(stUsuario), SEEK_SET);
            fread(&temp, sizeof(stUsuario), 1, arch);
            if (temp.eliminado==1){
                temp.eliminado = 0;
                fseek(arch, (-1)*sizeof(stUsuario), SEEK_CUR);
                fwrite(&temp, sizeof(stUsuario), 1,arch);
                fclose(arch);
                val = habilitarUsuarioAdl(adl,val,temp);
                mostrarAltaUsuario(temp.nombre);
            }else{
                system("cls");
                gotoxy(46,7);
                printf("El usuario");
                gotoxy(47,9);
                printf("%s",temp.nombre);
                gotoxy(41,11);
                printf("no esta dado de baja.");
                presionarContinuar();
                siguiente();
            }
        }else{
            printf("Error en la apertura del archivo\n");
        }
    }
    return val;
}

///--------------------------------------------------------------------------------------------------------------------------------
///                                                 Menu baja de usuario
///--------------------------------------------------------------------------------------------------------------------------------

void bajaUsuarioEnArchivo(stUsuario user, char DB_usuarios[]){

    FILE* arch = fopen(DB_usuarios,"r+b");

    fseek(arch,sizeof(stUsuario)* (user.id-1),SEEK_SET);
    fwrite(&user,sizeof(stUsuario),1,arch);
    fclose(arch);
}

void bajaUsuario(stCelda adl[], int val,char DB_usuarios[]){

    int id, i=0;

    system("cls");
    presionarNum();
    mostrarIngresarID();
    scanf("%i",&id);
    hidecursor(0);
    if (id>-1){
        while (( i < val) && ( adl[i].usr.id != id )){
            i++;
        }
        system("cls");
        gotoxy(32,9);
        if (( adl[i].usr.id == id )){
            if (adl[i].usr.admin!=1){
                adl[i].usr.eliminado = 1;
                bajaUsuarioEnArchivo(adl[i].usr,DB_usuarios);
                mostrarBajaUsuario(adl[i].usr.nombre);
            }else{
                printf("Imposible dar de baja a un Administrador.");

            }
        }else{
            printf("No se ha encontrado el usuario.");
        }
    }
    presionarContinuar();
    siguiente();
}

///----------------------------------------------------------------------------------------------------------------------------------
///                                                 Menu listar usuarios
///----------------------------------------------------------------------------------------------------------------------------------

///****************************************************************+********************************+********************************+
///                                             Filtro de usuarios.
///****************************************************************+********************************+********************************+



stUsuario filtroDeUsuarios(stUsuario userTemp, int filtrosAplicados[], int* filtroActivado){

    int opc;

    do{
        system("cls");
        gotoxy(21,7);printf(": %c",userTemp.genero);
        gotoxy(21,8);printf(": %s",userTemp.pais);
        gotoxy(21,9);printf(": %i",userTemp.eliminado);
        gotoxy(21,10);printf(": %i",userTemp.anioNacimiento);
        opc = mostrarFiltroDeUsuarios();
        system("cls");
        switch (opc){
            case 0:
                completarCampoChar(&userTemp.genero,&filtrosAplicados[0]);
                break;
            case 1:
                completarCampoString(&userTemp.pais,&filtrosAplicados[1]);
                break;
            case 2:
                completarCampoBin(&userTemp.eliminado,&filtrosAplicados[2]);
                break;
            case 3:
                completarCampoInt(&userTemp.anioNacimiento,&filtrosAplicados[3]);
                break;
            case 4:
                *filtroActivado = 1;
                system("cls");
                gotoxy(50,10);
                printf("Filtros activados!");
                presionarContinuar();
                siguiente();
                break;
            case 5:

                userTemp.genero = ' ';
                strcpy(userTemp.pais,"");
                userTemp.eliminado = 0;
                userTemp.anioNacimiento = 0;

                filtrosAplicados[0] = 0;
                filtrosAplicados[1] = 0;
                filtrosAplicados[2] = 0;
                filtrosAplicados[3] = 0;

                *filtroActivado = 0;
                system("cls");
                gotoxy(50,10);
                printf("Filtros desactivados!");
                presionarContinuar();
                siguiente();
                break;
        }

    }while( opc < 4);
    return userTemp;
}


void listarUsuarios(stCelda adl[], int val, char archivo[]){
    system("cls");
    int opcion;

    // variables filtro

    int filtroActivado = 0;
    int filtrosAplicados[4] = {0,0,0,0};
    stUsuario userFiltro;

    userFiltro.genero = ' ';
    strcpy(userFiltro.pais,"");
    userFiltro.eliminado = 0;
    userFiltro.anioNacimiento = 0;
    // fin variables filtro

    do{
        mostrarListadoUsuarios(archivo,filtroActivado,filtrosAplicados,userFiltro);
        gotoxy(0,3);
        opcion=mostrarMenuListadoU();
        system("cls");
        switch(opcion){
            case 0:
                modificarUsuario(adl, val, archivo);
                system("cls");
                break;
            case 1:
                userFiltro = filtroDeUsuarios(userFiltro, filtrosAplicados, &filtroActivado);
                break;
        }
    }while((opcion<2)/*&&(cant!=-1)*/);
}

//------------------------------------------------------------------------------------------------------------------------------------
//                                                    Modificar usuario
//------------------------------------------------------------------------------------------------------------------------------------

stUsuario buscarUsuarioArchivo(char DB_usuarios[], int id){

    FILE* arch = fopen(DB_usuarios, "rb");
    stUsuario user;
    fseek(arch, (sizeof(stUsuario)* (id-1)), SEEK_SET);
    fread(&user, sizeof(stUsuario), 1, arch);
    fclose(arch);
    return user;
}

void modificarEnArchivo(stUsuario usuario,char DB_usuarios[]){

    FILE* arch = fopen(DB_usuarios, "r+b");

    fseek(arch, (sizeof(stUsuario) * (usuario.id - 1)), SEEK_SET);
    fwrite(&usuario,sizeof(stUsuario),1,arch);
    fclose(arch);
}

void modificarUsuario(stCelda adl[], int val, char DB_usuarios[]){

    char pass[max_pass+1];
    int opcion, id, index, cantUsuarios;
    stUsuario user;
    FILE* arch = fopen(DB_usuarios,"rb");

    system("cls");
    mostrarIngresarID();
    scanf("%i",&id);
    hidecursor(0);

    cantUsuarios = cantidadRegistros(arch,sizeof(stUsuario));
    fclose(arch);

    if ( (id <= cantUsuarios) && (id > 0) ){

        user = buscarUsuarioArchivo(DB_usuarios, id);

        do{
            system("cls");
            desencriptarPass(user.vectorKey,user.pass,pass);
            gotoxy(0,7);
            printf("       Nombre       : %s\n",user.nombre);
            printf("      Password      : %s\n",pass);
            printf("        Anio        : %i\n",user.anioNacimiento);
            printf("        Pais        : %s\n",user.pais);
            printf("       Genero       : %c\n",user.genero);
            printf("       Admin        : %i (1-Si/0-No)\n",user.admin);
            printf("      Eliminado     : %i (1-Si/0-No)\n",user.eliminado);
            printf("       SALIR        ");
            opcion = mostrarModificarUsuario();
            switch (opcion){
                case 0:
                    editarNombre(&user,DB_usuarios);
                    break;
                case 1:
                    editarPass(&user,pass);
                    break;
                case 2:
                    editarAnio(&user);
                    break;
                case 3:
                    editarPais(&user);
                    break;
                case 4:
                    editarGenero(&user);
                    break;
                case 5:
                    editarAdmin(&user);
                    break;
                case 6:
                    editarEliminado(&user);
                    break;
            }
        }while(opcion!=7);

        index = buscarUsuarioPorId(adl,val, id);

        if ( index > -1){
             adl[index].usr = user;
        }
        modificarEnArchivo(user, DB_usuarios);

    }else{
        system("cls");
        printf("Usuario no encontrado.");
        siguiente();
    }

}

//--- Editar nombre

void editarNombre(stUsuario* user, char DB_usuarios[]){

    int existe;
    char nuevo_nombre[string_max];

    do{
        system("cls");
        printf("MODIFICAR NOMBRE DE USUARIO\n\n");
        printf("Valor actual: %s\n",user->nombre);
        printf("Nuevo valor: ");
        gets(nuevo_nombre);
        existe = verificarDatos(DB_usuarios,nuevo_nombre);
        if(existe){
            printf("Ese nombre ya esta en uso.");
            siguiente();
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
    }while((aux!=1) && (aux!=0));
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
    }while((aux!=1) && (aux!=0));
    user->admin = aux;
}

//-----------------------------------------------------------------------------------------------------------------------------------------
//                                                      Filtrar usuarios
//-----------------------------------------------------------------------------------------------------------------------------------------


///------------------------------------------------------------------------------------------------------------------------------
///                                                     Generar Back up
///------------------------------------------------------------------------------------------------------------------------------

void generarBackUpU(char archivoOriginal[]){
    char ruta[40] ={"backUp\\usuarios\\"};
    FILE* archO = fopen(archivoOriginal, "rb");
    strcat(ruta,archivoOriginal);
    FILE* archBU = NULL;
    archBU = fopen(ruta, "ab");
    stUsuario temp;
    while(fread(&temp, sizeof(stUsuario), 1, archO)>0){
        fwrite(&temp, sizeof(stUsuario), 1, archBU);
    }
    fclose(archO);
    fclose(archBU);
}

void recuperarDatosUsuarios(char archivo[]){

    char ruta[]={"backUp\\usuarios\\"};
    strcat(ruta,archivo);
    system("cls");

    FILE* BA=fopen(ruta,"rb");
    FILE* arch=fopen(archivo,"wb");
    stUsuario temp;

    while(fread(&temp,sizeof(stUsuario),1,BA)>0){
        fwrite(&temp,sizeof(stUsuario),1,arch);
    }
    fclose(BA);
    fclose(arch);
}

void menuBackUpU(char DB_usuarios[]){

    int opc=mostrarBackUp();
    switch (opc){
    case 0:
        generarBackUpU(DB_usuarios);
        system("cls");
        printf("Back up generado correctamente en carpeta backUp.");
        presionarContinuar();
        siguiente();
        break;
    case 1:
        recuperarDatosUsuarios(DB_usuarios);
        system("cls");
        printf("Se han restaurado los datos desde la base de datos.");
        presionarContinuar();
        siguiente();
        break;

    }
    return;
}


///************************************************************************************************************************************************************
///                                                  Gestion de peliculas
///************************************************************************************************************************************************************

void gestionPeliculas(nodoArbol* arbol, char DB_peliculas[]){

    int opcion_elegida;

    do{
        opcion_elegida=mostrarGestionPeliculas();
        switch(opcion_elegida){
            case 0:
                menuAltaPeliculas(arbol, DB_peliculas);
                break;
            case 1:
                bajaPelicula(DB_peliculas, arbol);
                break;
            case 2:
                listarPeliculas(arbol, DB_peliculas);
                break;
            case 3:
                system("cls");
                menuBackUpP(DB_peliculas, arbol);
                break;
        }
    }while(opcion_elegida!=4);

}

///---------------------------------------------------------------------------------------------------------------------------------------
///                                               Menu alta peliculas
///---------------------------------------------------------------------------------------------------------------------------------------

void menuAltaPeliculas(nodoArbol* arbol, char DB_peliculas[]){

    int opcion_elegida;
    do{
        opcion_elegida=mostrarDarAltaPeliculas();
        switch(opcion_elegida){
            case 0:
                ingresarPeliculas(DB_peliculas, arbol);
                break;
            case 1:
                habilitarPelicula(arbol, DB_peliculas);
                break;
        }
    }while(opcion_elegida!=2);
    return;

}

///----------------------------------------------------------------------------------------------------------------------------------
///                                                    Listado de peliculas
///----------------------------------------------------------------------------------------------------------------------------------

stPelicula filtroDePeliculas(stPelicula peliculaTemp, int filtrosAplicados[], int* filtroActivado){

    int opc;

    do{
        system("cls");
        gotoxy(21,7);printf(": %i",peliculaTemp.anio);
        gotoxy(21,8);printf(": %s",peliculaTemp.genero);
        gotoxy(21,9);printf(": %s",peliculaTemp.director);
        gotoxy(21,10);printf(": %i",peliculaTemp.eliminado);
        opc = mostrarFiltroDePeliculas();
        system("cls");
        switch (opc){
            case 0:
                completarCampoInt(&peliculaTemp.anio,&filtrosAplicados[0]);
                break;
            case 1:
                completarCampoString(&peliculaTemp.genero,&filtrosAplicados[1]);
                break;
            case 2:
                completarCampoString(&peliculaTemp.director,&filtrosAplicados[2]);
                break;
            case 3:
                completarCampoBin(&peliculaTemp.eliminado,&filtrosAplicados[3]);
                break;
            case 4:
                *filtroActivado = 1;
                system("cls");
                gotoxy(50,10);
                printf("Filtros activados!");
                presionarContinuar();
                siguiente();
                break;
            case 5:
                peliculaTemp.anio = 0;
                strcpy(peliculaTemp.genero,"");
                strcpy(peliculaTemp.director,"");
                peliculaTemp.eliminado = 0;

                filtrosAplicados[0] = 0;
                filtrosAplicados[1] = 0;
                filtrosAplicados[2] = 0;
                filtrosAplicados[3] = 0;

                *filtroActivado = 0;
                system("cls");
                gotoxy(50,10);
                printf("Filtros desactivados!");
                presionarContinuar();
                siguiente();
                break;
        }

    }while( opc < 4);
    return peliculaTemp;
}

void listarPeliculas(nodoArbol* arbol, char DB_peliculas[]){

    system("cls");
    int opcion;

    // variables filtro

    int filtroActivado = 0;
    int filtrosAplicados[4] ={0,0,0,0};
    stPelicula peliculaFiltro;

    peliculaFiltro.anio = 0;
    strcpy(peliculaFiltro.genero,"");
    strcpy(peliculaFiltro.director,"");
    peliculaFiltro.eliminado = 0;

    // fin variables filtro

    do{
        mostrarListadoPeliculas(DB_peliculas, filtroActivado, filtrosAplicados, peliculaFiltro);
        gotoxy(0,3);
        opcion = mostrarMenuListadoP();
        system("cls");
        switch(opcion){
            case 0:
                modificarPelicula(DB_peliculas,arbol);
                break;
            case 1:
                peliculaFiltro = filtroDePeliculas(peliculaFiltro, filtrosAplicados,&filtroActivado);
                break;
        }
    }while(opcion<2);
}

///---------------------------------------------------------------------------------------------------------------------------------------
///                                                 Generar Back up peliculas
///---------------------------------------------------------------------------------------------------------------------------------------

// Ya hay una función dentro de la librería películas.


