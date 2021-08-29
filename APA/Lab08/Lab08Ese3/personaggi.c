#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "personaggi.h"

link newNode(pg_t val, link next) {
    link x = malloc(sizeof(*x));
    x->val = val;
    x->next = next;
    return x;
}

tabPg_t *listInsert(tabPg_t *personaggi,  pg_t val) {
    link x;
    if(personaggi->headPg == NULL) {
        x = newNode(val, NULL);
        x->val.equip.vettEq = malloc(8*sizeof(inv_t));
        x->val.equip.inUso = 0;
        personaggi->headPg = x;
        personaggi->tailPg = x;
    }
    else {
        x = newNode(val, NULL);
        x->val.equip.vettEq = malloc(8*sizeof(inv_t));
        personaggi->tailPg->next = x;
        personaggi->tailPg = x;
    }
    return personaggi;
}


void stampaLista(tabPg_t personaggi){
    link x;
    for (x=personaggi.headPg; x!=NULL; x=x->next) {
        printf("%s %s %s %d %d %d %d %d %d\n", x->val.codice, x->val.nome, x->val.classe,
               x->val.stats.hp, x->val.stats.mp, x->val.stats.atk,
               x->val.stats.def, x->val.stats.mag, x->val.stats.spr);
    }
}

void caricaP(tabPg_t *personaggi){
    FILE *fp = fopen("pg.txt", "r");
    pg_t val;
    while (fscanf(fp, "%s %s %s %d %d %d %d %d %d", val.codice, val.nome, val.classe,
                  &val.stats.hp, &val.stats.mp, &val.stats.atk,
                  &val.stats.def, &val.stats.mag, &val.stats.spr) != EOF) {
        val.equip.inUso = 0;
        listInsert(personaggi, val);
        personaggi->nPg = personaggi->nPg + 1;
    }
    stampaLista(*personaggi);
}

void aggiungiP(tabPg_t *personaggi){
    pg_t val;
    char dati[MAX];
    printf("Inserisci dati: ");
    gets(dati);
    gets(dati);
    sscanf(dati, "%s %s %s %d %d %d %d %d %d", val.codice, val.nome, val.classe,
           &val.stats.hp, &val.stats.mp, &val.stats.atk,
           &val.stats.def, &val.stats.mag, &val.stats.spr);
    val.equip.inUso = 0;
    personaggi = listInsert(personaggi, val);
    personaggi->nPg = personaggi->nPg + 1;

    stampaLista(*personaggi);


}

void eliminaP(tabPg_t *personaggi){
    char code[MAX];
    link x, p;

    printf("Inserisci codice da eliminare:");
    scanf("%s", code);

    for (x=personaggi->headPg, p=NULL; x!=NULL; p=x, x=x->next) {
        if (strcmp(x->val.codice, code) == 0) {
            if (p == NULL) {
                personaggi->headPg = personaggi->headPg->next;
            }
            else {
                p->next = x->next;
            }
            free(x);
            break;
        }
    }
    if (x==NULL) {
        printf("Personaggio non trovato\n");
    }

    stampaLista(*personaggi);
}

void ricercaP(tabPg_t *personaggi){
    char code[MAX];
    link x;

    printf("Inserisci codice da carcare:");
    scanf("%s", code);

    for (x=personaggi->headPg; x!=NULL; x=x->next) {
        if (strcmp(x->val.codice, code) == 0) {
            printf("%s %s %s %d %d %d %d %d %d\n", x->val.codice, x->val.nome, x->val.classe,
               x->val.stats.hp, x->val.stats.mp, x->val.stats.atk,
               x->val.stats.def, x->val.stats.mag, x->val.stats.spr);
        printf("Equipaggiamento: \n");
        stampaEqPers(*personaggi, code);
            return;
        }
    }
    if (x==NULL) {
        printf("Personaggio non trovato\n");
    }
}

void stampaEqPers(tabPg_t personaggi,char *code){
    link x;
    int i;

    for (x=personaggi.headPg; x!=NULL; x = x->next) {
        if (strcmp(x->val.codice, code)==0) {
            for (i=0; i<x->val.equip.inUso; i++) {
                printf("%s %s %d %d %d %d %d %d\n", x->val.equip.vettEq[i].nome, x->val.equip.vettEq[i].tipo, x->val.equip.vettEq[i].stats.hp,
                       x->val.equip.vettEq[i].stats.mp, x->val.equip.vettEq[i].stats.atk, x->val.equip.vettEq[i].stats.def,
                       x->val.equip.vettEq[i].stats.mag, x->val.equip.vettEq[i].stats.spr);
            }
            break;
        }
    }
}


void modificaEq(tabPg_t *personaggi, tabInv_t *inventario){
    int scelta, i;
    char code[MAX];
    char nome[MAX];
    link x;

    printf("Inserisci codice personaggio:");
    scanf("%s", code);
    printf("Aggiungere(1) o rimuovere(0)?\n--> ");
    scanf("%d", &scelta);

    for (x=personaggi->headPg; x!=NULL; x=x->next) {
        if (strcmp(x->val.codice, code) == 0) {
            if (scelta == 1) { //aggiungi
                printf("Quale aggiungere?\n");
                stampaInv(*inventario);
                scanf("%s", nome);
                for (i=0; i<inventario->maxInv; i++) {
                    if (strcmp(inventario->vettInv[i].nome, nome) == 0) {
                        x->val.equip.vettEq[x->val.equip.inUso] = inventario->vettInv[i];
                        (x->val.equip.inUso)++;
                        break;
                    }
                }
            }
            else {            //rimuovere
                printf("Quale rimuovere?\n");
                stampaEqPers(*personaggi, code);
                scanf("%s", nome);
                for (i=0; i<x->val.equip.inUso; i++) {
                    if (strcmp(nome, x->val.equip.vettEq[i].nome) == 0) {
                        x->val.equip.vettEq[i] = x->val.equip.vettEq[x->val.equip.inUso-1];
                        (x->val.equip.inUso)--;
                        break;
                    }
                }
            }
            break;
        }
    }
    stampaEqPers(*personaggi, code);
}
