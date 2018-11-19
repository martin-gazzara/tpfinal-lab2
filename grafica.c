#include "grafica.h"

void intro(){
    hidecursor(0);
    Sleep(t2);
    gotoxy(42,12);printf("b");
    Sleep(t2);
    gotoxy(57,12);printf("O");
    Sleep(t2);
    gotoxy(49,12);printf("r");
    Sleep(t2);
    gotoxy(56,12);printf("E");
    Sleep(t2);
    gotoxy(47,12);printf("s");
    Sleep(t2);
    gotoxy(48,12);printf("e");
    Sleep(t2);
    gotoxy(45,12);printf("i");
    Sleep(t2);
    gotoxy(50,12);printf("t");
    Sleep(t2);
    gotoxy(51,12);printf("i");
    Sleep(t2);
    gotoxy(52,12);printf("o");
    Sleep(t2);
    gotoxy(59,12);printf("Y");
    Sleep(t2);
    gotoxy(54,12);printf("T");
    Sleep(t2);
    gotoxy(53,12);printf("n");
    Sleep(t2);
    gotoxy(46,12);printf("n");
    Sleep(t2);
    gotoxy(43,12);printf("y");
    Sleep(t2);
    gotoxy(58,12);printf("R");
    Sleep(t2);
    gotoxy(55,12);printf("H");
    Sleep(t2);
    Sleep(t2*10);

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
    gotoxy(54,12);printf("T");
    Sleep(t2/2);
    gotoxy(55,12);printf("H");
    Sleep(t2/2);
    gotoxy(56,12);printf("E");
    Sleep(t2/2);
    gotoxy(57,12);printf("O");
    Sleep(t2/2);
    gotoxy(58,12);printf("R");
    Sleep(t2/2);
    gotoxy(59,12);printf("Y");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),8);
    Sleep(t2*40);
}

void reiniciarColores(int colores[],int num){
    int i;
    for(i=0;i<num;i++){
        colores[i]=8;
    }
    return;
}

void mostrarOpcionesV(char opciones[][21],int colores[],int num){
    int i;
    for(i=0;i<num;i++){
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colores[i]);
        printf("%s",opciones[i]);
        gotoxy(whereX()-20,(whereY()+1));
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
    }
    return;
}

int elegirOpcionV(char formato[],char opc[][21],int num){
    int i=0;
    int aux=12;
    int colores[num];
    while(aux!=13){
        if (strcmp(formato,"centrado")==0){
            gotoxy(41,7);
        }else{
            gotoxy(0,7);
        }
        reiniciarColores(colores,num);
        colores[i]=115;
        mostrarOpcionesV(opc,colores,num);
        do{
            fflush(stdin);
            aux=getch();
        }while((aux!=72)&&(aux!=80)&&(aux!=13));
        switch (aux){
         case 72:
             if(i>0){
                i--;
             }
            break;
         case 80:
             if(i<(num-1)){
                i++;
             }
            break;
        }
    }
    return i;
}

void mostrarOpcionesH(char opciones[][21],int colores[],int num){
    int i;
    for(i=0;i<num;i++){
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colores[i]);
        printf("%s",opciones[i]);
        gotoxy(whereX(),whereY());
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
    }
    return;
}

int elegirOpcionH(char formato[],char opc[][21],int num){
    int i=0;
    int aux=12;
    int colores[num];
    while(aux!=13){
        if (strcmp(formato,"arriba")==0){
            gotoxy(5,0);
        }else{
            gotoxy(0,23);
        }
        reiniciarColores(colores,num);
        colores[i]=115;
        mostrarOpcionesH(opc,colores,num);
        do{
            fflush(stdin);
            aux=getch();
        }while((aux!=75)&&(aux!=77)&&(aux!=13));
        switch (aux){
         case 75:
             if(i>0){
                i--;
             }
            break;
         case 77:
             if(i<(num-1)){
                i++;
             }
            break;
        }
    }
    return i;
}

void pausa(){
    Sleep(1000);
    return;
}

void siguiente(){
    char aux;
    fflush(stdin);
    aux=getch();
    return;
}

void mostrarBienvenida(){
    gotoxy(36,10);
    hidecursor(0);
    printf("Bienvenido a UTNetflix");             /// Si tenemos tiempo, podriamos averiguar la posibilidad de emitir sonidos, incluso algun
    pausa();                                      /// audio, y poner con ASCII alguna imagen bonita, ASCII ART le dicen?
    return;
}

int menuPrincipal(){
    char opciones[][21]={"   Iniciar sesion  ","     Registrarse    ","        Salir       "};
    int numOpc=3;
    system("cls");
    gotoxy(41,3);
    printf("     UTNETFLIX      ");
    int eleccion=elegirOpcionV("centrado",opciones,numOpc);
    return eleccion;
}

