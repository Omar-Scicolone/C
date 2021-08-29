#include <stdio.h>
#include <stdlib.h>

int disp_rip(int pos, int *val, int *sol, int n, int k);
int verificaCond(int prec, int ins);

int main()
{
    int *sol, *val;
    int n = 4, pos=0;
    int k;
    int i, j, lenF;
    int trovato = 0, tot = 0;
    FILE *fp = fopen("e1_hard_test_set.txt", "r");
    fscanf(fp, "%d", &lenF);

    val = malloc(n * sizeof(int));
    for (j=0; j<lenF; j++, trovato=0, tot=0, pos=0){
        for(i=0; i<4; i++){
            fscanf(fp, "%d", &val[i]);
            tot += val[i];
        }

        sol = malloc(tot * sizeof(int));


        for (k=tot; k>0; k--){
            trovato = disp_rip(pos, val, sol, n, k);
            if (trovato == 1)
                break;
        }

        free(sol);
    }




    return 0;
}

int disp_rip(int pos, int *val, int *sol, int n, int k){
    int i;
    int trovato = 0;
    if(pos >= k){
        for(i=0; i<k; i++)
            printf("%d ", sol[i]);
        printf("\nCollana massima di lunghezza: %d\n", i);
        return 1; //soluzione trovata
    }

    for(i=0; i<n; i++){
        sol[pos] = i;
        //verifica che l'i appena messo vada bene, altrimenti ciclo successivo
        if (pos != 0)
            if (verificaCond(sol[pos-1], i) != 1)
                continue;
        //verifica che la quantita' vada bene, ovvero che val[i] sia maggiore di zero, altrimenti ciclo successivo
        if (val[i] == 0)
            continue;

        val[i]--;
        trovato = disp_rip(pos+1, val, sol, n, k);
        val[i]++;

        if(trovato == 1)
            return 1;
    }

    return 0;
}


int verificaCond(int prec, int ins){
    if (prec == 0) //zaffiro
        if (ins == 0 || ins == 1)
            return 1;

    if (prec == 1) //rubino
        if (ins == 3 || ins == 2)
            return 1;

    if (prec == 2) //topazio
        if (ins == 0 || ins == 1)
            return 1;

    if (prec == 3) //smeraldo
        if (ins == 3 || ins == 2)
            return 1;

    return 0;

}






