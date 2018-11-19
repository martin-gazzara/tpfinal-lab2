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
void habilitarPelicula(nodoArbol* arbol, char DB_peliculas[]){
    FILE* arch;
    stPelicula temp;
    int id;
    nodoArbol* nodo;
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
                nodo = buscar(arbol,temp.id);
                if (nodo){
                    nodo->p.eliminado = 0;
                }
                system("cls");
                gotoxy(46,7);
                printf("La pelicula");
                gotoxy(47,9);
                printf("%s",temp.nombre);
                gotoxy(41,11);
                printf("ha sido dada de alta.");
                presionarContinuar();
                siguiente();
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
int calcularId(char DB_peliculas[]){
    int id;
    FILE* arch;

    arch = fopen(DB_peliculas,"rb");

    if(!feof(arch)){
        id = cantidadRegistros(arch, sizeof(stPelicula))+1;
    }else{
        id=1;
    }
    fclose(arch);
    return id;
}

// Ingresa sinopsis de pelicula.

int escribirSinopsis(char arreglo[]){

int aux,index=0,i=0;

    while ((aux!=13)&&(aux!=27)){
        if(whereX()==93){
            gotoxy(whereX()-87,whereY()+1);
        }
        fflush(stdin);
        aux=getch();
        if ((aux!=13)&&(((aux<123)&&(aux>64))||((aux>47)&&(aux<58)))&&(i<sinopsis_max-1)){
            arreglo[i]=(char)aux;
            printf("%c",arreglo[i]);
            i++;
        }else if((aux==8)&&(i>0)){
            if(whereX()==6){
                gotoxy(whereX()+86,whereY()-1);
                printf(" ");
                gotoxy(whereX()-1,whereY());
            }else{
                gotoxy(whereX()-1,whereY());
                printf(" ");
                gotoxy(whereX()-1,whereY());
            }
            i--;
        }
    }
    arreglo[i]='\0';
    return aux;

}

//Carga una Pelicula al Arbol/Lista
void cargarPelisArbol(nodoArbol** arbol, stPelicula peli){
    nodoArbol* nuevo = crearNodo(peli);
    *arbol = insertar(*arbol, nuevo);
}

//Pedir datos de pelicula
stPelicula pedirInfo(char nombre[], int anio, char DB_peliculas[]){
    stPelicula peli;

    peli.eliminado = 0;
    peli.id = calcularId(DB_peliculas);

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
        p = pedirInfo(nombre, anio, DB_peliculas);
        cargarPelisArchivo(DB_peliculas, p);
        cargarPelisArbol(arbol, p);
        if(cantAltasSeguidas < 10) {
            cantAltasSeguidas++;
        } else {
           // arbol = generarArbol(DB_peliculas);
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

void persistirCambios(stPelicula temp, nodoArbol* arbol){

    if (arbol){
        if (arbol->p.id == temp.id){
            arbol->p = temp;
        }else{
            if (temp.id < arbol->p.id){
                persistirCambios(temp,arbol->izq);
            }else{
                persistirCambios(temp,arbol->der);
            }
        }
    }
}

void modificarCampoNombre(stPelicula* pelicula){

    gotoxy(1,5);printf("Valor actual: %s",pelicula->nombre);
    gotoxy(1,6);printf("Valor nuevo: ");
    hidecursor(1);
    fflush(stdin);
    gets(&pelicula->nombre);
    hidecursor(0);
}

void modificarCampoDirector(stPelicula* pelicula){

    gotoxy(1,5);printf("Valor actual: %s",pelicula->director);
    gotoxy(1,6);printf("Valor nuevo: ");
    hidecursor(1);
    fflush(stdin);
    gets(&pelicula->director);
    hidecursor(0);
}

void modificarCampoAnio(stPelicula* pelicula){

    gotoxy(1,5);printf("Valor actual: %i",pelicula->anio);
    gotoxy(1,6);printf("Valor nuevo: ");
    hidecursor(1);
    scanf("%i",&pelicula->anio);
    hidecursor(0);

}

void modificarCampoGenero(stPelicula* pelicula){

    gotoxy(1,5);printf("Valor actual: %s",pelicula->genero);
    gotoxy(1,6);printf("Valor nuevo: ");
    hidecursor(1);
    gets(&pelicula->genero);
    hidecursor(0);

}

void modificarCampoLenguaje(stPelicula* pelicula){

    gotoxy(1,5);printf("Valor actual: %s",pelicula->lenguaje);
    gotoxy(1,6);printf("Valor nuevo: ");
    hidecursor(1);
    gets(&pelicula->lenguaje);
    hidecursor(0);

}

void modificarCampoPais(stPelicula* pelicula){

    gotoxy(1,5);printf("Valor actual: %s",pelicula->pais);
    gotoxy(1,6);printf("Valor nuevo: ");
    hidecursor(1);
    gets(&pelicula->pais);
    hidecursor(0);

}

void modificarCampoPM(stPelicula* pelicula){

    gotoxy(1,5);printf("Valor actual: %i",pelicula->pm);
    gotoxy(1,6);printf("Valor nuevo: ");
    hidecursor(1);
    scanf("%i",&pelicula->pm);
    hidecursor(0);

}

void modificarCampoSubtitulo(stPelicula* pelicula){

    gotoxy(1,5);printf("Valor actual: %i",pelicula->subtitulo);
    gotoxy(1,6);printf("Valor nuevo(1-Si/0-No): ");
    hidecursor(1);
    scanf("%i",&pelicula->subtitulo);
    hidecursor(0);

}

void modificarCampoValoracion(stPelicula* pelicula){

    gotoxy(1,5);printf("Valor actual: %i",pelicula->valoracion);
    gotoxy(1,6);printf("Valor nuevo(10-Max/1-Min): ");
    hidecursor(1);
    scanf("%i",&pelicula->valoracion);
    hidecursor(0);

}

void modificarCampoSinopsis(stPelicula* pelicula){

    gotoxy(1,5);printf("Valor actual: %s",pelicula->sinopsis);
    printf("\nValor nuevo: ");
    hidecursor(1);
    gets(&pelicula->sinopsis);
    hidecursor(0);

}

void mostrarPeliculaAModificar(stPelicula pelicula){

    gotoxy(21,7);printf(": %s",pelicula.nombre);
    gotoxy(21,8);printf(": %s",pelicula.director);
    gotoxy(21,9);printf(": %i",pelicula.anio);
    gotoxy(21,10);printf(": %s",pelicula.genero);
    gotoxy(21,11);printf(": %s",pelicula.lenguaje);
    gotoxy(21,12);printf(": %s",pelicula.pais);
    gotoxy(21,13);printf(": %i",pelicula.pm);
    gotoxy(21,14);printf(": %i (1-Si /0-No)",pelicula.subtitulo);
    gotoxy(21,15);printf(": %i",pelicula.valoracion);
    gotoxy(21,16);printf(": Ingrese para ver el contenido");
}

//Modifica una película.
void modificarPelicula(char archivo[], nodoArbol* arbol){

    int opcion = 10,id;

    FILE* arch = fopen(archivo,"r+b");
    int cantPeliculas = cantidadRegistros(arch,sizeof(stPelicula));
    stPelicula temp;


    do{
        system("cls");
        presionarNum();
        mostrarIngresarID();
        scanf("%i",&id);
        hidecursor(0);
        if ((id<cantPeliculas) && (id > 0)){
            fseek(arch, sizeof(stPelicula)*(id-1), SEEK_SET);
            fread(&temp,sizeof(stPelicula), 1, arch);
            do{
                system("cls");
                mostrarPeliculaAModificar(temp);
                opcion = mostrarModificarPelicula();
                system("cls");
                switch (opcion){
                    case 0:
                        gotoxy(1,1);printf("Editar nombre");
                        modificarCampoNombre(&temp);
                        break;
                    case 1:
                        gotoxy(1,1);printf("Editar director");
                        modificarCampoDirector(&temp);
                        break;
                    case 2:
                        gotoxy(1,1);printf("Editar anio");
                        modificarCampoAnio(&temp);
                        break;
                    case 3:
                        gotoxy(1,1);printf("Editar genero");
                        modificarCampoGenero(&temp);
                        break;
                    case 4:
                        gotoxy(1,1);printf("Editar lenguaje");
                        modificarCampoLenguaje(&temp);
                        break;
                    case 5:
                        gotoxy(1,1);printf("Editar pais");
                        modificarCampoPais(&temp);
                        break;
                    case 6:
                        gotoxy(1,1);printf("Editar PM");
                        modificarCampoPM(&temp);
                        break;
                    case 7:
                        gotoxy(1,1);printf("Editar subtitulo");
                        modificarCampoSubtitulo(&temp);
                        break;
                    case 8:
                        gotoxy(1,1);printf("Editar valoracion");
                        modificarCampoValoracion(&temp);
                        break;
                    case 9:
                        gotoxy(1,1);printf("Editar sinopsis");
                        modificarCampoSinopsis(&temp);
                        break;

                }
            }while(opcion!=10);
            fseek(arch,sizeof(stPelicula)*(-1), SEEK_CUR);
            fwrite(&temp,sizeof(stPelicula),1,arch);

            persistirCambios(temp,arbol);

        }else{
            printf("La pelicula no existe.");
        }
    }while((id > 0) && (opcion != 10));
    fclose(arch);


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

//Completa un campo char
void completarCampoChar(char* caracter,int* val){

    printf("Valor actual: ");
    if (*caracter!=' '){
        printf("%i\n",*caracter);
    }else{
        printf("vacio\n");
    }
    printf("Valor a filtrar: ");
    fflush(stdin);
    scanf("%c",caracter);
    if (*caracter==' '){
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
    if (*num<=0){
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
        if (strcmp(string1,string2)==0){
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
/*
int aplicarFiltros(stPelicula criterio,int campFil[],stPelicula arreglo[],char DB_peliculas[]){

    FILE* arch;
    stPelicula aux;
    int a,b,c,e,d,f,g,h,i,j;
    int cont=0;
    if ((arch=fopen(DB_peliculas,"rb"))!=NULL){
        while(fread(&aux,sizeof(stPelicula),1,arch)>0){
            a=filtroString(aux.nombre,criterio.nombre,campFil[0]);b=filtroString(aux.director,criterio.director,campFil[1]);
            c=filtroNum(aux.anio,criterio.anio,campFil[2]);d=filtroString(aux.genero,criterio.genero,campFil[3]);
            e=filtroString(aux.lenguaje,criterio.lenguaje,campFil[4]);f=filtroNum(aux.pais,criterio.pais,campFil[5]);
            g=filtroNum(aux.eliminado,criterio.eliminado,campFil[6]);h=filtroNum(aux.pm,criterio.pm,campFil[7]);
            i=filtroNum(aux.subtitulo,criterio.subtitulo,campFil[8]);j=filtroNum(aux.valoracion,criterio.valoracion,campFil[9]);
            if (a&&b&&c&&d&&e&&f&&g&&h&&i&&j){
               arreglo[cont]=aux;
               cont++;
            }
        }
    }else{
        printf("Error en la apertura.");
    }
    fclose(arch);
    return cont;
}

int filtroPeliculas(char DB_peliculas[],stPelicula arreglo[]){

    stPelicula aux;
    vaciar(&aux);
    int resp=2;
    int camposFiltrados[10]={0};
    int cont=0;
    while (resp>1){
        system("cls");
        gotoxy(0,5);
        printf("Filtrar peliculas por:");
        gotoxy(0,7);
        printf("   APLICAR FILTROS  \n");
        printf("        SALIR       \n");
        printf("       Nombre        %s\n",aux.nombre);
        printf("      Director       %s\n",aux.director);
        printf("        Anio         %i\n",aux.anio);
        printf("       Genero        %s\n",aux.genero);
        printf("      Lenguaje       %s\n",aux.lenguaje);
        printf("        Pais         %s\n",aux.pais);
        printf("      Eliminado      %i\n",aux.eliminado);
        printf("         PM          %i\n",aux.pm);
        printf("     Subtitulado     %i\n",aux.subtitulo);
        printf("     Valoracion      %i\n",aux.valoracion);
        resp=mostrarMenuFiltro();
        system("cls");
        gotoxy(0,7);
        switch (resp){
            case 0:
                cont=aplicarFiltros(aux,camposFiltrados,arreglo,DB_peliculas);
                break;
            case 1:
                cont=-1;
                break;
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
                printf("ELIMINADO\n");
                completarCampoBin(&aux.eliminado,&camposFiltrados[6]);

                break;
            case 9:
                printf("PM\n");
                completarCampoInt(&aux.pm,&camposFiltrados[7]);

                break;
            case 10:
                printf("SUBTITULOS\n");
                completarCampoBin(&aux.subtitulo,&camposFiltrados[8]);
                break;
            default:
                printf("VALORACION\n");
                completarCampoInt(&aux.valoracion,&camposFiltrados[9]);
                break;
        }
        system("cls");
    }
    return cont;
}
*/
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
        case 3: postorder(arbol, user);
            break;
    }
}



///***************************************************************************************************************************************
///*******************************                       FILTRO PARA USUARIOS                              *******************************
///***************************************************************************************************************************************
/*
nodoArbol* aplicarFiltrosDisp(stPelicula criterio, int campFil[], nodoArbol* peliculasFiltradas, nodoArbol* arbol){
    int nombreValido,
        directorValido,
        anioValido,
        generoValido,
        lenguajeValido,
        paisValido,
        pmValido,
        subtituloValido,
        valoracionValido;
    int cont=0;
    while(arbol){
        nombreValido=filtroString(arbol->p.nombre,criterio.nombre,campFil[0]);
        directorValido=filtroString(arbol->p.director,criterio.director,campFil[1]);
        anioValido=filtroNum(arbol->p.anio,criterio.anio,campFil[2]);
        generoValido=filtroString(arbol->p.genero,criterio.genero,campFil[3]);
        lenguajeValido=filtroString(arbol->p.lenguaje,criterio.lenguaje,campFil[4]);
        paisValido=filtroNum(arbol->p.pais,criterio.pais,campFil[5]);
        pmValido=filtroNum(arbol->p.pm,criterio.pm,campFil[7]);
        subtituloValido=filtroNum(arbol->p.subtitulo,criterio.subtitulo,campFil[8]);
        valoracionValido=filtroNum(arbol->p.valoracion,criterio.valoracion,campFil[9]);

        if (nombreValido &&
            directorValido &&
            anioValido &&
            generoValido &&
            lenguajeValido &&
            paisValido &&
            eliminadoValido &&
            pmValido &&
            subtituloValido &&
            valoracionValido){
               nodo = crearNodo(arbol->p);
               peliculasFiltradas = insertar(peliculasFiltradas, nodo);
        }
        aplicarFiltros(criterio, campFil, peliculasFiltradas, arbol->izq);
        aplicarFiltros(criterio, campFil, peliculasFiltradas, arbol->der);
    }
    return peliculasFiltradas;
}

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
                //cont = aplicarFiltrosDisp(aux,camposFiltrados,arreglo,DB_peliculas); //usar arbol, no archivo/para que usa arreglo?//////////////////////
                break;
            default:
                cont=dim;
                break;
        }
        system("cls");
    }
    return cont;
}
*/
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
        case 1: preorder(arbol, user);
            break;
        case 2: inorder(arbol, user);
            break;
        case 3: postorder(arbol, user);
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

}

//Encuentra el menor de los nombres de películas.
int encontrarMenor(stPelicula arr[], int cant, int posIni){
    int menor = posIni;
    int i;

    for(i = posIni + 1; i < cant; i++){
        if(strcmp(arr[menor].nombre, arr[i].nombre)>0){
            menor = i;
        }
    }
    return menor;
}

//Ordena un arreglo por Título.
void ordenarTitulos(stPelicula arr[], int cant){
    int i=0;
    while(i < cant){
        int menor = encontrarMenor(arr, cant, i);
        stPelicula aux = arr[menor];
        arr[menor] = arr[i];
        arr[i] = aux;
        i++;
    }
}

//Insertar una película en orden por Género.
void insertarPelicula(stPelicula peliculas[], int pos, stPelicula peli) {
    while ((pos >= 0) && ((strcmp(peli.genero, peliculas[pos].genero)) < 0)){
        peliculas[pos+1] = peliculas[pos];
        pos--;
    }
    peliculas[pos+1] = peli;
}

//Ordena un arreglo por Género.
void ordenarGeneros(stPelicula peliculas[], int val) {
    nodoArbol* arbolGeneros = inicArbol();
    int pos = 0;
    while (pos < val) {
        insertarPelicula(peliculas, pos, peliculas[pos + 1]);
        pos++;
    }
}

//Ordena películas por Título o por Género.
int ordenarPeliculas(stPelicula arregloPeliculas[],int dim){
    int num;
    num=mostrarListarPorP();
    system("cls");
    switch(num){
        case 0:
          ordenarTitulos(arregloPeliculas, dim);
            break;
        case 1:
          ordenarGeneros(arregloPeliculas, (dim-1));
            break;
    }
    return num;
}

/*
////SOLO ESTA FUNCION SE VA A LLAMAR DESDE ALGUN MENU, EL RESTO SE LLAMAN INTERNAMENTE/
//Genera un listado de las películas
void listarPeliculas(char archivo[]){
    system("cls");
    int numOpc=3;
    int opcion;
    FILE* arch;
    arch = fopen(archivo, "rb");
    int dim,dimFiltro,d;

    dim = cantidadRegistros(arch, sizeof(stPelicula));
    rewind(arch);
    stPelicula arregloPeliculas[dim];
    pasarArreglo(arch,arregloPeliculas,dim);
    fclose(arch);
    d=ordenarPeliculas(arregloPeliculas,dim);
    if (d!=2){
        do{
            mostrarListadoP(arregloPeliculas,dim);
            gotoxy(0,3);
            opcion=mostrarMenuListado();
            switch(opcion){
            case 0:
                modificarPelicula(archivo,arregloPeliculas,dim);
                system("cls");
                break;
            case 1:
                dim=filtroPeliculas(archivo,arregloPeliculas);
                break;
            }
        }while((opcion<2)&&(dim!=-1));
    }
 }
*/
///***************************************************************************************************************************************
/// ****************************                              BACK UP                                         ****************************
///***************************************************************************************************************************************

//Genera un backup del archivo peliculas
void generarBackUpP(char archivoOriginal[], nodoArbol* arbol){
    char ruta[40] ={"backUp\\peliculas\\"};
    FILE* archBU = fopen(strcat(ruta,archivoOriginal), "wb");
    guardarP(archBU, arbol);
    fclose(archBU);
}

void guardarP(FILE* arch, nodoArbol* arbol){
    if(arbol!=NULL){
        fwrite(&arbol->p,sizeof(stPelicula), 1, arch);
        guardarP(arch, arbol->izq);
        guardarP(arch, arbol->der);
    }
}

void recuperarDatosPeliculas(char archivo[], nodoArbol* arbol){
    char ruta[]={"backUp\\peliculas\\"};
//    arbol = generarArbol(ruta);
    return arbol;
}

void menuBackUpP(char DB_peliculas[],nodoArbol* arbol){

    int opc=mostrarBackUp();
    switch (opc){
        case 0:
            generarBackUpP(DB_peliculas, arbol);
            system("cls");
            printf("Back up generado correctamente en carpeta backUp.");
            presionarContinuar();
            siguiente();
            break;
        case 1:
            recuperarDatosPeliculas(DB_peliculas, arbol);
            system("cls");
            printf("Se han restaurado los datos.");
            presionarContinuar();
            siguiente();
            break;
    }
}
/*
void listarPeliculasDisponibles(nodoArbol* arbol, char archivo[], stPelicula arregloPeliculas[], int dim){
    system("cls");
    int dimFiltro,numOpc=3,opcion;
    stPelicula resultBusqueda;
    do{
        gotoxy(0,3);
        mostrarListadoPDis(arbol);
        opcion=mostrarMenuListadoDisp();
        switch(opcion){
            case 0:
                resultBusqueda=buscarPelicula(archivo)
                system("cls");
                mostrarPelicula(resultBusqueda);
                presionarContinuar();
                siguiente();
                system("cls");
                break;
            case 1:
                dim=filtroPeliculasDisp(arbol,arregloPeliculas,dim);
                if(dim>0){
                    mostrarListadoPelis(arregloPeliculas,dim);
                }
                break;
        }

    }while((opcion<2));
    return;
}
*/
void mostrarListadoPelis(stPelicula peli, int dim){
    int i = 0;
    gotoxy(1,4);printf("ID");
    gotoxy(22,4);printf("NOMBRE");
    gotoxy(45,4);printf("ANIO");
    gotoxy(54,4);printf("GENERO");
    gotoxy(72,4);printf("DIRECTOR");
    gotoxy(87,4);printf("LENGUAJE");
    printf("\n");
    while(i<dim){
        mostrarPeliDisp(peli);
        i++;
    }
}
/*
stPelicula buscarPelicula(char DB_peliculas[]){

    stPelicula pelicula;
    int buscarId,opcion,esc;
    char buscarNombre[nombre_max];
    FILE* arch;

    arch=fopen(DB_peliculas,"r+b");
    system("cls");
    opcion=mostrarElegirPelicula();
    switch(opcion){
        case 0:
            system("cls");
            presionarNum();
            mostrarIngresarID();
            scanf("%i",&buscarId);
            if(buscarId!=-1){
            while((fread(&pelicula,sizeof(stPelicula),1,arch)>0)&&(pelicula.id!=buscarId));
            if((pelicula.id!=buscarId)||(pelicula.eliminado==1)){
                pelicula.id=0;
            }
            }else{
                pelicula.id=-1;
            }
            break;
        case 1:
            system("cls");
            presionarEsc();
            mostrarIngresarNombre();
            esc=escribirNombre(buscarNombre);
            if (esc!=27){
            while((fread(&pelicula,sizeof(stPelicula),1,arch)>0)&&(strcmp(pelicula.nombre,buscarNombre)!=0));
            if(strcmp(pelicula.nombre,buscarNombre)!=0){
                pelicula.id=0;
            }
            }else{
                pelicula.id=-1;
            }
            break;
        case 2:
            pelicula.id=-1;
            break;
    }
    hidecursor(0);
    return pelicula;
}

*/
