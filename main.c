#include <stdio.h>
#ifdef _WIN32
    #include <windows.h>
#endif

int main() {
#ifdef _WIN32
    SetConsoleCP(1250);
    SetConsoleOutputCP(1250);
#endif

    /* men� */

    printf("V�lassz egyet az al�bbi men�pontok k�z�l:\n");
    printf("1.: J�rat keres�se\n");
    printf("2.: Rep�l�jegy foglal�sa\n");
    printf("3.: Foglal�s t�rl�se\n");
    printf("4.: �sszes�t�s\n");
    printf("5.: Kil�p�s\n");








    int menupont;
    scanf("%d",&menupont);

    while(menupont != 5) {
        printf("V�lassz egyet az al�bbi men�pontok k�z�l:\n");
        printf("1.: J�rat keres�se\n");
        printf("2.: Rep�l�jegy foglal�sa\n");
        printf("3.: Foglal�s t�rl�se\n");
        printf("4.: �sszes�t�s\n");
        printf("5.: Kil�p�s\n");
        int menupont;
        scanf("%d",&menupont);
    }


    return 0;
}
