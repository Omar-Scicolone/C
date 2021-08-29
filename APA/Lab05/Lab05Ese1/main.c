#include <stdio.h>
#include <stdlib.h>
#define MAX_LEN 20
#define N 255

typedef struct{
    int numScelte;
    char **brani;
}Amico;

int princ_molt(int pos, Amico *amici, char **sol, int n, int count);

int main()
{
    FILE *fp;
    Amico *amici;
    char **sol;
    int numAmici;
    int i = 0, j = 0, comb;

    fp = fopen("brani.txt", "r");

    fscanf(fp, "%d", &numAmici);
    amici = malloc(numAmici*sizeof(Amico));

    while(fscanf(fp, "%d", &amici[i].numScelte) != EOF){
        amici[i].brani = malloc(amici[i].numScelte * sizeof(char *));

        for (j=0; j<amici[i].numScelte; j++){
            amici[i].brani[j] = malloc(N*sizeof(char));
            fscanf(fp, "%s", amici[i].brani[j]);
        }
        i++;
    }

    sol = malloc(numAmici*sizeof(char *));

    comb = princ_molt(0, amici, sol, numAmici, 0);
    printf("%d", comb);

    return 0;
}

int princ_molt(int pos, Amico *amici, char **sol, int n, int count){
    int i;

    if (pos >= n){
        for (i=0; i<n; i++){
            printf("%s\n", sol[i]);
        }
        printf("\n");
        return count+1;
    }
    for (i=0; i<amici[pos].numScelte; i++){
        sol[pos] = amici[pos].brani[i];
        count = princ_molt(pos+1, amici, sol, n, count);
    }

    return count;
}
