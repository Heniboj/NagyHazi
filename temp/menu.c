#include "menu.h"

void menu(Jarat* jaratok, int* jaratokMeret, Foglalas* foglalasok, int* foglalasokMeret) {
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
            char *honnan = beolvas(stdin, '\n');
            printf("Hova k�v�n utazni?");
            char *hova= beolvas(stdin, '\n');

            /* D�tumok beolvas�sa */
            printf("Mi legyen az indul�si d�tum?");
            Datum datum_kezdo = datumBeolvas();
            while(hibaKeres(datum_kezdo)) {
                printf("Hib�s D�tum form�tum, k�rlek pr�b�ld �jra\n");
                printf("Mi legyen az indul�si d�tum?");
                datum_kezdo = datumBeolvas();
            }
            printf("Mi legyen a v�gs� d�tum?");
            Datum datum_vegso = datumBeolvas();
            while(hibaKeres(datum_vegso)) {
                printf("Hib�s D�tum form�tum, k�rlek pr�b�ld �jra\n");
                printf("Mi legyen a v�gs� d�tum?");
                datum_vegso = datumBeolvas();
            }

            /* J�rat keres�se */
            jaratKeres(jaratok, *jaratokMeret, honnan, hova, datum_kezdo, datum_vegso);
        }

            /* Rep�l�jegy foglal�sa men�pont */
        else if(menupont == 2) {
            printf("Mi a j�rat azonos�t�ja?");
            char *jaratszam = (char*)malloc(7 * sizeof(char));
            getchar();
            gets(jaratszam);


            int jarat = 0;

            while (jarat < *jaratokMeret) {
                if (strcmp(jaratok[jarat].azonosito, jaratszam) == 0) {
                    char *nev = (char*)malloc(50 * sizeof(char));

                    printf("Milyen n�vre legyen a foglal�s?");
                    gets(nev);

                    printf("K�rlek v�lassz �l�helyet!\n");
                    foglaltsagiTerkep(jaratszam);
                    printf("V�lasztott �l�hely:");

                    char *ulohely = (char*)malloc(3 * sizeof(char));
                    getchar();
                    scanf("%s", ulohely);
                    printf("V�lassz az al�bbi men�k k�z�l:\n");
                    printf("1.: Norm�l\n");
                    printf("2.: Vega\n");
                    printf("3.: Lakt�zmentes\n");
                    printf("V�lasztott �tel sorsz�ma:");

                    int menu;
                    scanf("%d", &menu);
                    Foglalas foglalas;
                    strcpy(foglalas.azonosito, jaratszam);
                    free(jaratszam);
                    strcpy(foglalas.nev, nev);
                    free(nev);
                    strcpy(foglalas.ulohely, ulohely);
                    free(ulohely);
                    foglalas.menu = menu;

                    foglalasok = jaratFoglal(jaratok, foglalasok, foglalas, jarat, foglalasokMeret);
                }
                jarat++;
            }
        }

            /* Foglal�s t�rl�se men�pont */
        else if(menupont == 3) {
            char *nev = (char*)malloc(50 * sizeof(char));
            printf("Milyen n�ven van a foglal�s?");
            getchar();
            gets(nev);
            foglalasok = jaratTorol(foglalasok, nev, foglalasokMeret);
            free(nev);
        }

            /* �sszes�t�s men�pont */
        else if(menupont == 4) {
            printf("�sszes�t�s.\n");
            printf("J�ratsz�m    Norm�l    Veg�n    Lakt�zmentes\n");
            Osszesit(jaratok, foglalasok, *jaratokMeret, *foglalasokMeret);
        }

            /* Minden m�s �rt�k az 5-�t kiv�ve => nem l�tez� men�pont */
        else if(menupont != 5) {
            printf("Nem l�tez� men�pont.\n");
        }

    }
}
