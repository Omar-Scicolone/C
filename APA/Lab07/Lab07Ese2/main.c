#include <stdio.h>
#include <stdlib.h>

void disp_rip(int pos, int *val, int *sol, int n, int k, int *valori, int maxR, int *best, int *vett_best);
void aggiornaBest(int *sol, int *vett_best, int pos);
int verificaCond(int prec, int ins);
int verificaMaxRip(int i, int *sol, int maxR, int pos);

int main()
{
    int *sol, *val, *vett_best;
    int valori[4];
    int n = 4, pos=0;
    int k, maxR;
    int i, j, lenF, best;
    int tot = 0;
    FILE *fp = fopen("e2_test_set.txt", "r");
    fscanf(fp, "%d", &lenF);
    val = malloc(n * sizeof(int));

    for (j=0; j<lenF; j++, best=0, tot=0, pos=0){
        for(i=0; i<4; i++){
            fscanf(fp, "%d", &val[i]);
            tot += val[i];
        }

        for(i=0; i<4; i++)
            fscanf(fp, "%d", &valori[i]);

        fscanf(fp, "%d", &maxR);

        sol = malloc(tot * sizeof(int));
        vett_best = malloc(tot * sizeof(int));

        for (k=tot; k>0; k--){
            disp_rip(pos, val, sol, n, k, valori, maxR, &best, vett_best);
            }
        printf("%d", best);
        printf("\n");

        free(sol);
    }

    return 0;
}

void disp_rip(int pos, int *val, int *sol, int n, int k, int *valori, int maxR, int *best, int *vett_best){
    int i, nz = 0, ns = 0, flag = 0;
    int tmp_best = 0;

    if(pos >= k){
        //verificare che numero zaffiri<numero smeraldi DA FARE
        for(i=0; i<pos; i++){
            if(sol[i] == 0){
                nz++;
            }
            if (sol[i] == 3){
                ns++;
            }
        }
        if (nz>ns){
            return;
        }
        //fine condizione zaffiri<smeraldi

        for(i=0; i<k; i++){
            tmp_best += valori[sol[i]];
        }

        if (tmp_best > *best){
            *best = tmp_best;
            aggiornaBest(sol, vett_best, pos);
        }

        return;
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

        //verificaRip
        flag = verificaMaxRip(i, sol, maxR, pos);
        if (flag == 0)
            continue;

        val[i]--;
        disp_rip(pos+1, val, sol, n, k, valori, maxR, best, vett_best);
        val[i]++;
    }
    return;
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

void aggiornaBest(int *sol, int *vett_best, int pos){
    int i;

    for (i=0; i<pos; i++)
        vett_best[i] = sol[i];

}

int verificaMaxRip(int i, int *sol, int maxR, int pos){
    int flag = 0, k;

    for (k=pos; k>=(pos-maxR); k--){
        if (sol[k] != i){
            flag = 1;
            return flag;
        }
    }

    return flag;
}