void mostrarCrearUsuario(){
    int i;
  ///   Recuadro principal
    gotoxy(33,5);printf("%c",d_esq_si);
    for(i=0;i<34;i++){
        printf("%c",d_linea_h);
    }
    printf("%c",d_esq_sd);
    for(i=0;i<14;i++){
        gotoxy(33,6+i);printf("%c",d_linea_v);
        gotoxy(whereX()+34,whereY());printf("%c",d_linea_v);
    }

    gotoxy(33,whereY()+1);printf("%c",d_esq_ii);
    for(i=0;i<34;i++){
        printf("%c",d_linea_h);
    }
    printf("%c",d_esq_id);

///  Recuadro username

    gotoxy(35,8);printf("%c",s_esq_si);
    for(i=0;i<30;i++){
        printf("%c",s_linea_h);
    }
    printf("%c",s_esq_sd);
    gotoxy(35,9);printf("%c",s_linea_v);
    gotoxy(66,9);printf("%c",s_linea_v);
    gotoxy(35,10);printf("%c",s_esq_ii);
    for(i=0;i<30;i++){
        printf("%c",s_linea_h);
    }
    printf("%c",s_esq_id);


///  Recuadro pass 1

    gotoxy(35,12);printf("%c",s_esq_si);
    for(i=0;i<30;i++){
        printf("%c",s_linea_h);
    }
    printf("%c",s_esq_sd);
    gotoxy(35,13);printf("%c",s_linea_v);
    gotoxy(66,13);printf("%c",s_linea_v);
    gotoxy(35,14);printf("%c",s_esq_ii);
    for(i=0;i<30;i++){
        printf("%c",s_linea_h);
    }
    printf("%c",s_esq_id);

///  Recuadro pass 2

    gotoxy(35,16);printf("%c",s_esq_si);
    for(i=0;i<30;i++){
        printf("%c",s_linea_h);
    }
    printf("%c",s_esq_sd);
    gotoxy(35,17);printf("%c",s_linea_v);
    gotoxy(66,17);printf("%c",s_linea_v);
    gotoxy(35,18);printf("%c",s_esq_ii);
    for(i=0;i<30;i++){
        printf("%c",s_linea_h);
    }
    printf("%c",s_esq_id);
    gotoxy(45,6);printf("REGISTRARSE");
    gotoxy(36,9);printf("Su usuario:");
    gotoxy(36,13);printf("Ingrese password:");
    gotoxy(36,17);printf("Vuelva a ingresarla:");
    presionarEsc();
}

void mostrarPedirInformacion(){
    int i;
  ///   Recuadro principal
    gotoxy(33,5);printf("%c",d_esq_si);
    for(i=0;i<34;i++){
        printf("%c",d_linea_h);
    }
    printf("%c",d_esq_sd);
    for(i=0;i<14;i++){
        gotoxy(33,6+i);printf("%c",d_linea_v);
        gotoxy(whereX()+34,whereY());printf("%c",d_linea_v);
    }

    gotoxy(33,whereY()+1);printf("%c",d_esq_ii);
    for(i=0;i<34;i++){
        printf("%c",d_linea_h);
    }
    printf("%c",d_esq_id);

///  Recuadro username

    gotoxy(35,8);printf("%c",s_esq_si);
    for(i=0;i<30;i++){
        printf("%c",s_linea_h);
    }
    printf("%c",s_esq_sd);
    gotoxy(35,9);printf("%c",s_linea_v);
    gotoxy(66,9);printf("%c",s_linea_v);
    gotoxy(35,10);printf("%c",s_esq_ii);
    for(i=0;i<30;i++){
        printf("%c",s_linea_h);
    }
    printf("%c",s_esq_id);


///  Recuadro pass 1

    gotoxy(35,12);printf("%c",s_esq_si);
    for(i=0;i<30;i++){
        printf("%c",s_linea_h);
    }
    printf("%c",s_esq_sd);
    gotoxy(35,13);printf("%c",s_linea_v);
    gotoxy(66,13);printf("%c",s_linea_v);
    gotoxy(35,14);printf("%c",s_esq_ii);
    for(i=0;i<30;i++){
        printf("%c",s_linea_h);
    }
    printf("%c",s_esq_id);

///  Recuadro pass 2

    gotoxy(35,16);printf("%c",s_esq_si);
    for(i=0;i<30;i++){
        printf("%c",s_linea_h);
    }
    printf("%c",s_esq_sd);
    gotoxy(35,17);printf("%c",s_linea_v);
    gotoxy(66,17);printf("%c",s_linea_v);
    gotoxy(35,18);printf("%c",s_esq_ii);
    for(i=0;i<30;i++){
        printf("%c",s_linea_h);
    }
    printf("%c",s_esq_id);
    gotoxy(37,6);printf("Ingrese informacion personal");
    gotoxy(36,9);printf("Anio de nacimiento:");
    gotoxy(36,13);printf("Pais:");
    gotoxy(36,17);printf("Genero(m/f):");
}

