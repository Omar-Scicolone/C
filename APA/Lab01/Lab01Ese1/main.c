#include <stdio.h>
#include <stdlib.h>
#define MAXS 20
#define MAXG 20

int leggimatrice (int classifica[MAXS][MAXG]);
int contasquadre ();

int main() {

    int classifica[MAXS][MAXG];
    int i, j, k;
    int ngiornate = leggimatrice(classifica);
    int nsquadre = contasquadre();
    int capo = 0, punt = 0, max = 0;
    printf ("%d squadre x %d giornate\n", nsquadre, ngiornate);

    for (k=0; k<ngiornate; k++){

        for (i=0; i<nsquadre; i++){
            for (j=0; j<=k; j++){
                punt += classifica[i][j];
            }
            if (punt > max){
                max = punt;
                capo = i;
            }
            punt = 0;
        }
        printf("Alla fine della giornata %d, capolista %d con %d pti\n", k+1, capo+1, max);
        max = 0;
    }

    return 0;
}

int leggimatrice (int classifica[MAXS][MAXG]){
    FILE *fp;
    int i, j, tmp;
    char c;
    int flag = 0;
    int ncolonne = 0;
    fp = fopen("classifica.txt", "r");

    for (i=0; i<MAXS && flag == 0; i++) {
        j=0;
        ncolonne=0;
        fscanf(fp, "%c", &c);
        while (c != '\n' && flag == 0) {
            if (c != ' ') {
                tmp = c - '0';
                classifica[i][j] = tmp;
                j++;
                ncolonne++;
            }
            if (fscanf(fp, "%c", &c) == EOF){
                flag = 1;
            }
        }
    }
    return ncolonne;
}

int contasquadre(){
    FILE *ffp;
    ffp = fopen("classifica.txt", "r");
    int nsquadre = 0;
    char str [MAXG*2+1];
    while (fgets(str, MAXG*2+1, ffp) != NULL){
        nsquadre++;
    }
    return nsquadre;
}


