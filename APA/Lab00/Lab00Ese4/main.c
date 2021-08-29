#include <stdio.h>
#include <stdlib.h>
#define N 20

void sottomatrici (int dim, int matrix[N][N], int nr, int nc){
    int i,j,k,y;
    int count = 0, max = 0;
    int matrMax[N][N];
    int matrTmp[N][N];

    for (y=0; y<=nr-dim; y++){
        for (k=0; k<=nc-dim; k++){
            for (i=0; i<dim; i++){
                for (j=0; j<dim; j++){
                    printf("%d ", matrix[y+i][k+j]);

                    count += matrix[y+i][k+j];
                    matrTmp[i][j] = matrix[y+i][k+j];
                }
                printf("\n");
            }
            if (max<count){
                max = count;
                for (i=0; i<dim; i++){
                    for (j=0; j<dim; j++){
                        matrMax[i][j] = matrTmp[i][j];
                    }
                }
            }
            count = 0;
            printf("\n");
        }
    }

    printf("La matrice massiva e':\n");
    for (i=0; i<dim; i++){
            for (j=0; j<dim; j++){
                printf("%d ", matrMax[i][j]);
            }
    printf("\n");
    }
}
int main()
{
    char name [N];
    int matrix [N][N];
    int nr, nc, i, j, min, dim;
    FILE *fp;

    printf("Name's file: ");
    scanf("%s", name);
    fp = fopen(name, "r");
    fscanf(fp, "%d", &nr); //Max 20
    fscanf(fp, "%d", &nc); //Max 20

    for (i=0; i<nr; i++){
        for (j=0; j<nc; j++){
            fscanf(fp, "%d", &matrix[i][j]);
        }
    }



    if (nr<nc){
        min = nr;
    }
    else{
        min = nc;
    }

    printf("Dim matrices (1<dim<%d): ", min);
    scanf("%d", &dim);
    while (dim<min && dim > 1){
        sottomatrici(dim, matrix, nr, nc);
        printf("Dim matrices (1<dim<%d): ", min);
        scanf("%d", &dim);
    }

    return 0;
}