void mostrarIniciarSesion(){
    int i;
    system("cls");
/// Recuadro principal
    gotoxy(26,5);printf("%c",d_esq_si);
    for(i=0;i<43;i++){
        printf("%c",d_linea_h);
    }
    printf("%c",d_esq_sd);
    for(i=0;i<9;i++){
        gotoxy(26,6+i);printf("%c                                           %c",d_linea_v,d_linea_v);
    }
    gotoxy(26,whereY()+1);printf("%c",d_esq_ii);
    for(i=0;i<43;i++){
        printf("%c",d_linea_h);
    }
    printf("%c",d_esq_id);

/// Recuadros usuario
    gotoxy(28,8);printf("%c",s_esq_si);
    for(i=0;i<39;i++){
        printf("%c",s_linea_h);
    }
    printf("%c",s_esq_sd);
    gotoxy(28,9);printf("%c                                       %c",s_linea_v,s_linea_v);
    gotoxy(28,10);printf("%c",s_esq_ii);
    for(i=0;i<39;i++){
        printf("%c",s_linea_h);
    }
    printf("%c",s_esq_id);

///  Recuadro password
    gotoxy(28,12);printf("%c",s_esq_si);
    for(i=0;i<39;i++){
        printf("%c",s_linea_h);
    }
    printf("%c",s_esq_sd);
    gotoxy(28,13);printf("%c                                       %c",s_linea_v,s_linea_v);
    gotoxy(28,14);printf("%c",s_esq_ii);
    for(i=0;i<39;i++){
        printf("%c",s_linea_h);
    }
    printf("%c",s_esq_id);

/// Contenido
    gotoxy(40,6);
    printf("INICIAR SESION");
    gotoxy(30,9);
    printf("Usuario:");
    gotoxy(30,13);
    printf("Password:");
    presionarEsc();
    gotoxy(38,9);
    return;
}

void insertarTexto(char formato[],char texto[]){
    char aux[sinopsis_max];
    strcpy(aux,texto);
    int cantLetras=strlen(aux);
    int i=0,j,limite;  // Limite impide que se pongan sinopsis largas dentro del recuadro
    if (strcmp(formato,"titulo")==0){
        limite=nombre_max; // Maxima cantidad de caracteres permitidos en el titulo de la pelicula
        for(i=0;i<cantLetras;i++){
            aux[i]=toupper(aux[i]);
        }
    }else{
        limite=177;
    }
    i=0;
    while((i<cantLetras)&&(i<limite)){
        printf("%c",aux[i]);
        i++;
        if((i%30)==0){
            gotoxy(whereX()-30,whereY()+1);
        }
    }
    if(i==limite){
        printf("...");
    }
    return;
}

void generarRecuadro(stPelicula peli){
    int i,x_aux,y_aux;

    printf("%c",s_esq_si);
    for(i=0;i<30;i++){
        printf("%c",s_linea_h);
    }
    printf("%c",s_esq_sd);
    for(i=0;i<14;i++){
        gotoxy(whereX()-32,whereY()+1);
        printf("%c",s_linea_v);
        gotoxy(whereX()+30,whereY());
        printf("%c",s_linea_v);
    }
    gotoxy(whereX()-32,whereY()+1);
    printf("%c",s_esq_ii);
    for(i=0;i<30;i++){
        printf("%c",s_linea_h);
    }
    printf("%c",s_esq_id);
    gotoxy(whereX()-31,whereY()-12);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),232);
    printf("UTNetflix te recomienda       ");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),8);
    gotoxy(whereX()-30,whereY()+1);
    x_aux=whereX();
    y_aux=whereY();
    printf("ID: %i | Valoracion: %i",peli.id,peli.valoracion);
    gotoxy(x_aux,y_aux+2);
    insertarTexto("titulo",peli.nombre);
    gotoxy(x_aux,y_aux+5);
    insertarTexto("sinopsis",peli.sinopsis);
    return;
}

void mostrarRecomendadas(stPelicula recom[]){
    gotoxy(2,7);
    printf("Notamos que te gustan mucho");
    gotoxy(2,8);
    printf("las de %s",recom[0].genero);
    gotoxy(1,6);
    generarRecuadro(recom[0]);
    gotoxy(35,7);
    printf("Agregamos una nueva pelicula a");
    gotoxy(35,8);
    printf("nuestra plataforma");
    gotoxy(34,6);
    generarRecuadro(recom[1]);
    gotoxy(68,7);
    printf("Nuestra plataforma cuenta con");
    gotoxy(68,8);
    printf("las peliculas mas valoradas");
    gotoxy(67,6);
    generarRecuadro(recom[2]);
}

int mostrarMenuUsuario(char nombreUsuario[],stPelicula recom[]){
    int i,eleccion;

    system("cls");
    gotoxy(1,1);
    printf("Hola, %s!",nombreUsuario);
    gotoxy(1,2);
    printf("%c",d_esq_si);
    for(i=0;i<98;i++){
        printf("%c",d_linea_h);
    }
    printf("%c",d_esq_sd);
    gotoxy(1,3);
    printf("%c RECOMENDADAS",d_linea_v);
    for(i=0;i<85;i++){
        printf("%c",espacio);
    }
    printf("%c",d_linea_v);
    gotoxy(1,4);
    printf("%c",d_esq_ii);
    for(i=0;i<98;i++){
        printf("%c",d_linea_h);
    }
    printf("%c",d_esq_id);
    gotoxy(0,22);
    for(i=0;i<102;i++){
        printf("%c",s_linea_h);
    }
    //mostrarRecomendadas(recom);
    char opciones[][21]={"  Ver una pelicula  ","Todas las peliculas","    Ver historial   ","    Editar perfil   ","    Cerrar sesion   "};
    int numOpc=5;
    eleccion=elegirOpcionH("abajo",opciones,numOpc);
    return eleccion;
}

