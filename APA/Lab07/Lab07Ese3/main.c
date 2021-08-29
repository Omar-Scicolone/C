#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 50
typedef enum {
    caricaPersonaggi,
    caricaOggetti,
    aggiungiPersonaggio,
    eliminaPersonaggio,
    modificaEquip,
    stats,
    fine,
    err
} Scelte;
Scelte sceglicomando();

typedef struct {
    int hp, mp, atk, def, mag, spr;
} Statistiche;

typedef struct {
    char nome[MAX];
    char tipo[MAX];
    Statistiche stats;
} Oggetto;

typedef struct {
    Oggetto *oggetti;
    //int nInv;
    int maxInv;
} invWrapper;

typedef struct {
    int inUso;
    Oggetto *oggetti;
} Equipaggiamento;

typedef struct {
    char codice[MAX];
    char nome[MAX];
    char classe[MAX];
    Equipaggiamento equip;
    Statistiche stats;
} valPg;

typedef struct node {
    valPg val;
    struct node *next;
} NodoPg, *link;

typedef struct {
    link head;
    link tail;
    int nPg;
} listWrapper;


void caricaPers(listWrapper *lista);
link newNode(valPg val, link next);
listWrapper * listInsert(listWrapper *lista, valPg val);
void traverse(listWrapper lista);
void caricaOgg(invWrapper *inventario);
void stampaInv(invWrapper inventario);
void aggiungiPers(listWrapper *lista);
void eliminaP(listWrapper *lista);
void modificaEq(listWrapper *lista, invWrapper *inventario);
void stampaEqPers(listWrapper lista, char code[MAX]);
void stampaStatPers(listWrapper lista);

int main()
{
    listWrapper lista = {NULL, NULL, 0};
    invWrapper inventario = {NULL, 0};
    Scelte scelta;
    printf("BENVENUTO A FINAL FETO!\n");
    int continua = 1;
    while(continua) {
        scelta = sceglicomando();
        switch(scelta) {
        case caricaPersonaggi:
            caricaPers(&lista);
            traverse(lista);
            break;
        case caricaOggetti:
            caricaOgg(&inventario);
            stampaInv(inventario);
            break;
        case aggiungiPersonaggio:
            aggiungiPers(&lista);
            traverse(lista);
            break;
        case eliminaPersonaggio:
            eliminaP(&lista);
            traverse(lista);
            break;
        case modificaEquip:
            modificaEq(&lista, &inventario);
            break;
        case stats:
            stampaStatPers(lista);
            break;
        case fine:
            printf("Arrivederci!");
            continua = 0;
            break;
        case err:
        default:
            printf("Comando errato, riprova");
            break;
        }
        printf("\n");
    }

    return 0;
}

Scelte sceglicomando() {
    char *tabella[err] = {"caricaPersonaggi", "caricaOggetti", "aggiungiPersonaggio", "eliminaPersonaggio", "modificaEquip", "stats", "fine"};
    char c[MAX];
    Scelte scelta;

    printf("-caricaPersonaggi\n-caricaOggetti\n-aggiungiPersonaggio\n-eliminaPersonaggio\n-modificaEquip\n-stats\n-fine\n");
    printf("Effettua scelta:\n--> ");
    scanf("%s", c);

    for (scelta = caricaPersonaggi; scelta<err; scelta++) {
        if (strcmp(c, tabella[scelta])==0) {
            return scelta;
        }
    }

    return scelta;
}

link newNode(valPg val, link next) {
    link x = malloc(sizeof(*x));

    x->val = val;
    x->next = next;

    return x;
}

listWrapper *listInsert(listWrapper *lista, valPg val) {
    link x;

    if(lista->head == NULL) {
        x = newNode(val, NULL);
        x->val.equip.oggetti = malloc(8*sizeof(Oggetto));
        x->val.equip.inUso = 0;
        lista->head = x;
        lista->tail = x;
    }

    else {
        x = newNode(val, NULL);
        x->val.equip.oggetti = malloc(8*sizeof(Oggetto));
        lista->tail->next = x;
        lista->tail = x;
    }

    return lista;
}

