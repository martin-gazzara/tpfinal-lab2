#include "pelicula.h"

//Calcula la cantidad de Registros que tiene un Archivo.
int cantidadRegistros(FILE* arch, size_t tamanioDeTipo) {
    int aux;
    fseek(arch, 0, SEEK_END);
    aux=(int)ftell(arch)/tamanioDeTipo;
    rewind(arch);
    return aux;
}

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

//Rearmar arbol
void rearmararbol(nodoArbol** arbol) {
    *arbol = inicArbol(); // ?????????????
    //recorrer el archivo de forma recursiva y cargar el arbol

    // completar logica/////////////////////////////////////////////////////////
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
        if(cantAltasSeguidas != 3) {
            cantAltasSeguidas++;
        } else {
            rearmararbol();
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

///  Generar Arbol
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
    int cantPeliculas = cantidadRegistros(arch,sizeof(stPelicula)) /// OBTENER CANTIDAD DE PELICULAS EN EL REGISTRO
    arbol = leerMitad(arbol,arch,0,cantPeliculas);

    return arbol;
}