int mostrarElegirPelicula(){
    char opciones[][21]={"    Elegir por ID   ","  Elegir por nombre ","        Salir       "};
    int numOpc=3;
    int eleccion;
    eleccion=elegirOpcionV("centrado",opciones,numOpc);
    return eleccion;
}

void mostrarIngresarID(){
    int i;
    hidecursor(1);
    gotoxy(41,5);
    printf("%c",d_esq_si);
    for(i=0;i<15;i++){
        printf("%c",d_linea_h);
    }
    printf("%c",d_esq_sd);
    for(i=0;i<4;i++){
        gotoxy(41,whereY()+1);
        printf("%c               %c",d_linea_v,d_linea_v);
    }
    gotoxy(41,whereY()+1);
    printf("%c",d_esq_ii);
    for(i=0;i<15;i++){
        printf("%c",d_linea_h);
    }
    printf("%c",d_esq_id);
    gotoxy(43,6);
    printf("Ingrese un ID");
    gotoxy(45,8);
    printf("ID: ");
}

void mostrarIngresarNombre(){
    int i;

    gotoxy(20,7);
    printf("%c",d_esq_si);
    for(i=0;i<57;i++){
        printf("%c",d_linea_h);
    }
    printf("%c",d_esq_sd);
    for(i=0;i<3;i++){
        gotoxy(20,whereY()+1);
        printf("%c                                                         %c",d_linea_v,d_linea_v);
    }
    gotoxy(20,whereY()+1);
    printf("%c",d_esq_ii);
    for(i=0;i<57;i++){
        printf("%c",d_linea_h);
    }
    printf("%c",d_esq_id);
    gotoxy(40,8);
    printf("Ingrese un nombre");
    gotoxy(21,10);
    printf("Nombre:");
    return;
}

int mostrarVerPelicula(){
    char opciones[][21]={"    Ver pelicula    ","     Buscar otra    ","        Salir       "};
    int numOpc=3;
    int eleccion;
    eleccion=elegirOpcionH("abajo",opciones,numOpc);
    return eleccion;

}

int mostrarMenuHistorial(){
    char opciones[][21]={"  Borrar historial  ","        Salir       "};
    int numOpc=2;
    int eleccion;
    eleccion=elegirOpcionH("arriba",opciones,numOpc);
    return eleccion;
}

int mostrarEditarPerfil(char nombreUser[],int id){
    char opciones[][21]={"      Password      ","        Anio        ","       Genero       ","        Pais        ","        Salir       "};
    int eleccion,numOpc=5;
    gotoxy(1,1);
    printf("Editar perfil - %s (%i)",nombreUser,id);
    eleccion=elegirOpcionV("borde",opciones,numOpc);
    return eleccion;
}

int mostrarMenuAdmin(){
    system("cls");
    char opciones[][21]={"  Gestion Usuarios  ","  Gestion Peliculas ","   Cerrar sesion   "};
    int numOpc=3;
    gotoxy(1,1);
    printf("Bienvenido!");
    gotoxy(39,5);
    printf("TAREAS DE ADMINISTRADOR");
    int eleccion=elegirOpcionV("centrado",opciones,numOpc);
    return eleccion;
}

int mostrarGestionUsuarios(){
    system("cls");
    char opciones[][21]={"     Dar de alta    ","     Dar de baja    ","       Listado      ","       Back Up      ","        Atras       "};
    int numOpc=5, eleccion;
    gotoxy(41,5);
    printf("  GESTION DE USUARIOS");
    eleccion=elegirOpcionV("centrado",opciones,numOpc);
    return eleccion;
}

int mostrarBackUp(){
    char opciones[][21]={"   Crear back up    ","  Restaurar datos   ","       Salir        "};
    int numOpc=3,eleccion;
    gotoxy(47,5);
    printf("Back up");
    eleccion=elegirOpcionV("centrado",opciones,numOpc);
    return eleccion;
}

int mostrarGestionPeliculas(){
    system("cls");
    char opciones[][21]={"     Dar de alta    ","     Dar de baja    ","       Listado      ","       Back Up      ","        Atras       "};
    int numOpc=5, eleccion;
    gotoxy(41,5);
    printf("  GESTION DE PELICULAS");
    eleccion=elegirOpcionV("centrado",opciones,numOpc);
    return eleccion;
    return;
}

