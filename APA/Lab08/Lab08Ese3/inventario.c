#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inventario.h"



void stampaInv(tabInv_t inventario) {
    int i;
    for (i=0; i<inventario.maxInv; i++) {
        printf("%s %s %d %d %d %d %d %d\n", inventario.vettInv[i].nome, inventario.vettInv[i].tipo,
               inventario.vettInv[i].stats.hp, inventario.vettInv[i].stats.mp,
               inventario.vettInv[i].stats.atk, inventario.vettInv[i].stats.def,
               inventario.vettInv[i].stats.mag, inventario.vettInv[i].stats.spr);
    }
}


void caricaOgg(tabInv_t *inventario){
    FILE *fp = fopen("inventario.txt", "r");
    int i;

    fscanf(fp, "%d", &inventario->maxInv);

    inventario->vettInv = malloc(inventario->maxInv*sizeof(inv_t));

    for (i=0; i<inventario->maxInv; i++)
        fscanf(fp, "%s %s %d %d %d %d %d %d", inventario->vettInv[i].nome, inventario->vettInv[i].tipo, &inventario->vettInv[i].stats.hp,
               &inventario->vettInv[i].stats.mp, &inventario->vettInv[i].stats.atk, &inventario->vettInv[i].stats.def,
               &inventario->vettInv[i].stats.mag, &inventario->vettInv[i].stats.spr);

    stampaInv(*inventario);
}

void ricercaO(tabInv_t inventario){
    char nome[MAX];
    int i;

    printf("Inserisci nome da carcare:");
    scanf("%s", nome);


    for (i=0; i<inventario.maxInv; i++){
        if (strcmp(inventario.vettInv[i].nome, nome) == 0){
            printf("%s %s %d %d %d %d %d %d\n", inventario.vettInv[i].nome, inventario.vettInv[i].tipo,
               inventario.vettInv[i].stats.hp, inventario.vettInv[i].stats.mp,
               inventario.vettInv[i].stats.atk, inventario.vettInv[i].stats.def,
               inventario.vettInv[i].stats.mag, inventario.vettInv[i].stats.spr);
        }



    }

}
