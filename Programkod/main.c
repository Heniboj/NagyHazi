#ifdef _WIN32
#include <windows.h>
#endif

#include "debugmalloc.h"
#include "datumkezeles.h"
#include "jaratkezeles.h"
#include "menu.h"
#include "rendezes.h"

int main() {
#ifdef _WIN32
    SetConsoleCP(1250);
    SetConsoleOutputCP(1250);
#endif
    /* jaratok.txt adatainak beolvas�sa �s t�rol�sa */
    int jaratokMeret = 1;
    Jarat* jaratok = (Jarat*)malloc(jaratokMeret * sizeof(*jaratok));
    jaratok = jaratokBeolvas(jaratok, &jaratokMeret);
    jaratokMeret--;

    /* foglalasok.txt adatainak beolvas�sa �s t�rol�sa */
    int foglalasokMeret = 0;
    Foglalas* foglalasok = (Foglalas*)malloc(foglalasokMeret * sizeof(Foglalas));
    foglalasok = foglalasokBeolvas(jaratok, foglalasok, &foglalasokMeret, jaratokMeret);

    /* Men� */
    menu(jaratok, &jaratokMeret, &foglalasok, &foglalasokMeret);

    /* Foglal�sok rendez�se j�ratsz�m szerint */
    foglalasok = rendezes(jaratok, jaratokMeret, foglalasok, foglalasokMeret);

    /* Adatok elment�se */
    jaratRogzit(jaratok, jaratokMeret);
    foglalasokRogzit(foglalasok, foglalasokMeret);


    /* Felhaszn�lt mem�riater�letek felszabad�t�sa */
    for(int jarat = 0; jarat < jaratokMeret; jarat++) {
        free(jaratok[jarat].foglaltUlesek);
        free(jaratok[jarat].honnan);
        free(jaratok[jarat].hova);
    }
    for(int foglalas = 0; foglalas < foglalasokMeret; foglalas++) {
        free(foglalasok[foglalas].nev);
    }
    free(jaratok);
    free(foglalasok);

    return 0;
}
