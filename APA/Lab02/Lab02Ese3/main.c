#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX_S 20
#define MAX_L_S 5
#define MAX_L_P 25
#define MAX_L_R 200

typedef struct sequenze {
    char sequenza[MAX_L_S];
    int pos[10];
} Sequenze;

int letturaSeq(Sequenze seq[MAX_S]);
void toLow(char stringa[MAX_L_P]);
int confrontaParole(char parola [MAX_L_P], Sequenze seq[MAX_S], int numeroParola, int nSeq);

int main() {
    FILE *fp;

    Sequenze seq[MAX_S];
    int i,j, nSeq, lParola, numeroParola=0, altraP = 0;
    char parola [MAX_L_P];
    char parola2 [MAX_L_P];

    nSeq = letturaSeq(seq);
    fp = fopen("testo.txt", "r");

    while ((fscanf(fp, "%s", parola)) != EOF) {

        numeroParola++;
        lParola = strlen(parola);

        for (i=0; i<lParola; i++) {
            if (ispunct(parola[i]) != 0) {
                parola[i] = '\0';
                i++;
                for (j=0; i<lParola; j++) {
                    parola2[j] = parola[i];
                    i++;
                    altraP = 1;
                }
            }
        }

        toLow(parola);
        confrontaParole(parola, seq, numeroParola, nSeq);

        if (altraP == 1) {
            toLow(parola2);
            numeroParola++;
            confrontaParole(parola2, seq, numeroParola, nSeq);
            altraP = 0;
        }
    }

    for (i=0; i<nSeq; i++){
        printf("La sequenza %s appare nelle parole: \n", seq[i].sequenza);
        j=0;
        while (seq[i].pos[j] != 0 && j<10){
            printf("%d ", seq[i].pos[j]);
            j++;
        }
        printf("\n");
    }

    return 0;
}


int letturaSeq(Sequenze seq[MAX_S]) {
    FILE *fp;
    fp = fopen("sequenze.txt", "r");
    int nSeq, i=0, j;

    fscanf(fp, "%d", &nSeq);

    while ((fscanf(fp, "%s", seq[i].sequenza)) != EOF) {
        toLow(seq[i].sequenza);
        //chiamare una funzione per Maiusc/minusc
        for (j=0; j<10; j++) {
            seq[i].pos[j] = 0;
        }


        i++;
    }

    return nSeq;
}

int confrontaParole(char parola [MAX_L_P], Sequenze seq[MAX_S], int numeroParola, int nSeq) {
    int i, j, k, flag=0, diversi = 1;
    int lParola = strlen(parola);
    int lSeq;

    for (j=0; j<nSeq; j++) {
        lSeq = strlen(seq[j].sequenza);

        for (i=0; i<lParola; i++){

            if (parola[i] == seq[j].sequenza[0]){
                for (k=1, diversi=0; k<lSeq && diversi == 0; k++){
                    if (parola[i+k] != seq[j].sequenza[k]){
                        diversi = 1;
                }
            }
        }



        if (diversi == 0) {   //strstr(parola, seq[j].sequenza
            for (i=0; i<10 && flag == 0; i++) {
                if (seq[j].pos[i] == 0) {
                    flag = 1;
                    seq[j].pos[i] = numeroParola;
                }
            }
            return 1;
        }
    }
    }
    return 0;

}

void toLow(char stringa[MAX_L_P]){
    int lStringa = strlen(stringa);
    int i;

    for (i=0; i<lStringa; i++){
        if (stringa[i] < 'a'){
            stringa[i] = stringa[i] + ('a' - 'A');
        }
    }
}
