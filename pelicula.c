#include "pelicula.h"

//Calcula la cantidad de Registros que tiene un Archivo.
int cantidadRegistros(FILE* arch, size_t tamanioDeTipo) {
    int aux;
    fseek(arch, 0, SEEK_END);
    aux=(int)ftell(arch)/tamanioDeTipo;
    rewind(arch);
    return aux;
}

///***************************************************************************************************************************************
///****************************                           HABILITAR PELICULA                                 *****************************
///***************************************************************************************************************************************

//Habilita nuevamente una Película eliminada.
void habilitarPelicula(char DB_peliculas[]){
    FILE* arch;
    stPelicula temp;
    int id;
    nodoArbol* nodoNuevo;
    system("cls");
    presionarNum();
    mostrarIngresarID();
    scanf("%i",&id);
    hidecursor(0);
    if(id!=-1){
        if ((arch = fopen(DB_peliculas,"r+b"))!=NULL){
            fseek(arch, (id-1)*sizeof(stPelicula), SEEK_SET);
            fread(&temp, sizeof(stPelicula), 1, arch);
            if(temp.eliminado==1){
                temp.eliminado = 0;
                fseek(arch, (-1)*sizeof(stPelicula), SEEK_CUR);
                fwrite(&temp, sizeof(stPelicula), 1,arch);
                fclose(arch);
                nodoNuevo = crearNodo(temp);
                arbol = insertar(arbol, nodoNuevo);
                mostrarAltaPelicula(temp.nombre);
            }else{
                system("cls");
                    gotoxy(46,7);
                    printf("La pelicula");
                    gotoxy(47,9);
                    printf("%s",temp.nombre);
                    gotoxy(41,11);
                    printf("no ha sido dada de baja.");
                    presionarContinuar();
                    siguiente();
            }
        }
    }
}

///***************************************************************************************************************************************
///****************************                              BAJA PELICULA                                   *****************************
///***************************************************************************************************************************************

//Da de baja una película
void bajaPelicula(char DB_peliculas[], nodoArbol* arbol){

    stPelicula pelicula;
    FILE *arch;
    int id;
    arch=fopen(DB_peliculas,"r+b");

    system("cls");
    presionarNum();
    mostrarIngresarID();
    scanf("%i",&id);
    hidecursor(0);
    if (id!=-1){
        if(!NULL){
            while((fread(&pelicula,sizeof(stPelicula),1,arch)>0)&&(pelicula.id!=id));
            if(!feof(arch)){
                fseek(arch,(-1)*sizeof(stPelicula),SEEK_CUR);
                pelicula.eliminado=1;
                fwrite(&pelicula,sizeof(stPelicula),1,arch);
                arbol = borrarNodo(arbol, id);
                mostrarBajaPelicula(pelicula.nombre);
            }else{
                system("cls");
                gotoxy(40,10);
                printf("La pelicula no existe.");
                presionarContinuar();
                siguiente();
            }
        }
    }
    fclose(arch);
    return;
}

///***************************************************************************************************************************************
///****************************                              ALTA PELICULA                                   *****************************
///***************************************************************************************************************************************

//Verifica si una Película ya fue cargada.
int verificacionPelicula(char archivo[], char nombre[], int anio) {
    FILE* arch;
    arch = fopen(archivo, "rb");
    int flag=0;
    stPelicula peli;
    while ((fread(&peli, sizeof(stPelicula), 1, arch) > 0) && (!flag)) {
        if ((strcmpi(peli.nombre,nombre)==0) && (peli.anio == anio)) {
            flag = 1;
        }
    }
    fclose(arch);
    return flag;
}
//Verifica si el campo subtítulo es correcto.
void verificacionSub(int* valor) {
    while ((*valor > 1) || (*valor < 0)) {
        printf("Valor ingresado incorrecto. Ingrese 0 o 1\n");
        scanf("%d", valor);
    }
}

//Verifica si el PM ingresdo es correcto.
void verificacionPM(int* pm) {
    while ((*pm != 0) && (*pm != 13) && (*pm != 16) && (*pm != 18)) {
        printf("Error al ingresar pm. Los valores tienen que ser:(0: ATP, 13: +13, 16: +16, 18:+18)\n");
        scanf("%d", pm);
    }
}

