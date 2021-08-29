#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STRING 30
#define MAX 1000

typedef enum {
    r_date,
    r_partenza,
    r_capolinea,
    r_ritardo,
    r_ritardo_tot,
    r_fine,
    r_err
} comandi_e;

typedef struct corse {
    char codice_tratta [MAX_STRING];
    char partenza [MAX_STRING];
    char destinazione [MAX_STRING];
    char data [MAX_STRING];
    char ora_partenza [MAX_STRING];
    char ora_arrivo [MAX_STRING];
    int ritardo;
} Corse;


comandi_e leggiComando(void);
void date(char data_in[MAX], char data_fin[MAX], Corse corse[MAX], int nRighe, int rit);
void partenza(char riga[MAX], Corse corse[MAX], int nRighe);
void capolinea(char riga[MAX], Corse corse[MAX], int nRighe);
void ritardo(char riga[MAX], Corse corse[MAX], int nRighe);
void ritardo_tot(char riga[MAX], Corse corse[MAX], int nRighe);

int main() {
    comandi_e codiceComando;
    FILE *fp;
    char spazio;
    int nRighe, i;
    Corse corse[MAX];
    int continua = 1;
    char riga[MAX], data_in[MAX], data_fin[MAX];

    fp = fopen("corse.txt", "r");
    fscanf(fp, "%d", &nRighe);

    printf("Benvenuto nel servizio DuttuSugnuBabbuBus\n");
    printf("Ecco i nostri viaggi\n");

    for (i=0; i<nRighe; i++) {
        fscanf(fp, "%s", corse[i].codice_tratta);
        fscanf(fp, "%s", corse[i].partenza);
        fscanf(fp, "%s", corse[i].destinazione);
        fscanf(fp, "%s", corse[i].data);
        fscanf(fp, "%s", corse[i].ora_partenza);
        fscanf(fp, "%s", corse[i].ora_arrivo);
        fscanf(fp, "%d", &corse[i].ritardo);
        printf("%s %s %s %s %s %s %d\n", corse[i].codice_tratta, corse[i].partenza, corse[i].destinazione, corse[i].data, corse[i].ora_arrivo, corse[i].ora_partenza, corse[i].ritardo);
    }

    while(continua) {
        codiceComando = leggiComando();

        switch (codiceComando) {
        case r_date:
            scanf("%s", data_in);
            scanf("%s", data_fin);
            date(data_in, data_fin, corse, nRighe, 0);
            break;
        case r_partenza:
            spazio = getchar();
            gets(riga);
            partenza(riga, corse, nRighe);
            break;
        case r_capolinea:
            spazio = getchar();
            gets(riga);
            capolinea(riga, corse, nRighe);
            break;
        case r_ritardo:
            scanf("%s", data_in);
            scanf("%s", data_fin);
            date(data_in, data_fin, corse, nRighe, 1);
            break;
        case r_ritardo_tot:
            spazio = getchar();
            gets(riga);
            ritardo_tot(riga, corse, nRighe);
            break;
        case r_fine:
            continua = 0;
            break;
        case r_err:
        default:
            printf("Comando errato (case sensitive)\n");
        }
    }
    return 0;
}

comandi_e leggiComando(void) {
    comandi_e c;
    char cmd[MAX];
    char *tabella[r_err] = {"date", "partenza", "capolinea", "ritardo", "ritardo_tot", "fine"};
    printf("\nInserire un comando tra: \ndate\npartenza\ncapolinea\nritardo\nritardo_tot\nfine\n");
    scanf("%s", cmd);

    c = r_date;
    while (c<r_err && strcmp(cmd, tabella[c])!=0) {
        c++;
    }

    return c;
}

