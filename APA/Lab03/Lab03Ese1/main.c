#include <stdio.h>
#include <stdlib.h>
#define MAX 50
#define MAX_CARATT 10
#define MAX_COORD 2

typedef struct matrici {
    int coord[MAX_COORD];
    int base;
    int area;
    int haltezza;
} Matrici;

void leggiMatrice(int matr[MAX][MAX], int *pr, int *pc);
int riconosciRegione(int matr[MAX][MAX],int nr, int nc, int i, int j,int *b,int *h, Matrici matrici[MAX*MAX], int *indic);

int main() {

    int matr[MAX][MAX];
    Matrici matrici[MAX*MAX];
    int indiciMatrici = 0;
    int nr, nc, i, j, ind_max;
    int b_max = 0, h_max = 0, a_max = 0;

    int b, h;

    leggiMatrice(matr, &nr, &nc);

    for (i=0; i<nr; i++) {
        for (j=0; j<nc; j++) {

            if (riconosciRegione(matr,nr,nc,i,j,&b,&h, matrici, &indiciMatrici)) {
                printf("Trovato rettangolo coordinate %d %d\n", i, j);
                printf("Con base %d e altezza %d \n", b, h);

            }
        }}


            for (i=0; i<indiciMatrici; i++) {
                if (matrici[i].base>b_max) {
                    b_max = matrici[i].base;
                    ind_max = i;
                }
            }

            printf("Max Base: estr. sup. SX=<%d, %d> b=%d, h=%d, Area=%d\n", matrici[ind_max].coord[0], matrici[ind_max].coord[1], matrici[ind_max].base, matrici[ind_max].haltezza, matrici[ind_max].area);

            for (i=0; i<indiciMatrici; i++) {
                if (matrici[i].area>a_max) {
                    a_max = matrici[i].area;
                    ind_max = i;
                }
            }
            printf("Max Area: estr. sup. SX=<%d, %d> b=%d, h=%d, Area=%d\n", matrici[ind_max].coord[0], matrici[ind_max].coord[1], matrici[ind_max].base, matrici[ind_max].haltezza, matrici[ind_max].area);

            for (i=0; i<indiciMatrici; i++) {
                if (matrici[i].haltezza>h_max) {
                    h_max = matrici[i].haltezza;
                    ind_max = i;
                }
            }
            printf("Max Altezza: estr. sup. SX=<%d, %d> b=%d, h=%d, Area=%d\n", matrici[ind_max].coord[0], matrici[ind_max].coord[1], matrici[ind_max].base, matrici[ind_max].haltezza, matrici[ind_max].area);

            return 0;
        }


        void leggiMatrice(int matr[MAX][MAX], int *pr, int *pc) {
            int nr, nc;

            FILE *fp;
            fp = fopen("matrice.txt", "r");
            fscanf(fp, "%d %d", pr, pc);

            nr = *pr;
            nc = *pc;

            int i, j;
            for (i=0; i< nr; i++) {
                for (j=0; j< nc; j++) {
                    fscanf(fp, "%d", &matr[i][j]);
                }
            }
        }

        int riconosciRegione(int matr[MAX][MAX],int nr, int nc, int i, int j,int *b,int *h, Matrici matrici[MAX*MAX], int *indic) {

            int coordY = i;
            int coordX = j;
            int b_tmp = 0;
            int h_tmp = 0;
            int k=0, n=0, m=0, y=0;

            if (matr[i][j] == 1) {
                //definizione base
                k = j;
                while (matr[i][k]==1) {
                    b_tmp++;  //ricorda di azzerarli
                    k++;
                }

                //definizione altezza
                k = i;
                while (matr[k][j]==1) {
                    h_tmp++;       //ricorda di azzerarli
                    k++;
                }

                //def
                *b = b_tmp;
                matrici[*indic].base = b_tmp;
                *h = h_tmp;
                matrici[*indic].haltezza = h_tmp;

                matrici[*indic].area = b_tmp*h_tmp;

                matrici[*indic].coord[0] = coordY;
                matrici[*indic].coord[1] = coordX;
                *indic = *indic + 1;

                n = h_tmp+coordY;
                m = b_tmp+coordX;

                for (k=coordY; k<n; k++) {
                    for (y=coordX; y<m; y++) {
                        matr[k][y] = 0;
                    }
                }
            return 1;
            }
            return 0;
        }