//Verifica si la valoracion ingresada es correcta.
void verificacionVal(int* valoracion) {
    while ((*valoracion<0) || (*valoracion>10)) {
        printf("Error a ingresar valoracion: la valoracion es de 0-5\n");
        scanf("%d", valoracion);
    }
}

//Calcula el ID de una Película.
int calcularId(FILE* arch){
    int id;
    if(!feof(arch)){
        id = cantidadRegistros(arch, sizeof(stPelicula))+1;
    }else{
        id=1;
    }
    return id;
}

//Carga una Pelicula al Arbol/Lista
void cargarPelisArbol(nodoArbol** arbol, stPelicula peli){
    nodoArbol* nuevo = crearNodo(peli);
    *arbol = insertar(*arbol, nuevo);
}

//Pedir datos de pelicula
stPelicula pedirInfo(char nombre[], int anio){
    stPelicula peli;

    peli.eliminado = 0;
    peli.id = calcularId(arch);
    gotoxy(82,4);printf("%i",peli.id);
    strcpy(peli.nombre,nombre);
    peli.anio = anio;

    gotoxy(15,8);
    fflush(stdin);
    gets(peli.director);

    gotoxy(59,8);
    fflush(stdin);
    gets(peli.genero);

    gotoxy(15,12);
    fflush(stdin);
    gets(peli.lenguaje);

    gotoxy(91,12);
    scanf("%d", &peli.pm);
    verificacionPM(&peli.pm);

    gotoxy(17,16);
    scanf("%d", &peli.valoracion);
    verificacionVal(&peli.valoracion);

    gotoxy(33,16);
    fflush(stdin);
    gets(peli.pais);

    gotoxy(89,16);
    scanf("%d", &peli.subtitulo);
    verificacionSub(&peli.subtitulo);

    gotoxy(15,20);
    escribirSinopsis(peli.sinopsis);

    return peli;
}


//Carga una Película a un Archivo.
void cargarPelisArchivo(char archivo[], stPelicula peli){
    FILE * arch;
    stPelicula peli;
    arch = fopen(archivo, "ab");
    int val;
    val = fwrite(&peli, sizeof(stPelicula), 1, arch);
    fclose(arch);
    system("cls");
    gotoxy(38,6);
    if(val==1){
        printf("Pelicula cargada con exito\n");
    }else{
        printf("Error al cargar la pelicula\n");
    }
}

//Verifica si el usuario desea cargar otra Película.
void verificarNuevaCarga(char* control){
    printf("Desea cargar otra pelicula? s/n\n");
    fflush(stdin);
    scanf("%c", control);
}

//Ingresa una Película.
void ingresarPeliculas(char DB_peliculas[], nodoArbol** arbol){
    char nombre[nombre_max];
    int anio;
    int cantAltasSeguidas = 0;
    stPelicula p;
    system("cls");
    mostrarFormularioPeliculas();
    gotoxy(13,4);
    fflush(stdin);
    gets(nombre);
    gotoxy(71,4);
    scanf("%d", &anio);
    if (verificacionPelicula(DB_peliculas, nombre, anio) == 0) {
        p = pedirInfo(nombre, anio);
        cargarPelisArchivo(DB_peliculas, p);
        cargarPelisArbol(arbol, p);
        if(cantAltasSeguidas < 10) {
            cantAltasSeguidas++;
        } else {
            generarArbol(DB_peliculas);
            cantAltasSeguidas = 0;
        }
    } else {
        system("cls");
        gotoxy(38,6);
        printf("Error, pelicula ya cargada\n");
    }
    hidecursor(0);
    presionarContinuar();
    siguiente();
}

///***************************************************************************************************************************************
/// ****************************                          MODIFICACION PELICULA                               ****************************
///***************************************************************************************************************************************

