#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int u;
    int v;
}Arco;

typedef struct{
    int N;  //numero vertici
    int E; //numero archi
    Arco *archi;
} Graph;

int powerset (int pos, int *val, int *sol, int k, int start, int count, Graph grafo);


int main()
{
    FILE *fp = fopen("grafo.txt", "r");
    Graph grafo;
    int i, pos = 0, *sol, *val, start = 0, count = 0;

    fscanf(fp, "%d %d", &grafo.N, &grafo.E);
    grafo.archi = malloc((grafo.E)*sizeof(Arco));

    for (i=0; i<grafo.E; i++){
        fscanf(fp, "%d", &grafo.archi[i].u);
        fscanf(fp, "%d", &grafo.archi[i].v);
    }

    val = malloc(grafo.N*sizeof(Arco));
    for (i=0; i<grafo.N; i++){
        val[i] = (i);
    }

    sol = malloc((2^grafo.N)*sizeof(int));

    powerset(pos, val, sol, grafo.N, start, count, grafo);


    return 0;
}


int powerset (int pos, int *val, int *sol, int k, int start, int count, Graph grafo){
    int i, j, flag;

    if (start >= k){
        //adesso devi verificare se quello che c'è in sol è corretto

        for (i=0; i<grafo.E; i++){
            flag = 0;
            for(j=0; j<pos; j++){
                if (grafo.archi[i].u == sol[j] || grafo.archi[i].v  == sol[j])
                    flag = 1;
            }
            if (flag == 0){
                break;
            }
        }
            if(flag == 1){
                printf("{ ");
                for(i = 0; i<pos; i++)
                    printf("%d ", sol[i]);
                printf("}");
                printf("\n");
            }
        return count+1;
    }

    for (i=start; i<k; i++){
        sol[pos] = val[i];
        count = powerset(pos+1, val, sol, k, i+1, count, grafo);
    }
    count = powerset(pos, val, sol, k, k, count, grafo);

    return count;
}