void caricaPers(listWrapper *lista) {
    FILE *fp = fopen("pg.txt", "r");
    valPg val;
    while (fscanf(fp, "%s %s %s %d %d %d %d %d %d", val.codice, val.nome, val.classe,
                  &val.stats.hp, &val.stats.mp, &val.stats.atk,
                  &val.stats.def, &val.stats.mag, &val.stats.spr) != EOF) {
        listInsert(lista, val);
        lista->nPg = lista->nPg + 1;
    }
}

void traverse(listWrapper lista) {
    link x;

    for (x=lista.head; x!=NULL; x=x->next) {
        printf("%s %s %s %d %d %d %d %d %d\n", x->val.codice, x->val.nome, x->val.classe,
               x->val.stats.hp, x->val.stats.mp, x->val.stats.atk,
               x->val.stats.def, x->val.stats.mag, x->val.stats.spr);
    }


}

void caricaOgg(invWrapper *inventario) {
    FILE *fp = fopen("inventario.txt", "r");
    int i;

    fscanf(fp, "%d", &inventario->maxInv);

    inventario->oggetti = malloc(inventario->maxInv*sizeof(Oggetto));

    for (i=0; i<inventario->maxInv; i++)
        fscanf(fp, "%s %s %d %d %d %d %d %d", inventario->oggetti[i].nome, inventario->oggetti[i].tipo, &inventario->oggetti[i].stats.hp,
               &inventario->oggetti[i].stats.mp, &inventario->oggetti[i].stats.atk, &inventario->oggetti[i].stats.def,
               &inventario->oggetti[i].stats.mag, &inventario->oggetti[i].stats.spr);
}

void stampaInv(invWrapper inventario) {
    int i;
    for (i=0; i<inventario.maxInv; i++) {
        printf("%s %s %d %d %d %d %d %d\n", inventario.oggetti[i].nome, inventario.oggetti[i].tipo,
               inventario.oggetti[i].stats.hp, inventario.oggetti[i].stats.mp,
               inventario.oggetti[i].stats.atk, inventario.oggetti[i].stats.def,
               inventario.oggetti[i].stats.mag, inventario.oggetti[i].stats.spr);
    }

}

void aggiungiPers(listWrapper *lista) {
    valPg val;
    char dati[MAX];
    printf("Inserisci dati: ");
    gets(dati);
    gets(dati);
    sscanf(dati, "%s %s %s %d %d %d %d %d %d", val.codice, val.nome, val.classe,
           &val.stats.hp, &val.stats.mp, &val.stats.atk,
           &val.stats.def, &val.stats.mag, &val.stats.spr);
    lista = listInsert(lista, val);
    lista->nPg = lista->nPg + 1;
}

