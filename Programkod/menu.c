#include "debugmalloc.h"
#include "validacio.h"
#include "jaratkezeles.h"
#include "menu.h"
#include <stdio.h>

void menu(Jarat* jaratok, int* jaratokMeret, Foglalas** foglalasok, int* foglalasokMeret) {
    int menupont = 0;
    while(menupont != 5) {
        printf("V�lassz egyet az al�bbi men�pontok k�z�l:\n");
        printf("1.: J�rat keres�se\n");
        printf("2.: Rep�l�jegy foglal�sa\n");
        printf("3.: Foglal�s t�rl�se\n");
        printf("4.: �sszes�t�s\n");
        printf("5.: Kil�p�s\n");
        scanf("%d",&menupont);

        /* J�rat keres�se men�pont */
        if(menupont == 1) {
            /* �tic�lok beolvas�sa */
            getchar();
            printf("Honnan k�v�n utazni?");
            char* honnan = inputValidacio(beolvas(stdin, '\n'));
            printf("Hova k�v�n utazni?");
            char* hova= inputValidacio(beolvas(stdin, '\n'));
            /* D�tumok beolvas�sa */
            printf("Mi legyen az indul�si d�tum?");
            Datum datum_kezdo = datumBeolvas();
            while(datumValidacio(datum_kezdo)) {
                printf("Hib�s D�tum form�tum, k�rlek pr�b�ld �jra\n");
                printf("Mi legyen az indul�si d�tum?");
                datum_kezdo = datumBeolvas();
            }
            printf("Mi legyen a v�gs� d�tum?");
            Datum datum_vegso = datumBeolvas();
            while(datumValidacio(datum_vegso)) {
                printf("Hib�s D�tum form�tum, k�rlek pr�b�ld �jra\n");
                printf("Mi legyen a v�gs� d�tum?");
                datum_vegso = datumBeolvas();
            }

            /* J�rat keres�se */
            jaratKeres(jaratok, *jaratokMeret, honnan, hova, datum_kezdo, datum_vegso);
            free(honnan);
            free(hova);
        }

        /* Rep�l�jegy foglal�sa men�pont */
        else if(menupont == 2) {
            Foglalas foglalas;
            printf("Mi a j�rat azonos�t�ja?");
            scanf("%s",foglalas.azonosito);

            int jarat = 0;

            while (jarat < *jaratokMeret) {
                if (strcmp(jaratok[jarat].azonosito, foglalas.azonosito) == 0) {
                    printf("Milyen n�vre legyen a foglal�s?");
                    getchar();
                    foglalas.nev = inputValidacio(beolvas(stdin, '\n'));

                    printf("K�rlek v�lassz �l�helyet!\n");
                    foglaltsagiTerkep(jaratok, *jaratokMeret, foglalas.azonosito);
                    printf("V�lasztott �l�hely:");
                    scanf("%s", foglalas.ulohely);

                    while(ulohelyValidacio(ulohelySzam(foglalas.ulohely), jaratok[jarat].foglaltUlesek, (90 - jaratok[jarat].ferohely))) {
                        printf("Ez az �l�hely m�r foglalt,, k�rlek �rd be �jra.\n");
                        scanf("%s", foglalas.ulohely);
                    }

                    printf("V�lassz az al�bbi men�k k�z�l:\n");
                    printf("1.: Norm�l\n");
                    printf("2.: Vega\n");
                    printf("3.: Lakt�zmentes\n");
                    printf("V�lasztott �tel sorsz�ma:");

                    scanf("%d", &(foglalas.menu));
                    while(foglalas.menu != normal && foglalas.menu != vega && foglalas.menu != laktozmentes) {
                        printf("Nem l�tez� men�, k�rlek �rd be �jra.\n");
                        scanf("%d", &(foglalas.menu));
                    }

                    *foglalasok = jaratFoglal(jaratok, *foglalasok, foglalas, jarat, foglalasokMeret);
                    break;
                }
                jarat++;
            }
            if(jarat == *jaratokMeret) {
                printf("Hib�s vagy nem l�tez� azonos�t�.\n");
            }
        }

        /* Foglal�s t�rl�se men�pont */
        else if(menupont == 3) {
            char *nev;
            printf("Milyen n�ven van a foglal�s?");
            getchar();
            nev = inputValidacio(beolvas(stdin, '\n'));
            *foglalasok = jaratTorol(*foglalasok, nev, foglalasokMeret);
            free(nev);
        }

        /* �sszes�t�s men�pont */
        else if(menupont == 4) {
            printf("�sszes�t�s.\n");
            printf("J�ratsz�m\tNorm�l\t\tVeg�n\t""Lakt�zmentes\n");
            Osszesit(jaratok, *foglalasok, *jaratokMeret, *foglalasokMeret);
        }

        /* Minden m�s �rt�k az 5-�t kiv�ve => nem l�tez� men�pont */
        else if(menupont != 5) {
            printf("Nem l�tez� men�pont.\n");
        }
    }
}