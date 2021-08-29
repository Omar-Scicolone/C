#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char * argv[])
{
    if (argc != 1){
        printf("ERROR");
        return -1;
    }

    FILE *mt;
    char map [24][70+1];
    int res, i,j, lunghezza=0, lunghezza_max = 0, len, riga, col_inizio=0, col_inizio_2=0, col_fine, alt, altezza = 0, altezza_max =0, rig_inzio=0, rig_fine=0, riga_inizio_2 = 0, colonna;

    mt = fopen("Matrix.txt", "r");
    if (mt == NULL){
        printf("ERROR");
        return -2;
    }
    i=0;
    res = fscanf(mt, "%s", map[i]);
    len = strlen(map[i]);
    while (res != EOF){
    j = 0;
    for (j=0; j<len; j++){
        if ('d' == map[i][j]){
            lunghezza++;
            /*while(col_inizio==0){
                    col_inizio=j;}*/
        }
        else {
            if (lunghezza > lunghezza_max){
                /*col_inizio = col_inizio_2;
                col_inizio=0;*/
                riga = i+1;
                col_fine=j;
                lunghezza_max=lunghezza;}
                 lunghezza=0;
            }
        }
        i++;
        res = fscanf (mt, "%s", map [i]);
    }
    alt = i;

    for (j=0; j<len; j++){
        for (i=0; i<alt; i++){
            if (map[i][j]=='d'){
                altezza++;
                /*while(rig_inzio==0){
                    rig_inzio=i;}*/
            }
            else{
                if (altezza>altezza_max){
                    colonna=j;
                    rig_fine = i;
                    /*rig_inzio =  riga_inizio_2;
                    rig_inzio=0;*/
                    altezza = altezza_max;
                } altezza=0;
            }
        }
    }
if (altezza_max>lunghezza_max){
    printf("Sequenza trovata: carattere %c - verticale - colonna %d - lunghezza %d ", 'd', colonna, altezza_max);
    printf((/*"Inizio: colonna %d*/ "- Fine: colonna %d"), rig_inzio, rig_fine);
}
else {
    printf("Sequenza trovata: carattere %c - orizzontale - riga %d - lunghezza %d ", 'd', riga, lunghezza_max);
    printf((/*"Inizio: riga %d - */"Fine: riga %d"), col_inizio, col_fine);
}
    return 0;
}
