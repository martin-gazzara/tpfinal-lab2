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
