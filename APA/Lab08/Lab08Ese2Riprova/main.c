#include <stdio.h>
#include <stdlib.h>

typedef struct{
    char co;
    int vo;
    char cv;
    int vv;
}Tessera;

void princ_molt(int pos2, Tessera **sol2, int dim, Tessera **best_sol2, int *best_value2, int *ruotabile);
void perm_sempl(int pos, Tessera *val, Tessera **sol, int *mark, int n, int dim, Tessera **best_sol, int *best_value, Tessera **best_sol2, Tessera **sol2, int *ruotabile);
int calcolaVatt(Tessera **sol, int dim);
void ruota(Tessera **sol,  int r, int c);

int main()
{
    FILE *fp = fopen("tiles.txt", "r");
    Tessera *tessere;
    int *mark;
    int *ruotabile;
    int numTess;
    Tessera **board;
    Tessera **best_sol = NULL;
    int best_value = 0;
    int r, c, i, j, index, rotation;
    char capo;
    Tessera **best_sol2 = NULL;
    Tessera **sol2 = NULL;

    fscanf(fp, "%d", &numTess);
    tessere = malloc(numTess*sizeof(Tessera));
    mark = calloc(numTess, sizeof(int));
    ruotabile = calloc(numTess, sizeof(int));

    for(i=0; i<numTess; i++){
        fscanf(fp, "%c", &capo);
        fscanf(fp, "%c %d %c %d", &tessere[i].co, &tessere[i].vo, &tessere[i].cv, &tessere[i].vv);
    }
    fclose(fp);

   fp = fopen("board.txt", "r");

    fscanf(fp, "%d %d", &r, &c);

    sol2 = malloc(r*sizeof(Tessera *));
    best_sol2 = malloc(r*sizeof(Tessera *));
    for(i=0; i<r; i++){
        best_sol2[i] = malloc(r*sizeof(Tessera));
        sol2[i] = malloc(r*sizeof(Tessera));
    }


    board = malloc(r*sizeof(Tessera *));
    best_sol = malloc(r*sizeof(Tessera *));
    for(i=0; i<r; i++){
        board[i] = malloc(c*sizeof(Tessera));
        best_sol[i] = malloc(c*sizeof(Tessera));
        for(j=0; j<c; j++){
            fscanf(fp, "%d/%d", &index, &rotation);
            if (index != -1){
                mark[index] = 1;
                if (rotation == 0){
                    board[i][j] = tessere[index];
                }
                else {
                    board[i][j].co = tessere[index].cv;
                    board[i][j].cv = tessere[index].co;
                    board[i][j].vo = tessere[index].vv;
                    board[i][j].vv = tessere[index].vo;
                }
            }
            else{
                board[i][j].vo = -1;
            }
        }
    }

    for(i=0; i<numTess; i++){
        ruotabile[i] = mark[i];
    }

    perm_sempl(0, tessere, board, mark, numTess, r, best_sol, &best_value, best_sol2, sol2, ruotabile);

    printf("Stampa soluzione migliore\n");
    for(i=0; i<r; i++){
        for(j=0; j<c; j++){
            printf("%c%d %c%d       ", best_sol[i][j].co, best_sol[i][j].vo, best_sol[i][j].cv, best_sol[i][j].vv);
        }
        printf("\n");
    }

    printf("\n\nBest Value = %d", best_value);

  return 0;
}

void perm_sempl(int pos, Tessera *val, Tessera **sol, int *mark, int n, int dim, Tessera **best_sol, int *best_value, Tessera **best_sol2, Tessera **sol2, int *ruotabile){
    int i, j, r, c;
    int pos2 = 0;
    int best_value2 = 0;


    if(pos >= dim*dim){

        for(i=0; i<dim; i++){
            for(j=0; j<dim; j++){
                sol2[i][j] = sol[i][j];
            }
        }

        princ_molt(pos2, sol2, dim, best_sol2, &best_value2, ruotabile);
        if (best_value2 > *best_value){
            *best_value = best_value2;

            for(i=0; i<dim; i++){
                for(j=0; j<dim; j++){
                    best_sol[i][j] = best_sol2[i][j];
                }
            }
        }
        return;
    }
    r = pos/dim;
    c = pos%dim;

    if (sol[r][c].vo != -1){
            perm_sempl(pos+1, val, sol, mark, n, dim, best_sol, best_value, best_sol2, sol2, ruotabile);
            return;
    }

    for(i=0; i<n; i++){
        if (mark[i] == 0){
            mark[i] = 1;
            sol[r][c] = val[i];
            perm_sempl(pos+1, val, sol, mark, n, dim, best_sol, best_value, best_sol2, sol2, ruotabile);
            mark[i] = 0;
            sol[r][c].vo = -1;
        }
    }

    return;
}

int calcolaVatt(Tessera **mat, int dim){
    int i, j, tot=0, tot_tmp = 0;

    for(i=0; i<dim; i++){
        tot_tmp = mat[i][0].vo;
        for(j=1; j<dim; j++){
            if (mat[i][j].co == mat[i][j-1].co){
                tot_tmp += mat[i][j].vo; //
            }
            else{
               tot_tmp = 0;
               break;
            }
        }
        tot += tot_tmp;
    }

    for(j=0; j<dim; j++){
        tot_tmp = mat[0][j].vv;
        for(i=1; i<dim; i++){
            if (mat[i][j].cv == mat[i-1][j].cv){
                tot_tmp += mat[i][j].vv; //
            }
            else{
               tot_tmp = 0;
               break;
            }
        }
        tot += tot_tmp;
    }

    return tot;
}

void princ_molt(int pos2, Tessera **sol2, int dim, Tessera **best_sol2, int *best_value2, int *ruotabile){
    int i, j, r, c;
    int val_att = 0;

    if (pos2>=dim*dim){
       val_att = calcolaVatt(sol2, dim);
       if (val_att > *best_value2){
            *best_value2 = val_att;

            for(i=0; i<dim; i++){
                for(j=0; j<dim; j++){
                    best_sol2[i][j] = sol2[i][j];
                }
            }
        }
       return;
    }

    r = pos2/dim;
    c = pos2%dim;
    if (ruotabile[pos2] == 0){
        for (i=0; i<2; i++){
            if (i!=0)
                ruota(sol2, r, c);
            princ_molt(pos2+1, sol2, dim, best_sol2, best_value2, ruotabile);
        }
    }
    else
        princ_molt(pos2+1, sol2, dim, best_sol2, best_value2, ruotabile);

    return;
}

void ruota(Tessera **sol2, int r, int c){
    Tessera tmp;
    tmp.co = sol2[r][c].cv;
    tmp.vo = sol2[r][c].vv;
    sol2[r][c].cv = sol2[r][c].co;
    sol2[r][c].vv = sol2[r][c].vo;
    sol2[r][c].co = tmp.co;
    sol2[r][c].vo = tmp.vo;
    return;
}