//Modifica una película.
void modificarPelicula(char archivo[],nodoArbol* arbolPeliculas){
    int id, opcion = 0;
    FILE* arch = NULL;
    nodoArbol* nodoPelicula;

    system("cls");
    presionarNum();
    mostrarIngresarID();
    scanf("%i",&id);
    nodoPelicula = buscar(arbolPeliculas,id);
    if (nodoPelicula){
        while (opcion!=10){
            system("cls");
            opcion = mostrarModificarPelicula(pelicula);
            system("cls")
            gotoxy(0,7);
            switch (opcion){
                case 0:
                    printf("Nombre actual: %s\n",nodoPelicula->p.nombre);
                    printf("Ingrese nuevo nombre: ");
                    fflush(stdin);
                    gets(&(nodoPelicula->p.nombre));
                    break;
                case 1:
                    printf("Director actual: %s\n",nodoPelicula->p.director);
                    printf("Ingrese nuevo director: ");
                    fflush(stdin);
                    gets(&(nodoPelicula->p.director));
                    break;
                case 2:
                    printf("Anio actual: %i\n",nodoPelicula->p.anio);
                    printf("Ingrese anio nuevo: ");
                    scanf("%i",&(nodoPelicula->p.anio));
                    break;
                case 3:
                    printf("Genero actual: %s\n",nodoPelicula->p.genero);
                    printf("Ingrese nuevo genero: ");
                    fflush(stdin);
                    gets(&(nodoPelicula->p.genero));
                    break;
                case 4:
                    printf("Lenguaje actual: %s\n",nodoPelicula->p.lenguaje);
                    printf("Ingrese nuevo lenguaje: ");
                    fflush(stdin);
                    gets(&(nodoPelicula->p.lenguaje));
                    break;
                case 5:
                    printf("Pais actual: %s\n",nodoPelicula->p.pais);
                    printf("Ingrese nuevo pais: ");
                    fflush(stdin);
                    gets(&(nodoPelicula->p.pais));
                    break;
                case 6:
                    printf("PM actual: %i\n",nodoPelicula->p.pm);
                    printf("Ingrese PM nuevo: ");
                    scanf("%i",&(nodoPelicula->p.pm));
                    break;
                case 7:
                    printf("Subtitulo actual (1-Si 0-No): %i\n",nodoPelicula->p.subtitulo);
                    printf("Ingrese subtitulo nuevo: ");
                    do{
                        scanf("%i",&(nodoPelicula->p.pm));
                    }while((nodoPelicula->p.pm != 0) && (nodoPelicula->p.pm != 1));
                    break;
                case 8:
                    printf("Valoracion actual: %i\n",nodoPelicula->p.valoracion);
                    printf("Ingrese valoracion nueva: ");
                    do{
                        scanf("%i",&(nodoPelicula->p.pm));
                    }while((nodoPelicula->p.pm < 1) && (nodoPelicula->p.pm > 10));
                    break;
                case 9:
                    printf("Ingrese nueva sinopsis: \n");
                    fflush(stdin);
                    gets(&(nodoPelicula->p.sinopsis));
                    break;
            }
        }
    }else{
        printf("No se encuentra la pelicula");
        siguiente();
    }
}


///***************************************************************************************************************************************
/// ****************************                           CONSULTA PELICULA                                  ****************************
///***************************************************************************************************************************************

//Borra los datos de una pelicula
void vaciar(stPelicula* peli){
    strcpy(peli->nombre,"");
    strcpy(peli->director,"");
    strcpy(peli->genero,"");
    strcpy(peli->lenguaje,"");
    strcpy(peli->pais,"");
    strcpy(peli->sinopsis,"");
    peli->anio=0;
    peli->eliminado=0;
    peli->id=0;
    peli->pm=0;
    peli->subtitulo=0;
    peli->valoracion=0;
    return;
}

//Completa un campo bin 0 1
void completarCampoBin(int* num,int* val){
    printf("Valor actual: ");
    if (*num!=0){
        printf("Si\n");
    }else{
        printf("No\n");
    }
    printf("Valor a filtrar(2.Quitar filtro/1.Si/0.No): ");
    do{
        scanf("%i",num);
    }while((*num<0)&&(*num>2));
    if(*num==2){
        *val=0;
    }else{
        *val=1;
    }
    return;
}

//Completa un campo int
void completarCampoInt(int* num,int* val){

    printf("Valor actual: ");
    if (*num!=-1){
        printf("%i\n",*num);
    }else{
        printf("vacio\n");
    }
    printf("Valor a filtrar: ");
    scanf("%i",num);
    if (*num<0){
        *val=0;
    }else{
        *val=1;
    }
    return;
}

