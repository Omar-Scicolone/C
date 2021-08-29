#include <stdio.h>
#include <stdlib.h>

void stampaCodifica (void *p, int size, int bigEndian);

int main()
{
    int ai;
    float af;
    double ad;
    long double ald;
    unsigned char number[4];

    int sizeAi = sizeof(ai);
    int sizeAf = sizeof(af);
    int sizeAd = sizeof(ad);
    int sizeAld = sizeof(ald);
    int bigEndian = 0;



    printf("Dimensione degli int = %d byte e %d bit\n", sizeAi, sizeAi*8);
    printf("Dimensione dei float = %d byte e %d bit\n", sizeAf, sizeAf*8);
    printf("Dimensione dei double = %d byte e %d bit\n", sizeAd, sizeAd*8);
    printf("Dimensione dei long double = %d byte e %d bit\n\n", sizeAld, sizeAld*8);


    ai = 1; //quindi 0000 0000 0000 0000 0000 0000 0000 0001
    ai = ai >> 1;
    if(ai == 0){
        bigEndian = 1;
        printf("Calcolatore Big Endian\n");
    }
    else
        printf("Calcolatore Little Endian\n");

    printf("Inserisci valore: ");
    scanf("%f", &af);
    ad = (double)af;
    ald = (long double)af;

    stampaCodifica((void *)&af, sizeof(af), bigEndian);
    stampaCodifica((void *)&ad, sizeof(ad), bigEndian);
    stampaCodifica((void *)&ald, sizeof(ald), bigEndian);



    return 0;
}

void stampaCodifica (void *p, int size, int bigEndian){

}
