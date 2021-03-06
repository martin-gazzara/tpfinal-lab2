
#ifndef STRUCTS_H
#define STRUCTS_H


#define string_max 20
#define nombre_max 50
#define sinopsis_max 400
#define f_pass 2
#define c_pass 5
#define max_pass 10

// stUsuario
typedef struct {
        int id;
        char nombre[string_max];
        int admin;  //1 admin 0 user
        int pass[f_pass][c_pass];
        int anioNacimiento;
        char genero;
        char pais[string_max];
        int eliminado;
        int vectorKey[2];

} stUsuario;


// stPelicula
typedef struct {
    char director[string_max];
    char genero[string_max];
    char lenguaje[string_max];
    char nombre[nombre_max];
    char pais[string_max];
    char sinopsis[sinopsis_max];

    int anio;
    int eliminado;
    int id;
    int pm;
    int subtitulo;
    int valoracion;

}stPelicula;

// NodoArbol
typedef struct{
    stPelicula p;
    struct nodoArbol* izq;
    struct nodoArbol* der;
}nodoArbol;


// NodoListaPelicula
typedef struct{
    stPelicula p;
    struct nodoListaPelicula * sig;
} nodoListaPelicula;

// stCelda
typedef struct{
    stUsuario usr;
    nodoListaPelicula * listaPelis;
} stCelda;

// stPelisVistas
typedef struct{
    int idAutoincremental;
    int idUsuario;
    int idPelicula;
} stPelisVistas;

#endif // STRUCTS_H
