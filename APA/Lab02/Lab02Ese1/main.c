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

void leggiMatrice(int matr[MAX][MAX], int nr, int nc, FILE *fp);

int main()
{
    FILE *fp;
    int matr[MAX][MAX];
    Matrici matrici[MAX*MAX];
    int indiciMatrici = 0;
    int nr, nc, i, j, k, y, coordX, coordY, n, m, ind_max;
    int b_max = 0, h_max = 0, a_max = 0;
    int b_tmp = 0, h_tmp = 0;

    fp = fopen("matrice.txt", "r");
    fscanf(fp, "%d %d", &nr, &nc);
    leggiMatrice(matr, nr, nc, fp);

    for (i=0; i<nr; i++){
        for (j=0; j<nc; j++){

            coordY = i;
            coordX = j;
            b_tmp = 0;
            h_tmp = 0;

            if (matr[i][j] == 1){
                //definizione base
                k = j;
                while (matr[i][k]==1){
                    b_tmp++;  //ricorda di azzerarli
                    k++;
                }

                //definizione altezza
                k = i;
                while (matr[k][j]==1){
                    h_tmp++;       //ricorda di azzerarli
                    k++;
                }

                //def
                matrici[indiciMatrici].base = b_tmp;
                matrici[indiciMatrici].haltezza = h_tmp;
                matrici[indiciMatrici].area = b_tmp*h_tmp;
                matrici[indiciMatrici].coord[0] = coordY;
                matrici[indiciMatrici].coord[1] = coordX;
                indiciMatrici++;

                n = h_tmp+coordY;
                m = b_tmp+coordX;

                for (k=coordY; k<n; k++){
                    for (y=coordX; y<m; y++){
                            matr[k][y] = 0;
                    }
                }

            }
        }
    }

    for (i=0; i<indiciMatrici; i++){
        if (matrici[i].base>b_max){
            b_max = matrici[i].base;
            ind_max = i;
        }
    }
    printf("Max Base: estr. sup. SX=<%d, %d> b=%d, h=%d, Area=%d\n", matrici[ind_max].coord[0], matrici[ind_max].coord[1], matrici[ind_max].base, matrici[ind_max].haltezza, matrici[ind_max].area);

    for (i=0; i<indiciMatrici; i++){
        if (matrici[i].area>a_max){
            a_max = matrici[i].area;
            ind_max = i;
        }
    }
    printf("Max Area: estr. sup. SX=<%d, %d> b=%d, h=%d, Area=%d\n", matrici[ind_max].coord[0], matrici[ind_max].coord[1], matrici[ind_max].base, matrici[ind_max].haltezza, matrici[ind_max].area);

    for (i=0; i<indiciMatrici; i++){
        if (matrici[i].haltezza>h_max){
            h_max = matrici[i].haltezza;
            ind_max = i;
        }
    }
    printf("Max Altezza: estr. sup. SX=<%d, %d> b=%d, h=%d, Area=%d\n", matrici[ind_max].coord[0], matrici[ind_max].coord[1], matrici[ind_max].base, matrici[ind_max].haltezza, matrici[ind_max].area);

    return 0;
}


void leggiMatrice(int matr[MAX][MAX], int nr, int nc, FILE *fp){
    int i, j;
    for (i=0; i<nr; i++){
        for (j=0; j<nc; j++){
            fscanf(fp, "%d", &matr[i][j]);
        }
    }
}


