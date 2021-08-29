#include <stdio.h>
#include <stdlib.h>

int** malloc2dR(int nr, int nc);
void separa(int **mat, int nr, int nc, int *b, int *n, int *nB, int *nN);


int main()
{
    int nTotN = 1;
    int nTotB = 1;
    int nr, nc, i, j;
    FILE *fp = fopen("mat.txt", "r");
    int **mat;
    int *b;
    int *n;
    fscanf(fp, "%d%d", &nr, &nc);
    mat = malloc2dR(nr, nc);

    for(i=0; i<nr; i++) {
        for(j=0; j<nc; j++) {
            fscanf(fp, "%d", &mat[i][j]);
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }

    b = malloc((((nr*nc)/2)+1)*sizeof(int));
    n = malloc((((nr*nc)/2)+1)*sizeof(int));


    separa(mat, nr, nc, b, n, &nTotB, &nTotN);

    printf("Bianchi: ");
    for (i=0; i<nTotB-1; i++) {
        printf("%d ", b[i]);
    }

    printf("\nNeri: ");
    for (i=0; i<nTotN-1; i++) {
        printf("%d ", n[i]);
    }

    free(b);
    free(n);


    return 0;
}

int** malloc2dR(int nr, int nc) {
    int **m;
    int i;

    m = malloc(nr*sizeof(int*));

    for (i=0; i<nr; i++) {
        m[i] = malloc(nc*sizeof(int));
    }

    return m;
}

void separa(int **mat, int nr, int nc, int *b, int *n, int *nTotB, int *nTotN) {
    int i, j;

    int fine[2];

    for(i=0; i<nr; i++) {
        if (i%2 == 0) {                     //inizia con n
            for(j=0; j<nc; j++) {
                if (j%2 == 0) {             //sei al n
                    n[(*nTotN)-1] = mat[i][j];
                    (*nTotN)++;
                    //n = realloc(n, (*nTotN)*sizeof(int));

                } else {                    //sei al b
                    b[(*nTotB)-1] = mat[i][j];
                    (*nTotB)++;
                    //b = realloc(b, (*nTotB)*sizeof(int));
                }
            }
        } else {                            //inizia con b
            for(j=0; j<nc; j++) {
                if (j%2 == 0) {             //sei al b
                    b[(*nTotB)-1] = mat[i][j];
                    (*nTotB)++;
                    //b = realloc(b, (*nTotB)*sizeof(int));
                } else {                    //sei al n
                    n[(*nTotN)-1] = mat[i][j];
                    (*nTotN)++;
                    //n = realloc(n, (*nTotN)*sizeof(int));
                }
            }
        }
    }
}


