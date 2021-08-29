#include <stdio.h>
#include <stdlib.h>
#define MAX 50
#include <string.h>
#include "personaggi.h"
#include "inventario.h"

typedef enum {
    caricaPersonaggi,
    aggiungiPersonaggio,
    eliminaPersonaggio,
    ricercaPersonaggio,
    modificaEquip,
    caricaOggetti,
    ricercaOggetto,
    fine,
    err
} Scelte;

Scelte sceglicomando();

int main()
{
    tabPg_t personaggi  = {NULL, NULL, 0};
    tabInv_t  inventario = {NULL, 0};

    Scelte scelta;
    printf("BENVENUTO A FINAL FETO!\n");
    int continua = 1;
    while(continua) {
        scelta = sceglicomando();
        switch(scelta) {
        case caricaPersonaggi:
            caricaP(&personaggi);
            break;
        case aggiungiPersonaggio:
            aggiungiP(&personaggi);
            break;
        case eliminaPersonaggio:
            eliminaP(&personaggi);
            break;
        case ricercaPersonaggio:
            ricercaP(&personaggi);
            break;
        case modificaEquip:
            modificaEq(&personaggi, &inventario);
            break;
        case caricaOggetti:
            caricaOgg(&inventario);
            break;
        case ricercaOggetto:
            ricercaO(inventario);
            break;
        case fine:
            continua = 0;
            break;
        case err:
        default:
            printf("Comando errato, riprova\n");
            break;
        }
        printf("\n");
    }

    return 0;
}

Scelte sceglicomando() {
    char *tabella[err] = {"caricaPersonaggi", "aggiungiPersonaggio", "eliminaPersonaggio", "ricercaPersonaggio", "modificaEquip", "caricaOggetti", "ricercaOggetto", "fine"};
    char c[MAX];
    Scelte scelta;

    printf("-caricaPersonaggi\n-aggiungiPersonaggio\n-eliminaPersonaggio\n-ricercaPersonaggio\n-modificaEquip\n-caricaOggetti\n-ricercaOggetto\n-fine\n");
    printf("Effettua scelta:\n--> ");
    scanf("%s", c);

    for (scelta = caricaPersonaggi; scelta<err; scelta++) {
        if (strcmp(c, tabella[scelta])==0) {
            return scelta;
        }
    }
    return scelta;
}