//Completa un campo de string
void completarCampoString(char string[],int* val){
    printf("Valor actual: ");
    if (strlen(string)>0){
        printf("%s\n",string);
    }else{
        printf("vacio\n");
    }
    printf("\nValor a filtrar: ");
    fflush(stdin);
    gets(string);
    if(strlen(string)>0){
        *val=1;
    }else{
        *val=0;
    }
    return;
}

//Filtra strings
int filtroString(char string1[],char string2[],int fil){
    int val;

    if (fil==1){
        if (strcmpi(string1,string2)==0){
            val=1;
        }else{
            val=0;
        }
    }else{
        val=1;
    }
    return val;
}

//Filtra numero
int filtroNum(int num1,int num2,int fil){
    int val;
    if (fil==1){
        if (num1==num2){
            val=1;
        }else{
            val=0;
        }
    }else{
        val=1;
    }

    return val;
}


///***************************************************************************************************************************************
///*******************************                         FILTRO PARA ADMIN                               *******************************
///***************************************************************************************************************************************


///***************************************************************************************************************************************
///*******************************                     LISTAR PELICULAS PARA ADMIN                         *******************************
///***************************************************************************************************************************************

//Lista las peliculas
void mostrarListadoP(nodoArbol* arbol, int opc, stUsuario user){
    int i=0;
    gotoxy(1,4);printf("ID");
    gotoxy(22,4);printf("NOMBRE");
    gotoxy(45,4);printf("ANIO");
    gotoxy(54,4);printf("GENERO");
    gotoxy(72,4);printf("DIRECTOR");
    gotoxy(87,4);printf("LENGUAJE");
    gotoxy(96,4);printf("ELIM");
    printf("\n");
    switch(opc){
        case 1: preorder(arbol, user);
            break;
        case 2: inorder(arbol, user);
            break;
        case 3: posorder(arbol, user);
            break;
    }
}



///***************************************************************************************************************************************
///*******************************                       FILTRO PARA USUARIOS                              *******************************
///***************************************************************************************************************************************

int filtroPeliculasDisp(nodoArbol* arbol,stPelicula arreglo[],int dim){
    stPelicula aux;
    vaciar(&aux);
    int resp=2;
    int camposFiltrados[9]={0};
    int cont=0;
    while (resp>1){
        system("cls");
        printf("Filtrar peliculas por:\n");
        gotoxy(0,7);
        printf("\n\n       Nombre       : %s\n",aux.nombre);
        printf("      Director      : %s\n",aux.director);
        printf("        Anio        : %i\n",aux.anio);
        printf("       Genero       : %s\n",aux.genero);
        printf("      Lenguaje      : %s\n",aux.lenguaje);
        printf("        Pais        : %s\n",aux.pais);
        printf("         PM         : %i\n",aux.pm);
        printf("     Subtitulado    : %i\n",aux.subtitulo);
        printf("     Valoracion     : %i\n",aux.valoracion);
        resp=mostrarMenuFiltroDisp();
        system("cls");
        switch (resp){
            case 2:
                printf("NOMBRE\n");
                completarCampoString(aux.nombre,&camposFiltrados[0]);
                break;
            case 3:
                printf("DIRECTOR\n");
                completarCampoString(aux.director,&camposFiltrados[1]);
                break;
            case 4:
                printf("ANIO\n");
                completarCampoInt(&aux.anio,&camposFiltrados[2]);
                break;
            case 5:
                printf("GENERO\n");
                completarCampoString(aux.genero,&camposFiltrados[3]);
                break;
            case 6:
                printf("LENGUAJE\n");
                completarCampoString(aux.lenguaje,&camposFiltrados[4]);
                break;
            case 7:
                printf("PAIS\n");
                completarCampoString(aux.pais,&camposFiltrados[5]);
                break;
            case 8:
                printf("PM\n");
                completarCampoInt(&aux.pm,&camposFiltrados[6]);
                break;
            case 9:
                printf("SUBTITULOS\n");
                completarCampoBin(&aux.subtitulo,&camposFiltrados[7]);
                break;
            case 10:
                printf("VALORACION\n");
                completarCampoInt(&aux.valoracion,&camposFiltrados[8]);
                break;
            case 0:
                printf("\n");
                cont=aplicarFiltrosDisp(aux,camposFiltrados,arreglo,DB_peliculas); //usar arbol, no archivo/para que usa arreglo?//////////////////////
                break;
            default:
                cont=dim;
                break;
        }
        system("cls");
    }
    return cont;
}

