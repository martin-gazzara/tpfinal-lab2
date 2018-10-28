#define string_max 30
#define nombre_max 60
#define sinopsis_max 400
#define f_pass 2
#define c_pass 5

// stUsuario
typedef struct {
        int id;
        char nombre[string_max];
        int admin;
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