void eliminaP(listWrapper *lista) {
    char code[MAX];
    link x, p;

    printf("Inserisci codice da eliminare:");
    scanf("%s", code);

    for (x=lista->head, p=NULL; x!=NULL; p=x, x=x->next) {
        if (strcmp(x->val.codice, code) == 0) {
            if (p == NULL) {
                lista->head = lista->head->next;
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
}

void stampaEqPers(listWrapper lista, char code[MAX]) {
    link x;
    int i;

    for (x=lista.head; x!=NULL; x = x->next) {
        if (strcmp(x->val.codice, code)==0) {
            for (i=0; i<x->val.equip.inUso; i++) {
                printf("%s %s %d %d %d %d %d %d\n", x->val.equip.oggetti[i].nome, x->val.equip.oggetti[i].tipo, x->val.equip.oggetti[i].stats.hp,
                       x->val.equip.oggetti[i].stats.mp, x->val.equip.oggetti[i].stats.atk, x->val.equip.oggetti[i].stats.def,
                       x->val.equip.oggetti[i].stats.mag, x->val.equip.oggetti[i].stats.spr);
            }
            break;
        }
    }

}

void modificaEq(listWrapper *lista, invWrapper *inventario) {
    int scelta, i;
    char code[MAX];
    char nome[MAX];
    link x;


    printf("Inserisci codice personaggio:");
    scanf("%s", code);
    printf("Aggiungere(1) o rimuovere(0)?\n--> ");
    scanf("%d", &scelta);

    for (x=lista->head; x!=NULL; x=x->next) {
        if (strcmp(x->val.codice, code) == 0) {
            if (scelta == 1) { //aggiungi
                printf("Quale aggiungere?\n");
                stampaInv(*inventario);
                scanf("%s", nome);
                for (i=0; i<inventario->maxInv; i++) {
                    if (strcmp(inventario->oggetti[i].nome, nome) == 0) {
                        x->val.equip.oggetti[x->val.equip.inUso] = inventario->oggetti[i];
                        (x->val.equip.inUso)++;
//                        x->val.stats.atk += inventario->oggetti[i].stats.atk;
//                        x->val.stats.def += inventario->oggetti[i].stats.def;
//                        x->val.stats.hp += inventario->oggetti[i].stats.hp;
//                        x->val.stats.mp += inventario->oggetti[i].stats.mp;
//                        x->val.stats.mag += inventario->oggetti[i].stats.mag;
//                        x->val.stats.spr += inventario->oggetti[i].stats.spr;
                        break;
                    }
                }
            }
            else {            //rimuovere
                printf("Quale rimuovere?\n");
                stampaEqPers(*lista, code);
                scanf("%s", nome);
                for (i=0; i<x->val.equip.inUso; i++) {
                    if (strcmp(nome, x->val.equip.oggetti[i].nome) == 0) {
                        x->val.equip.oggetti[i] = x->val.equip.oggetti[x->val.equip.inUso-1];
                        (x->val.equip.inUso)--;
//                        x->val.stats.atk -= inventario->oggetti[i].stats.atk;
//                        x->val.stats.def -= inventario->oggetti[i].stats.def;
//                        x->val.stats.hp -= inventario->oggetti[i].stats.hp;
//                        x->val.stats.mp -= inventario->oggetti[i].stats.mp;
//                        x->val.stats.mag -= inventario->oggetti[i].stats.mag;
//                        x->val.stats.spr -= inventario->oggetti[i].stats.spr;
                        break;
                    }
                }
            }
            break;
        }
    }
    stampaEqPers(*lista, code);

}

void stampaStatPers(listWrapper lista) {
    link x;
    char code[MAX];
    printf("Scegli il codice del personaggio di cui stampare le stats\n-->");
    scanf("%s", code);
    int hp = 0, mp = 0, atk = 0, def = 0, mag = 0, spr = 0, i;


    for (x=lista.head; x!=NULL; x = x->next) {
        if (strcmp(x->val.codice, code)==0) {
            hp = x->val.stats.hp;
            mp = x->val.stats.mp;
            atk = x->val.stats.atk;
            def = x->val.stats.def;
            mag = x->val.stats.mag;
            spr = x->val.stats.spr;
            for(i=0; i<x->val.equip.inUso; i++){
                hp += x->val.equip.oggetti[i].stats.hp;
                mp += x->val.equip.oggetti[i].stats.mp;
                atk += x->val.equip.oggetti[i].stats.atk;
                def += x->val.equip.oggetti[i].stats.def;
                mag += x->val.equip.oggetti[i].stats.mag;
                spr += x->val.equip.oggetti[i].stats.spr;
            }
            if(hp<=0)
                hp=1;
            if(mp<=0)
                mp=1;
            if(atk<=0)
                atk=1;
            if(def<=0)
                def=1;
            if(mag<=0)
                mag=1;
            if(spr<=0)
                spr=1;
            printf("\nHP->%d \nMP->%d \nATK->%d \nDEF->%d \nMAG->%d \nSPR->%d\n", hp, mp, atk, def, mag, spr);
            break;
        }
    }

}


