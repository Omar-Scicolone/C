#include <stdio.h>
#include <stdlib.h>
#define MAXN 30

void ruota(int V[MAXN], int N, int P, int dir){
    int i, j, n;
    int vett[N];
    for (i=0; i<N; i++){
        vett[i] = V[i];
    }


    if (dir == -1){
        for (j=0; j<N; j++){
            if (j+P > N-1){
                n = j+P - N;
            }
            else {
                n = j+P;
            }

            V[n] = vett[j];
        }
    }
    else{
        for (j=0; j<N; j++){
            if (j-P < 0){
                n = j-P + N;
            }
            else{
                n = j-P;
            }
            V[n] = vett[j];
        }

    }
}


int main()
{
    int i = 0, N = 0, P = 1, dir = 0;
    int V [MAXN];

    printf("Lunghezza vettore: ");
    scanf("%d", &N);
    while (N > MAXN){
        printf("Lunghezza vettore minore/uguale 30: ");
        scanf("%d", &N);
    }

    for (i=1; i<=N; i++){
        printf("Inserisci elemento no %d: ", i);
        scanf("%d", &V[i-1]);
    }

    while (P != 0){
        printf("Quante rotazioni?: ");
        scanf("%d", &P);

        while (P>=N){
            printf("Quante rotazioni? (minore di %d): ", N);
            scanf("%d", &P);
        }
            if (P != 0){
            printf("SX = 1 \nDX = -1 \n");
            scanf("%d", &dir);

            ruota(V, N, P, dir);
        }
    }

    for (i=0; i<N; i++){
        printf("%d ", V[i]);

    }

    return 0;
}