int mostrarMenuListadoDisp(){
    char opciones[][21]={"    Mas detalles   ","       Filtrar      ","        Salir       "};
    int numOpc=3;
    int eleccion;
    gotoxy(0,0);printf(" MENU ");
    eleccion=elegirOpcionH("arriba",opciones,numOpc);
    return eleccion;
}

int mostrarMenuListadoU(){
    gotoxy(0,0);
    printf("MENU");
    char opciones[][21]={" Modificar usuario  ","       Filtrar      ","        Salir       "};
    int numOpc=3,eleccion;
    eleccion=elegirOpcionH("arriba",opciones,numOpc);
    return eleccion;
}

int mostrarMenuListadoP(){
    gotoxy(0,0);
    printf("MENU");
    char opciones[][21]={" Modificar pelicula ","       Filtrar      ","        Salir       "};
    int numOpc=3,eleccion;
    eleccion=elegirOpcionH("arriba",opciones,numOpc);
    return eleccion;
}

int mostrarMenuFiltroDisp(){
    char opciones[][21]={"   Aplicar filtros  ","        Salir       ","       Nombre       ","      Director      ","        Anio        ","       Genero       ","      Lenguaje      ","        Pais        ","         PM         ","     Subtitulado    ","     Valoracion     "};
    int numOpc=11,eleccion;
    eleccion=elegirOpcionV("borde",opciones,numOpc);
    return eleccion;
}

int mostrarMenuFiltro(){
    char opciones[][21]={"   Aplicar filtros  ","        Salir       ","       Nombre       ","      Director      ","        Anio        ","       Genero       ","      Lenguaje      ","        Pais        ","      Eliminado     ","         PM         ","     Subtitulado    ","     Valoracion     "};
    int numOpc=12,eleccion;
    eleccion=elegirOpcionV("borde",opciones,numOpc);
    return eleccion;
}

int mostrarDarAltaPeliculas(){
    char opciones[][21]={"  Ingresar pelicula "," Habilitar pelicula ","        Atras       "};
    int numOpc=3;
    int eleccion;
    system("cls");
    gotoxy(41,5);
    printf("     DAR DE ALTA");
    eleccion=elegirOpcionV("centrado",opciones,numOpc);
    return eleccion;
}

int mostrarDarAltaUsuarios(){
    char opciones[][21]={"  Ingresar usuario  ","  Habilitar usuario ","        Atras       "};
    int numOpc=3;
    system("cls");
    gotoxy(41,5);
    printf("     DAR DE ALTA");
    int eleccion=elegirOpcionV("centrado",opciones,numOpc);
    return eleccion;
}

int mostrarModificarUsuario(){

    char opciones[][21] = {"       Nombre       ","      Password      ","        Anio        ","        Pais        ","       Genero       ","       Admin        ","      Eliminado     ","       SALIR        "};
    int eleccion,numOpc = 8;
    gotoxy(1,1);printf("Modificar usuario");
    eleccion=elegirOpcionV("borde",opciones,numOpc);
    return eleccion;
}

void cerrarPrograma(){
    system("cls");
    hidecursor(0);
    gotoxy(38,11);
    printf("Gracias por usar UTNETFLIX!");
    pausa();
    return;
}

void mensaje_passIncorrecto(){
    gotoxy(40,15);
    printf("Contrasaeña incorrecta");
    return;
}

void mostrarBajaUsuario(char nombre[]){
    system("cls");
    gotoxy(46,7);
    printf("El usuario");
    gotoxy(47,9);
    printf("%s",nombre);
    gotoxy(41,11);
    printf("ha sido dado de baja.");
    /*presionarContinuar();
    siguiente();*/
}

void mostrarBajaPelicula(char nombre[]){
    system("cls");
    gotoxy(46,7);
    printf("La pelicula");
    gotoxy(47,9);
    printf("%s",nombre);
    gotoxy(41,11);
    printf("ha sido dada de baja.");
    presionarContinuar();
    siguiente();
    return;
}

void mostrarAltaUsuario(char nombre[]){
    system("cls");
    gotoxy(46,7);
    printf("El usuario");
    gotoxy(47,9);
    printf("%s",nombre);
    gotoxy(41,11);
    printf("ha sido dado de alta.");
    presionarContinuar();
    siguiente();
    return;
}

void mostrarAltaPelicula(char nombre[]){
    system("cls");
    gotoxy(46,7);
    printf("La pelicula");
    gotoxy(47,9);
    printf("%s",nombre);
    gotoxy(41,11);
    printf("ha sido dada de alta.");
    presionarContinuar();
    siguiente();
    return;
}

int mostrarListarPorP(){
    char opciones[][21]={"      Titulo      ","       Genero       ","        Salir       "};
    int numOpc=3,eleccion;
    system("cls");
    gotoxy(39,5);
    printf("Listar usando criterio:");
    eleccion=elegirOpcionV("centrado",opciones,numOpc);
    return eleccion;

}

int mostrarListarPorU(){
    char opciones[][21]={"       Nombre       "," Cantidad de vistas ","        Salir       "};
    int numOpc=3,eleccion;
    system("cls");
    gotoxy(39,5);
    printf("Listar usando criterio:");
    eleccion=elegirOpcionV("centrado",opciones,numOpc);
    return eleccion;
}