void date(char data_in[MAX], char data_fin[MAX], Corse corse[MAX], int nRighe, int rit) {
    int giorno1=0, mese1=0, anno1=0;
    int giorno2=0, mese2=0, anno2=0;
    int i = 0, j = 0;
    char data[MAX];
    int giorno=0, mese=0, anno=0;

    //giorno1
    while (data_in[i]!='/') {
        giorno1 = giorno1*10;
        giorno1 += data_in[i]-48;
        i++;
    }

    i++;
    while (data_in[i]!='/') {
        mese1 = mese1*10;
        mese1 += data_in[i]-48;
        i++;
    }

    i++;
    while (data_in[i]!='/'&& data_in[i]!='\0') {
        anno1 = anno1*10;
        anno1 += data_in[i]-48;
        i++;
    }

    i=0;
    while (data_fin[i]!='/') {
        giorno2 = giorno2*10;
        giorno2 += data_fin[i]-48;
        i++;
    }

    i++;
    while (data_fin[i]!='/') {
        mese2 = mese2*10;
        mese2 += data_fin[i]-48;
        i++;
    }

    i++;
    while (data_fin[i]!='/' && data_fin[i]!='\0') {
        anno2 = anno2*10;
        anno2 += data_fin[i]-48;
        i++;
    }

    for(j=0; j<nRighe; j++) {
        int n = 0;
        int m = 0;
        i=0;
        strcpy(data, corse[j].data);

        giorno=0;
        mese=0;
        anno=0;

        while (data[i]!='/') {
            giorno = giorno*10;
            giorno += data[i]-48;
            i++;
        }
        i++;

        while (data[i]!='/') {
            mese = mese*10;
            mese += data[i]-48;
            i++;
        }
        i++;
        while (data[i]!='/' && data[i]!='\0') {
            anno = anno*10;
            anno += data[i]-48;
            i++;
        }

        n = (((anno-anno1)*12 + (mese-mese1))*30 + giorno - giorno1);
        m = (((anno2-anno1)*12 + (mese2-mese1))*30 + giorno2 - giorno1);

        if (n > 0 && n < m) {
            if(rit == 0) {
                printf("%s %s %s %s %s %s %d\n", corse[j].codice_tratta, corse[j].partenza, corse[j].destinazione, corse[j].data, corse[j].ora_arrivo, corse[j].ora_partenza, corse[j].ritardo);
            } else {
                if (corse[j].ritardo != 0) {
                    printf("%s %s %s %s %s %s %d\n", corse[j].codice_tratta, corse[j].partenza, corse[j].destinazione, corse[j].data, corse[j].ora_arrivo, corse[j].ora_partenza, corse[j].ritardo);
                }
            }
        }

    }
}

void partenza(char riga[MAX], Corse corse[MAX], int nRighe) {
    int j = 0;
    for (j=0; j<nRighe; j++) {
        if (strcmp(riga, corse[j].partenza) == 0 ) {
            printf("%s %s %s %s %s %s %d\n", corse[j].codice_tratta, corse[j].partenza, corse[j].destinazione, corse[j].data, corse[j].ora_arrivo, corse[j].ora_partenza, corse[j].ritardo);
        }
    }
}

void capolinea(char riga[MAX], Corse corse[MAX], int nRighe) {
    int j = 0;
    for (j=0; j<nRighe; j++) {
        if (strcmp(riga, corse[j].destinazione) == 0 ) {
            printf("%s %s %s %s %s %s %d\n", corse[j].codice_tratta, corse[j].partenza, corse[j].destinazione, corse[j].data, corse[j].ora_arrivo, corse[j].ora_partenza, corse[j].ritardo);
        }
    }
}

void ritardo_tot(char riga[MAX], Corse corse[MAX], int nRighe) {
    int rit_tot = 0, j;

    for (j=0; j<nRighe; j++) {
        if (strcmp(riga, corse[j].codice_tratta) == 0 ) {
                rit_tot += corse[j].ritardo;
        }
    }
    printf("La tratta %s ha accumulato %d minuti di ritardo", riga, rit_tot);
}


