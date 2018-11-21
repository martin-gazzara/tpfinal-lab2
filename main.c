#include <stdio.h>
#include <stdlib.h>
#include "usuarios.h"
#include "grafica.h"
#include "intro.h"

int main(){

    Sleep(1000);
    hidecursor(0);
    intro_animation();
    system("cls");
    intro();
    system("cls");
    bienvenida();
    return 0;
}