void presionarEsc(){
    gotoxy(79,24);
    printf("Presione ESC para salir");
    return;
}

void presionarNum(){
    gotoxy(79,23);
    printf("Presione -1 para salir");
    return;
}

void presionarContinuar(){
    gotoxy(69,23);
    printf("Presione una tecla para continuar");
}

void proximamente(){
    system("cls");
    gotoxy(44,8);
    printf("PROXIMAMENTE!");
    gotoxy(33,10);
    printf("Estamos construyendo esta seccion.");
}

void mostrarFormularioPeliculas(){
    int i;

/// Recuadro principal

    system("cls");
    hidecursor(0);
    gotoxy(3,1);
    printf("%c",d_esq_si);
    for(i=0;i<91;i++){
        printf("%c",d_linea_h);
    }
    printf("%c",d_esq_sd);
    for(i=0;i<25;i++){
        gotoxy(whereX()-93,whereY()+1);
        printf("%c",d_linea_v);
        gotoxy(whereX()+91,whereY());
        printf("%c",d_linea_v);
    }
    gotoxy(whereX()-93,whereY()+1);
    printf("%c",d_esq_ii);
    for(i=0;i<91;i++){
        printf("%c",d_linea_h);
    }
    printf("%c",d_esq_id);

/// Recuadro nombre pelicula

    gotoxy(5,3);
    printf("%c",s_esq_si);
    for(i=0;i<57;i++){
        printf("%c",s_linea_h);
    }
    printf("%c",s_esq_sd);
    gotoxy(whereX()-59,whereY()+1);
    printf("%c",s_linea_v);
    gotoxy(whereX()+57,whereY());
    printf("%c",s_linea_v);
    gotoxy(whereX()-59,whereY()+1);
    printf("%c",s_esq_ii);
    for(i=0;i<57;i++){
        printf("%c",s_linea_h);
    }
    printf("%c",s_esq_id);
    gotoxy(6,4);
    printf("Nombre: ");

///  Recuadro anio

    gotoxy(65,3);
    printf("%c",s_esq_si);
    for(i=0;i<10;i++){
        printf("%c",s_linea_h);
    }
    printf("%c",s_esq_sd);
    gotoxy(whereX()-12,whereY()+1);
    printf("%c",s_linea_v);
    gotoxy(whereX()+10,whereY());
    printf("%c",s_linea_v);
    gotoxy(whereX()-12,whereY()+1);
    printf("%c",s_esq_ii);
    for(i=0;i<10;i++){
        printf("%c",s_linea_h);
    }
    printf("%c",s_esq_id);
    gotoxy(66,4);
    printf("Anio: ");

/// Recuadro ID

    gotoxy(78,3);
    printf("%c",s_esq_si);
    for(i=0;i<14;i++){
        printf("%c",s_linea_h);
    }
    printf("%c",s_esq_sd);
    gotoxy(whereX()-16,whereY()+1);
    printf("%c",s_linea_v);
    gotoxy(whereX()+14,whereY());
    printf("%c",s_linea_v);
    gotoxy(whereX()-16,whereY()+1);
    printf("%c",s_esq_ii);
    for(i=0;i<14;i++){
        printf("%c",s_linea_h);
    }
    printf("%c",s_esq_id);
    gotoxy(79,4);
    printf("ID: ");

///  Recuadro Director

    gotoxy(5,7);
    printf("%c",s_esq_si);
    for(i=0;i<41;i++){
        printf("%c",s_linea_h);
    }
    printf("%c",s_esq_sd);
    gotoxy(whereX()-43,whereY()+1);
    printf("%c",s_linea_v);
    gotoxy(whereX()+41,whereY());
    printf("%c",s_linea_v);
    gotoxy(whereX()-43,whereY()+1);
    printf("%c",s_esq_ii);
    for(i=0;i<41;i++){
        printf("%c",s_linea_h);
    }
    printf("%c",s_esq_id);
    gotoxy(6,8);
    printf("Director: ");

///  Recuadro Genero

    gotoxy(51,7);
    printf("%c",s_esq_si);
    for(i=0;i<41;i++){
        printf("%c",s_linea_h);
    }
    printf("%c",s_esq_sd);
    gotoxy(whereX()-43,whereY()+1);
    printf("%c",s_linea_v);
    gotoxy(whereX()+41,whereY());
    printf("%c",s_linea_v);
    gotoxy(whereX()-43,whereY()+1);
    printf("%c",s_esq_ii);
    for(i=0;i<41;i++){
        printf("%c",s_linea_h);
    }
    printf("%c",s_esq_id);
    gotoxy(52,8);
    printf("Genero: ");

/// Recuadro Lenguaje

    gotoxy(5,11);
    printf("%c",s_esq_si);
    for(i=0;i<41;i++){
        printf("%c",s_linea_h);
    }
    printf("%c",s_esq_sd);
    gotoxy(whereX()-43,whereY()+1);
    printf("%c",s_linea_v);
    gotoxy(whereX()+41,whereY());
    printf("%c",s_linea_v);
    gotoxy(whereX()-43,whereY()+1);
    printf("%c",s_esq_ii);
    for(i=0;i<41;i++){
        printf("%c",s_linea_h);
    }
    printf("%c",s_esq_id);
    gotoxy(6,12);
    printf("Lenguaje: ");

///  Recuadro publico

    gotoxy(51,11);
    printf("%c",s_esq_si);
    for(i=0;i<41;i++){
        printf("%c",s_linea_h);
    }
    printf("%c",s_esq_sd);
    gotoxy(whereX()-43,whereY()+1);
    printf("%c",s_linea_v);
    gotoxy(whereX()+41,whereY());
    printf("%c",s_linea_v);
    gotoxy(whereX()-43,whereY()+1);
    printf("%c",s_esq_ii);
    for(i=0;i<41;i++){
        printf("%c",s_linea_h);
    }
    printf("%c",s_esq_id);
    gotoxy(52,12);
    printf("Publico(0:ATP, 13:+13, 16:+16, 18:+18):");

///  Recuadro valoracion

    gotoxy(5,15);
    printf("%c",s_esq_si);
    for(i=0;i<16;i++){
        printf("%c",s_linea_h);
    }
    printf("%c",s_esq_sd);
    gotoxy(whereX()-18,whereY()+1);
    printf("%c",s_linea_v);
    gotoxy(whereX()+16,whereY());
    printf("%c",s_linea_v);
    gotoxy(whereX()-18,whereY()+1);
    printf("%c",s_esq_ii);
    for(i=0;i<16;i++){
        printf("%c",s_linea_h);
    }
    printf("%c",s_esq_id);
    gotoxy(6,16);
    printf("Valoracion:");

///  Recuadro pais

    gotoxy(27,15);
    printf("%c",s_esq_si);
    for(i=0;i<32;i++){
        printf("%c",s_linea_h);
    }
    printf("%c",s_esq_sd);
    gotoxy(whereX()-34,whereY()+1);
    printf("%c",s_linea_v);
    gotoxy(whereX()+32,whereY());
    printf("%c",s_linea_v);
    gotoxy(whereX()-34,whereY()+1);
    printf("%c",s_esq_ii);
    for(i=0;i<32;i++){
        printf("%c",s_linea_h);
    }
    printf("%c",s_esq_id);
    gotoxy(28,16);
    printf("Pais:");

///  Recuadro subtitulos

    gotoxy(65,15);
    printf("%c",s_esq_si);
    for(i=0;i<27;i++){
        printf("%c",s_linea_h);
    }
    printf("%c",s_esq_sd);
    gotoxy(whereX()-29,whereY()+1);
    printf("%c",s_linea_v);
    gotoxy(whereX()+27,whereY());
    printf("%c",s_linea_v);
    gotoxy(whereX()-29,whereY()+1);
    printf("%c",s_esq_ii);
    for(i=0;i<27;i++){
        printf("%c",s_linea_h);
    }
    printf("%c",s_esq_id);
    gotoxy(66,16);
    printf("Subtitulos (0:No,1:Si):");

/// Recuadro Sinopsis

    gotoxy(5,19);
    printf("%c",s_esq_si);
    for(i=0;i<87;i++){
        printf("%c",s_linea_h);
    }
    printf("%c",s_esq_sd);
    for(i=0;i<5;i++){
        gotoxy(whereX()-89,whereY()+1);
        printf("%c",s_linea_v);
        gotoxy(whereX()+87,whereY());
        printf("%c",s_linea_v);
    }
    gotoxy(whereX()-89,whereY()+1);
    printf("%c",s_esq_ii);
    for(i=0;i<87;i++){
        printf("%c",s_linea_h);
    }
    printf("%c",s_esq_id);
    gotoxy(6,20);
    printf("Sinopsis:");

/// fin
    gotoxy(0,0);
    hidecursor(1);
}


