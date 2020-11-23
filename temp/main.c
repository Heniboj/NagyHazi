#include <stdio.h>
#include <string.h>
#ifdef _WIN32
    #include <windows.h>
#endif

#include "datumkezeles.h"
#include "jaratkezeles.h"
#include "menu.h"

//#include "debugmalloc.h"

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
    FILE* fp;
    fp = fopen("foglalasok.txt", "r");
    Foglalas tempFoglalas;

    int i = 0;
    int foglalasokMeret = 0;
    Foglalas* foglalasok = (Foglalas*)malloc(0);
    while(fscanf(fp,"%[^#]#%[^#]#%[^#]#%d\n", tempFoglalas.azonosito, tempFoglalas.nev, tempFoglalas.ulohely, &(tempFoglalas.menu)) != EOF) {
        for(int j = 0; j < jaratokMeret; j++) {
            if(strcmp(jaratok[j].azonosito, tempFoglalas.azonosito) == 0) {
                foglalasok = jaratFoglal(jaratok, foglalasok, tempFoglalas, j, &foglalasokMeret);
            }
        }
        i++;
    }
    fclose(fp);



    /* Men� */
    menu(jaratok, &jaratokMeret, foglalasok, &foglalasokMeret);


    jaratRogzit(jaratok, jaratokMeret);

    /* Foglal�sok adatainak r�gz�t�se a foglalasok.txt f�jlba */

    fp = fopen("foglalasok.txt", "w");
    //printf("\n FADFADF %d \n",foglalasokMeret);
    for (int foglalas = 0; foglalas < foglalasokMeret; foglalas++) {
        fprintf(fp, "%s#%s#%s#%d\n", foglalasok[foglalas].azonosito, foglalasok[foglalas].nev, foglalasok[foglalas].ulohely, foglalasok[foglalas].menu);
    }
    fclose(fp);



    /* Felhaszn�lt mem�riater�letek felszabad�t�sa */
    for(int jarat = 0; jarat < jaratokMeret; jarat++) {
        free(jaratok[jarat].foglaltUlesek);
        free(jaratok[jarat].honnan);
        free(jaratok[jarat].hova);
    }
    free(jaratok);
    free(foglalasok);


    return 0;
}
