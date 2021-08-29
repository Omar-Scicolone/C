#include <stdio.h>
#include <stdlib.h>
#define MAX 20
#define DIM 30

void memoMatr(int matr[DIM][DIM], int nr, int nc, FILE *fp);
void rotPerRighe(int matr[DIM][DIM], int nr, int nc);
void rotPerColonne(int matr[DIM][DIM], int nr, int nc);
int main() {
    char name[MAX];
    int matr[DIM][DIM];
    int scelta;
    FILE *fp;
    int nc, nr, i, j;
    printf("Inserire nome file: ");
    scanf("%s", name);

    fp = fopen(name, "r");

    fscanf(fp, "%d", &nr);
    fscanf(fp, "%d", &nc);

    memoMatr(matr, nr, nc, fp);

    printf("Scegli rotazione:\n1 per righe\n2 per colonne\n0 per fine\n");
    scanf("%d", &scelta);


    while(scelta != 0) {
        if(scelta == 1) {
            rotPerRighe(matr, nr, nc);
        } else {
            rotPerColonne(matr, nr, nc);
        }
        printf("Scegli rotazione:\n1 per righe\n2 per colonne\n0 per fine\n");
        scanf("%d", &scelta);
    }
    printf("\n");
    printf("Rotazioni completate con la seguente matrice\n");
    for (i=0; i<nr; i++) {
        for (j=0; j<nc; j++) {
            printf("%d ", matr[i][j]);
        }
        printf("\n");
    }

    return 0;
}

void memoMatr(int matr[DIM][DIM], int nr, int nc, FILE *fp) {
    int i, j;

    for (i=0; i<nr; i++) {
        for (j=0; j<nc; j++) {
            fscanf(fp, "%d", &matr[i][j]);
        }
    }
}

void rotPerRighe(int matr[DIM][DIM], int nr, int nc) {
    int ind, dir, pos, i, j, n;
    int tmp[DIM][DIM];

    for (i=0; i<nr; i++) {
        for (j=0; j<nc; j++) {
            tmp[i][j] = matr[i][j];
        }
    }

    printf("Scegli indice, direzione (0 = DX | 1 = SX), rotazioni\n");
    scanf("%d %d %d", &ind, &dir, &pos);

    if (dir == 0) { //destra
        for (j=0; j<nc; j++) {
            if (j+pos < nc) {
                matr[ind][j+pos] = tmp[ind][j];
            } else {
                n = j+pos-nc;
                while (n>=nc){
                    n -= nc;
                }
                matr[ind][n] = tmp[ind][j];
            }
        }


    } else {
        for (j=0; j<nc; j++) {
            if (j-pos >= 0) {
                matr[ind][j-pos] = tmp[ind][j];
            }

            else {
                n = j-pos+nc;
                while (n<0) {
                    n += nc;

                }

                matr[ind][n] = tmp[ind][j];
            }

        }
    }

    //stampa
    printf("\n");
    for (i=0; i<nr; i++) {
        for (j=0; j<nc; j++) {
            printf("%d ", matr[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void rotPerColonne(int matr[DIM][DIM], int nr, int nc) {
    int ind, dir, pos, i, j, n;
    int tmp[DIM][DIM];

    for (i=0; i<nr; i++) {
        for (j=0; j<nc; j++) {
            tmp[i][j] = matr[i][j];
        }
    }

    printf("Scegli indice, direzione (0 = GIU' | 1 = SU), rotazioni\n");
    scanf("%d %d %d", &ind, &dir, &pos);

    if (dir == 0) { //GIU
        for (i=0; i<nr; i++) {
            if (i+pos < nr) {
                matr[i+pos][ind] = tmp[i][ind];
            } else {
                n = i+pos-nr;
                while (n>=nr){
                    n -= nr;
                }
                matr[n][ind] = tmp[i][ind];
            }
        }


    } else {
        for (i=0; i<nr; i++) {
            if (i-pos >= 0) {
                matr[i-pos][ind] = tmp[i][ind];
            }

            else {
                n = i-pos+nr;
                while (n<0) {
                    n += nr;

                }

                matr[n][ind] = tmp[i][ind];
            }

        }
    }

    //stampa
    printf("\n");
    for (i=0; i<nr; i++) {
        for (j=0; j<nc; j++) {
            printf("%d ", matr[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}