int mostrarModificarPelicula(){

    char opciones[][21]={"       Nombre       ","      Director      ","        Anio        ","       Genero       ","      Lenguaje      ","        Pais        ","         PM         ","     Subtitulado    ","     Valoracion     ","      Sinopsis      ","        Salir       "};
    int numOpc=11,eleccion;
    gotoxy(1,1);printf("Modificar película");
    eleccion=elegirOpcionV("borde",opciones,numOpc);
    return eleccion;

}

///******* PARA FILTRAR PELICULAS

int evaluarPelicula(int filtrosAplicados[], stPelicula peliculaFiltro, stPelicula temp){

    int ok = 0;

    if(
        ((filtrosAplicados[0] && (peliculaFiltro.anio == temp.anio))||(!filtrosAplicados[0])) &&
        ((filtrosAplicados[1] && (strcmp(peliculaFiltro.genero,temp.genero) == 0))||(!filtrosAplicados[1])) &&
        ((filtrosAplicados[2] && (strcmp(peliculaFiltro.director,temp.director)== 0))||(!filtrosAplicados[2])) &&
        ((filtrosAplicados[3] && (peliculaFiltro.eliminado == temp.eliminado))||(!filtrosAplicados[3]))
    ){
        ok = 1;
    }else{
        ok = 0;
    }
    return ok;
}

