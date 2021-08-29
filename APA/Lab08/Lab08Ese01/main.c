#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int s;
    int f;
}att;

void powerset(int pos, att *v, att *sol, int k, int next, att* bestValue, int *bestDist);
void attSel(int N, att *v);

int main()
{
    att *v;
    int N, i = 0;
    FILE *fp = fopen("att.txt", "r");
    fscanf(fp, "%d", &N);
    v = malloc(N * sizeof(att));

    while (fscanf(fp, "%d %d", &v[i].s, &v[i].f) != EOF)
        i++;

    attSel(N, v);
    return 0;
}


void powerset(int pos, att *v, att *sol, int k, int start, att* bestValue, int *bestDist){
    int i;
    int d = 0;

    if (start >= k){

        for (i=0; i<pos; i++){
            d += (sol[i].f - sol[i].s);
        }
        if (d > *bestDist){
            *bestDist = d;
            for (i=0; i<pos; i++){
                bestValue[i].s = sol[i].s;
                bestValue[i].f = sol[i].f;
            }
        }

        return;
    }
    for (i=start; i<k; i++){
        sol[pos] = v[i];

        if (pos != 0){
            if(sol[pos-1].s <= sol[pos].s && sol[pos].s < sol[pos-1].f){ //controllo conpatibilita
                continue;
            }
        }

        powerset(pos+1, v, sol, k, i+1, bestValue, bestDist);
    }

    powerset(pos, v, sol, k, k, bestValue, bestDist);
    return;
}

void attSel(int N, att *v){
    att *sol;
    att *bestValue;
    int bestDist = 0;
    int i;

    sol = calloc(N, sizeof(att));
    bestValue = calloc(N, sizeof(att));
    powerset(0, v, sol, N, 0, bestValue, &bestDist);

    printf("Distanza migliore = %d\n", bestDist);

    printf("Con il percorso: ");
    for(i=0; i<N; i++){
        if(bestValue[i].s != 0)
            printf("{%d %d} ", bestValue[i].s, bestValue[i].f);
    }

}

