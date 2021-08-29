#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LENGTH 200
#define MAX_DIZ 30
#define MAX_WORD 50

typedef struct word {
    char recod[MAX_WORD];
    char w[MAX_WORD];
} Word;


int leggiDiz(Word dizionario [MAX_DIZ]);
void stampaInMatrice(char str[MAX_LENGTH], FILE *fw, char c);
void modificaInMatrice(char str[MAX_LENGTH], int indiceInizioDaPassare, char recod[MAX_WORD], char w[MAX_WORD], FILE *fw, char c);

int main() {
    FILE *fs, *fw;
    int nDiz, i, j, k = 0, len, len2, flag = 0, trovato = 0, indiceInizio, indiceInizioDaPassare;
    char str[MAX_LENGTH];
    Word dizionario [MAX_DIZ];
    fs = fopen("sorgente.txt", "r");
    fw = fopen("recodifica.txt", "w");
    nDiz = leggiDiz(dizionario);
    char c;

    while (fscanf(fs, "%s", str) != EOF) {

        c = fgetc(fs);

        trovato = 0;
        for (i=0; i<nDiz && trovato == 0; i++) {
            len = strlen(str);
            len2 = strlen(dizionario[i].w);
            for(j=0; j<len && trovato == 0; j++) {
                if (str[j] == dizionario[i].w[0]) {
                    indiceInizio = j;
                    indiceInizioDaPassare = j;
                    indiceInizio++;

                    for (k=1; k<len2 && flag == 0; k++){ //questo flag deve tornare a 0
                        if (dizionario[i].w[k]!= str[indiceInizio]){
                            flag = 1;
                        }
                        else {
                            indiceInizio++;
                        }
                    }
                    if (flag == 0){
                        modificaInMatrice(str, indiceInizioDaPassare, dizionario[i].recod, dizionario[i].w, fw, c);
                        trovato = 1;
                    }
                    else {
                        j = indiceInizioDaPassare;
                    }
                }
                flag = 0;
            }
        }
        if (trovato == 0){
            stampaInMatrice(str, fw, c);
        }
    }

    return 0;
}

int leggiDiz(Word dizionario [MAX_DIZ]) {
    FILE *fd;
    int nRighe, i;

    fd = fopen("dizionario.txt", "r");
    fscanf(fd, "%d", &nRighe);
    for (i=0; i<nRighe; i++) {
        fscanf(fd, "%s", dizionario[i].recod);
        fscanf(fd, "%s", dizionario[i].w);
    }
    return nRighe;
}

void stampaInMatrice(char str[MAX_LENGTH], FILE *fw, char c){
    fprintf(fw, "%s ", str);
    if (c == '\n'){
        fprintf(fw, "%c", c);
    }

}

void modificaInMatrice(char str[MAX_LENGTH], int indiceInizioDaPassare, char recod[MAX_WORD], char w[MAX_WORD], FILE *fw, char c){
    int len = strlen(str);
    int len2 = strlen(w);
    int len3 = strlen(recod);
    int n = len-len2+len3;
    int i;
    int k = 0;
    char tmp[MAX_LENGTH];


    for (i=0; i<n; i++){
        if (i<indiceInizioDaPassare){
            tmp[i] = str[i];
        }

        else{
            if (i<indiceInizioDaPassare+len3){
                tmp[i] = recod[k];
                k++;
            }
            else {
                tmp[i] = str[i-len2];
            }
        }
    }
    tmp[i] = '\0';
    fprintf(fw, "%s ", tmp);
    if (c == '\n'){
        fprintf(fw, "%c", c);
    }
}