void mostrarListadoPeliculas(char archivo[],int filtroActivado, int filtrosAplicados[], stPelicula peliculaFiltro){

    FILE* arch = fopen(archivo,"rb");
    stPelicula temp;
    int line = 5;
    int mostrar;

    system("cls");
    gotoxy(1,4);printf("ID");
    gotoxy(17,4);printf("NOMBRE");
    gotoxy(45,4);printf("ANIO");
    gotoxy(54,4);printf("GENERO");
    gotoxy(86,4);printf("DIRECTOR");
    gotoxy(110,4);printf("ELIM");
    printf("\n");

    while( (fread(&temp,sizeof(stPelicula),1,arch)) > 0  ){

        if(filtroActivado){
            mostrar = evaluarPelicula(filtrosAplicados, peliculaFiltro, temp);
        }else{
            mostrar = 1;
        }

        if (mostrar){
            gotoxy(1,line);printf("%i",temp.id);
            gotoxy(5,line);printf("%s",temp.nombre);
            gotoxy(45,line);printf("%i", temp.anio);
            gotoxy(54,line);printf("%s",temp.genero);
            gotoxy(84,line);printf("%s",temp.director);
            gotoxy(112,line);printf("%o",temp.eliminado);
            line++;
        }
    }

    fclose(arch);

}

int mostrarFiltroDePeliculas(){
    char opciones[][21]={"        Anio        ","       Genero       ","      Director      ","      Eliminado     ","   Aplicar filtros  ","   Quitar filtros   ","        Salir       "};
    int eleccion,numOpc=7;
    gotoxy(1,1);
    printf("Filtros a aplicar");
    eleccion=elegirOpcionV("borde",opciones,numOpc);
    return eleccion;
}

///*****  PARA FITLRAR USUARIOS

int evaluarUsuario(int filtrosAplicados[], stUsuario userFiltro, stUsuario temp){

    int ok = 0;

    if(
        ((filtrosAplicados[0] && (userFiltro.genero == temp.genero))||(!filtrosAplicados[0])) &&
        ((filtrosAplicados[1] && (strcmp(userFiltro.pais,temp.pais) == 0))||(!filtrosAplicados[1])) &&
        ((filtrosAplicados[2] && (userFiltro.eliminado == temp.eliminado))||(!filtrosAplicados[2])) &&
        ((filtrosAplicados[3] && (userFiltro.anioNacimiento == temp.anioNacimiento))||(!filtrosAplicados[3]))
    ){
        ok = 1;
    }else{
        ok = 0;
    }
    return ok;
}

void mostrarListadoUsuarios(char archivo[],int filtroActivado, int filtrosAplicados[], stUsuario userFiltro){

    FILE* arch = fopen(archivo,"rb");
    stUsuario temp;
    int line = 5;
    int mostrar;
/*
    system("cls");
                printf("flag mostrarUsuarios - filtro.\n");
                printf("%c\n",userFiltro.genero);
                printf("%s\n",userFiltro.pais);
                printf("%i\n",userFiltro.eliminado);
                printf("%i\n",userFiltro.anioNacimiento);
                printf("Arreglo de filtros: ");
                printf("%i %i %i %i",filtros[0],filtros[1],filtros[2],filtros[3]);
                siguiente();
*/
    system("cls");
    gotoxy(1,4);printf("ID");
    gotoxy(17,4);printf("NOMBRE");
    gotoxy(45,4);printf("ANIO");
    gotoxy(54,4);printf("GENERO");
    gotoxy(67,4);printf("PAIS");
    gotoxy(96,4);printf("ELIM");
    printf("\n");

    while( (fread(&temp,sizeof(stUsuario),1,arch)) > 0  ){

        if(filtroActivado){
            mostrar = evaluarUsuario(filtrosAplicados, userFiltro, temp);
        }else{
            mostrar = 1;
        }

        if (mostrar){
            gotoxy(1,line);printf("%i",temp.id);
            gotoxy(5,line);printf("%s",temp.nombre);
            gotoxy(45,line);printf("%i", temp.anioNacimiento);
            gotoxy(56,line);printf("%c",temp.genero);
            gotoxy(65,line);printf("%s",temp.pais);
            gotoxy(98,line);printf("%o",temp.eliminado);
            line++;
        }
    }

    fclose(arch);

}

int mostrarFiltroDeUsuarios(){
    char opciones[][21]={"       Genero       ","        Pais        ","      Eliminado     ","        Anio        ","   Aplicar filtros  ","   Quitar filtros   ","        Salir       "};
    int eleccion,numOpc=7;
    gotoxy(1,1);
    printf("Filtros a aplicar");
    eleccion=elegirOpcionV("borde",opciones,numOpc);
    return eleccion;
}
