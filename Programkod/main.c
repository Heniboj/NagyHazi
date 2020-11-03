#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#ifdef _WIN32
    #include <windows.h>
#endif

//#include "debugmalloc.h"

typedef struct Datum {
    int ev;
    int honap;
    int nap;
}Datum;

typedef struct Jarat {
  char azonosito[7];
  Datum datum;
  char honnan[50];
  char hova[50];
  int ferohely;
  int *foglaltUlesek;
}Jarat;

typedef enum Menu{
    normal,
    vega,
    laktozmentes
}Menu;

typedef struct Foglalas {
    char azonosito[7];
    char nev[50];
    int ulohely;
    int menu;
}Foglalas;

Datum datumBeolvas(void) {
    Datum datum;
    char datumstring[11];
    scanf("%s", datumstring);
    datum.ev = atoi(strtok(datumstring, "/"));
    datum.honap = atoi(strtok(NULL, "/"));
    datum.nap = atoi(strtok(NULL, "/"));
    return datum;
}

bool datumOsszehasonlit(Datum datum1, Datum datum2) {
    if(datum1.ev < datum2.ev) {
        return false;
    } else if(datum1.ev > datum2.ev) {
        return true;
    }

    if(datum1.ev == datum2.ev) {
        if(datum1.honap < datum2.honap) {
            return false;
        }else if(datum1.honap > datum2.honap) {
            return true;
        }else if(datum1.nap < datum2.nap) {
            return false;
        }else if(datum1.nap > datum2.nap) {
            return true;
        }
    }
    return true;
}

bool hibaKeres(Datum datum) {
    if(datum.ev < 2020) {
        return true;
    } else if(datum.honap < 1 || datum.honap > 12) {
        return true;
    } else if(datum.nap < 1 || datum.nap > 31) {
        return true;
    }
    return false;
}


void jaratKeres(Jarat *jaratok, int meret, char *honnan, char *hova, Datum datum_kezdo, Datum datum_vegso) {
    int talalatok = 0;
    for(int i = 0; i < meret;i++) {
        if(strcmp(jaratok[i].honnan, honnan) == 0 && strcmp(jaratok[i].hova, hova) == 0) {
            if(datumOsszehasonlit(jaratok[i].datum, datum_kezdo)) {
                if(!datumOsszehasonlit(jaratok[i].datum, datum_vegso)) {
                    printf("%s %d %d %d %s %s %d\n", jaratok[i].azonosito, jaratok[i].datum.ev, jaratok[i].datum.honap, jaratok[i].datum.nap, jaratok[i].honnan, jaratok[i].hova, jaratok[i].ferohely);
                    talalatok++;
                }
            }
        }
    }
    if(talalatok == 0) {
        printf("Nem tal�lhat� j�rat a megadott keres�si felt�telek szerint.");
    }
}

void jaratFoglal(char* jaratszam) {

}


int main() {
#ifdef _WIN32
    SetConsoleCP(1250);
    SetConsoleOutputCP(1250);
#endif

    /* jaratok.txt adatainak beolvas�sa �s t�rol�sa */
    FILE* fp;
    fp = fopen("jaratok.txt", "r");
    Jarat tempJarat;

    int i = 0;
    int jaratokMeret = 1;
    Jarat* jaratok = (Jarat*)malloc(jaratokMeret * sizeof(*jaratok));

    while(fscanf(fp,"%[^#]#%d/%d/%d#%[^#]#%[^#]#%d\n", tempJarat.azonosito, &(tempJarat.datum.ev), &(tempJarat.datum.honap), &(tempJarat.datum.nap), tempJarat.honnan, tempJarat.hova, &(tempJarat.ferohely)) != EOF) {
        tempJarat.foglaltUlesek = NULL;
        jaratok = (Jarat*)realloc(jaratok, jaratokMeret * sizeof(*jaratok));
        jaratok[i] = tempJarat;
        i++;
        jaratokMeret++;
    }
    jaratokMeret--;
    fclose(fp);


    /* foglalasok.txt adatainaka beolvas�sa �s t�rol�sa */
    fp = fopen("foglalasok.txt", "r");
    Foglalas tempFoglalas;

    i = 0;
    int foglalasokMeret = 0;
    Foglalas* foglalasok = NULL;
    while(fscanf(fp,"%[^#]#%[^#]#%d#%d\n", tempFoglalas.azonosito, tempFoglalas.nev, &(tempFoglalas.ulohely), &(tempFoglalas.menu)) != EOF) {
        foglalasokMeret++;
        if(foglalasokMeret == 1) {
            foglalasok = (Foglalas*)malloc(foglalasokMeret * sizeof(*foglalasok));
        } else {
            foglalasok = (Foglalas*)realloc(foglalasok, foglalasokMeret * sizeof(*foglalasok));
        }
        foglalasok[i] = tempFoglalas;
        for(int j = 0; j < jaratokMeret; j++) {
            if(strcmp(jaratok[j].azonosito, foglalasok[i].azonosito) == 0) {
                if(jaratok[j].foglaltUlesek == NULL) {
                    jaratok[j].foglaltUlesek = (int*)malloc(((96-jaratok[j].ferohely)+1) * sizeof(int));
                } else {
                    jaratok[j].foglaltUlesek = realloc(jaratok[j].foglaltUlesek,((96-jaratok[j].ferohely)+1) * sizeof(int));
                }
                jaratok[j].ferohely--;
            }
        }
        i++;
    }
    fclose(fp);


    //printf("%s %d %d %d %s %s %d\n", jaratok[0].azonosito, jaratok[0].datum.ev, jaratok[0].datum.honap, jaratok[0].datum.nap, jaratok[0].honnan, jaratok[0].hova, jaratok[0].ferohely);










    /* Men� */

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
            fflush(stdin);
            printf("Honnan k�v�n utazni?");
            char honnan[50];
            gets(honnan);
            printf("Hova k�v�n utazni?");
            char hova[50];
            gets(hova);

            /* D�tumok beolvas�sa */
            printf("Mi legyen az indul�si d�tum?");
            Datum datum_kezdo = datumBeolvas();
            while(hibaKeres(datum_kezdo)) {
                printf("Hib�s D�tum form�tum, k�rlek pr�b�ld �jra\n");
                printf("Mi legyen az indul�si d�tum?");
                datum_kezdo = datumBeolvas();
            }
            Datum datum_vegso = datumBeolvas();
            printf("Mi legyen a v�gs� d�tum?");
            while(hibaKeres(datum_vegso)) {
                printf("Hib�s D�tum form�tum, k�rlek pr�b�ld �jra\n");
                printf("Mi legyen a v�gs� d�tum?");
                datum_vegso = datumBeolvas();
            }

            /* J�rat keres�se */
            jaratKeres(jaratok, jaratokMeret, honnan, hova, datum_kezdo, datum_vegso);
        }

        /* Rep�l�jegy foglal�sa men�pont */
        else if(menupont == 2) {
            printf("Ez a rep�l�jegy foglal�sa men�pont.\n");
        }

        /* Foglal�s t�rl�se men�pont */
        else if(menupont == 3) {
            printf("Foglal�s t�rl�se.\n");
        }

        /* �sszes�t�s men�pont */
        else if(menupont == 4) {
            printf("�sszes�t�s.\n");
        }

        /* Minden m�s �rt�k az 5-�t kiv�ve => nem l�tez� men�pont */
        else if(menupont != 5) {
            printf("Nem l�tez� men�pont.\n");
        }

    }






    free(jaratok);
    free(foglalasok);
    return 0;
}