///***************************************************************************************************************************************
///*******************************                   LISTAR PELICULAS PARA USUARIOS                        *******************************
///***************************************************************************************************************************************

//Lista las peliculas disponibles al usuario
void mostrarListadoPDis(nodoArbol* arbol, int opc, stUsuario user){
    int i=0;
    gotoxy(1,4);printf("ID");
    gotoxy(22,4);printf("NOMBRE");
    gotoxy(45,4);printf("ANIO");
    gotoxy(54,4);printf("GENERO");
    gotoxy(72,4);printf("DIRECTOR");
    gotoxy(87,4);printf("LENGUAJE");
    printf("\n");
    switch(opc){
        case 1: preorder(arbol, user)
            break;
        case 2: inorder(arbol, user);
            break;
        case 3: posorder(arbol, user);
            break;
    }
}

//Muestra una Película.
void mostrarPelicula(stPelicula peli){
    printf("Nombre: %s\n", peli.nombre);
    printf("Anio: %d\n", peli.anio);
    printf("Director: %s\n", peli.director);
    printf("Pais: %s\n", peli.pais);
    printf("Genero: %s\n", peli.genero);
    printf("Lenguajes: %s\n", peli.lenguaje);
    if (peli.subtitulo == 1){
        printf("Subtitulos: Si\n");
    }else{
        printf("Subtitulos: No\n");
    }
    printf("PM: %d\n", peli.pm);
    printf("Sinopsis: %s\n", peli.sinopsis);
    printf("Valoracion: %d puntos\n", peli.valoracion);
    printf("------------------------------------------\n");
    return;


///***************************************************************************************************************************************
/// ****************************                             GENERAR ARBOL                                    ****************************
///***************************************************************************************************************************************

// Lee el registro del medio de un intervalo de registros del archivo de películas
nodoArbol* leerMitad(nodoArbol* arbol, FILE* arch,int desde, int hasta){

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
        fseek(arch,(index-1)*sizeof(stPelicula),SEEK_SET);
        if((fread(&pelicula,sizeof(stPelicula),1,arch)!=NULL)){
            arbol->p = pelicula;
            arbol->izq = leerMitad(arbol->izq,arch,desde,index-1);
            arbol->der = leerMitad(arbol->der,arch,index,hasta);
        }
    }
    return arbol;
}

// Funcion que retorna un arbol de peliculas.
nodoArbol* generarArbol(char DB_peliculas[]){

    FILE* arch = NULL;
    nodoArbol* arbol = inicArbol();

    arch = fopen(DB_peliculas,"rb");
    int cantPeliculas = cantidadRegistros(arch,sizeof(stPelicula));
    arbol = leerMitad(arbol,arch,0,cantPeliculas);

    return arbol;
}

///***************************************************************************************************************************************
/// ****************************                              BACK UP                                         ****************************
///***************************************************************************************************************************************

//Genera un backup del archivo peliculas
void generarBackUpP(char archivoOriginal[], nodoArbol* arbol){
    char ruta[40] ={"backUp\\peliculas\\"};
    FILE* archBU = fopen(strcat(ruta,archivoOriginal), "wb");
    guardar(archBU, arbol);
    fclose(archBU);
}

void guardar(FILE* arch, nodoArbol* arbol){
    if(arbol!=NULL){
        fwrite(&arbol->p,sizeof(stPelicula), 1, arch);
        guardar(arch, arbol->izq);
        guardar(arch, arbol->der);
    }
}

void recuperarDatosPeliculas(char archivo[], nodoArbol* arbol){
    char ruta[]={"backUp\\peliculas\\"};
    arbol = generarArbol(ruta);
    return arbol;
}

void menuBackUpP(char DB_peliculas[]){
    int opc=mostrarBackUp();
    switch (opc){
    case 0:
        generarBackUpP(DB_peliculas);
        system("cls");
        printf("Back up generado correctamente en carpeta backUp.");
        presionarContinuar();
        siguiente();
        break;
    case 1:
        recuperarDatosPeliculas(DB_peliculas);
        system("cls");
        printf("Se han restaurado los datos.");
        presionarContinuar();
        siguiente();
        break;

    }
}
