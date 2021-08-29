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
    r_stampa,
    r_ordine_data,
    r_ordine_tratta,
    r_ordine_partenza,
    r_ordine_arrivo,
    r_ricerca_partenza,
    r_nuovoFile,
    r_fine,
    r_err
} comandi_e;

typedef enum {
    s_video,
    s_file,
    s_err
} scelta;

typedef enum {
    s_o_data,
    s_o_tratta,
    s_o_partenza,
    s_o_arrivo,
    s_o_err
} scelta_ordine;

typedef enum {
    non_ordinato,
    o_tratta,
    o_partenze,
    o_arrivo,
    o_date
} stato;

typedef struct corse {
    char codice_tratta [MAX_STRING];
    char partenza [MAX_STRING];
    char destinazione [MAX_STRING];
    char data [MAX_STRING];
    char ora_partenza [MAX_STRING];
    char ora_arrivo [MAX_STRING];
    int ritardo;
} Corse;

void copiaCorse (Corse corse[MAX], Corse *ord, int i);


comandi_e leggiComando(void);
void date(char data_in[MAX], char data_fin[MAX], Corse corse[MAX], int nRighe, int rit);
void partenza(char riga[MAX], Corse corse[MAX], int nRighe);
void capolinea(char riga[MAX], Corse corse[MAX], int nRighe);
void ritardo(char riga[MAX], Corse corse[MAX], int nRighe);
void ritardo_tot(char riga[MAX], Corse corse[MAX], int nRighe);
void ordinaTratta(Corse *corse, int nRighe);
void ordinaPartenza(Corse *corse, int nRighe);
void ordinaArrivo(Corse *corse, int nRighe);
void ordinaDate(Corse *corse, int nRighe);
void shift(Corse * x1, Corse * x2);
void stampa(Corse corse[MAX], int nRighe);
void ricercaLineare(Corse corse[MAX], int nRighe);
void ricercaDicotomica(Corse corse[MAX], int nRighe);
void leggiFile(FILE *fp, Corse corse[MAX]);

int nRighe;
Corse *ordTratta;
Corse *ordPartenza;
Corse *ordArrivo;
Corse *ordDate;

int main() {
    comandi_e codiceComando;
    scelta_ordine ordineScelto;
    char *tabOrd[s_o_err] = {"Data", "Tratta", "Partenza", "Arrivo"};
    int cont = 1;
    char sclt_ordine[MAX];
    FILE *fp;
    char spazio, nomeFile[MAX];
    Corse corse[MAX];
    int continua = 1;
    char riga[MAX], data_in[MAX], data_fin[MAX];
    stato st = non_ordinato;

    fp = fopen("corse.txt", "r");

    printf("Benvenuto nel servizio DuttuSugnuBabbuBus\n");
    printf("Ecco i nostri viaggi\n");

    leggiFile(fp, corse);
    while(continua) {
        codiceComando = leggiComando();

        switch (codiceComando) {
        case r_date:
            printf("Inserire data inizio (gg/mm/aaaa): ");
            scanf("%s", data_in);
            printf("Inserire data fine (gg/mm/aaaa): ");
            scanf("%s", data_fin);
            date(data_in, data_fin, corse, nRighe, 0);
            break;
        case r_partenza:
            printf("Inserire stazione di partenza: ");
            spazio = getchar();
            gets(riga);
            partenza(riga, corse, nRighe);
            break;
        case r_capolinea:
            spazio = getchar();
            printf("Inserire stazione di arrivo: ");
            gets(riga);
            capolinea(riga, corse, nRighe);
            break;
        case r_ritardo:
            printf("Inserire data inizio (gg/mm/aaaa): ");
            scanf("%s", data_in);
            printf("Inserire data fine (gg/mm/aaaa): ");
            scanf("%s", data_fin);
            date(data_in, data_fin, corse, nRighe, 1);
            break;
        case r_ritardo_tot:
            spazio = getchar();
            printf("Inserire tratta: ");
            gets(riga);
            ritardo_tot(riga, corse, nRighe);
            break;
        case r_ordine_data:
            ordinaDate(ordDate, nRighe);
            break;
        case r_ordine_tratta:
            ordinaTratta(ordTratta, nRighe);
            st = o_tratta;
            break;
        case r_ordine_partenza:
            ordinaPartenza(ordPartenza, nRighe);
            st = o_partenze;
            break;
        case r_ordine_arrivo:
            ordinaArrivo(ordArrivo, nRighe);
            st = o_arrivo;
            break;
        case r_ricerca_partenza:
            if (st == o_partenze) {
                ricercaDicotomica(corse, nRighe);
            }
            else
                ricercaLineare(corse, nRighe);
            break;
        case r_stampa:
            cont = 1;
            while (cont) {
                printf("Quale ordine stampare? Data/Tratta/Partenza/Arrivo \n----> ");
                scanf("%s", sclt_ordine);
                ordineScelto = s_o_data;
                while (ordineScelto < s_o_err && strcmp(sclt_ordine, tabOrd[ordineScelto])!=0) {
                    ordineScelto++;
                }
                switch (ordineScelto) {
                case s_o_data:
                    stampa(ordDate, nRighe);
                    cont = 0;
                    break;
                case s_o_tratta:
                    stampa(ordTratta, nRighe);
                    cont = 0;
                    break;
                case s_o_partenza:
                    stampa(ordPartenza, nRighe);
                    cont = 0;
                    break;
                case s_o_arrivo:
                    stampa(ordArrivo, nRighe);
                    cont = 0;
                    break;
                case s_o_err:
                default:
                    printf("Comando errato (case sensitive)\n");
                }
            }
            break;
        case r_nuovoFile:
            printf("Inserisci nome nuovo file: "); //MANCA IL NUOVO FILE
            scanf("%s", nomeFile);
            fclose(fp);
            fp = fopen(nomeFile, "r");
            free(ordArrivo);
            free(ordPartenza);
            free(ordTratta);
            free(ordArrivo);
            leggiFile(fp, corse);
            break;
        case r_fine:
            printf("Arrivederci!");
            continua = 0;
            break;
        case r_err:
        default:
            printf("Comando errato (case sensitive)\n");
        }
    }
    spazio = spazio + 1; //solo per far scomparire il warning
    return 0;
}

comandi_e leggiComando(void) {
    comandi_e c;
    char cmd[MAX];
    char *tabella[r_err] = {"date", "partenza", "capolinea", "ritardo", "ritardo_tot", "stampa", "ordine_data", "ordine_tratta", "ordine_partenza", "ordine_arrivo", "ricerca_partenza", "nuovo_File", "fine"};
    printf("\nInserire un comando tra: \n-date\n-partenza\n-capolinea\n-ritardo\n-ritardo_tot\n-stampa\n-ordine_data\n-ordine_tratta\n-ordine_partenza\n-ordine_arrivo\n-ricerca_partenza\n-nuovo_File\n-fine\n----> ");
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
void ordinaTratta(Corse *corse, int nRighe) {
    int i, j, l=0, r = nRighe -1;
    Corse tmp;
    for (i=0; i<r; i++) {
        for (j=0; j<r-(i-l); j++) {
            if (strcmp(corse[j].codice_tratta, corse[j+1].codice_tratta) > 0) {
                shift(&tmp, &corse[j]);
                shift(&corse[j], &corse[j+1]);
                shift(&corse[j+1], &tmp);
            }
        }
    }
    printf("Ordinato per codici tratte!\n");

}

void ordinaPartenza(Corse *corse, int nRighe) {
    int i, j, l=0, r = nRighe -1;
    Corse tmp;
    for (i=0; i<r; i++) {
        for (j=0; j<r-(i-l); j++) {
            if (strcmp(corse[j].partenza, corse[j+1].partenza) > 0) {
                shift(&tmp, &corse[j]);
                shift(&corse[j], &corse[j+1]);
                shift(&corse[j+1], &tmp);
            }
        }
    }
    printf("Ordinato per partenze!\n");
}

void ordinaArrivo(Corse *corse, int nRighe) {
    int i, j, l=0, r = nRighe -1;
    Corse tmp;
    for (i=0; i<r; i++) {
        for (j=0; j<r-(i-l); j++) {
            if (strcmp(corse[j].destinazione, corse[j+1].destinazione) > 0) {
                shift(&tmp, &corse[j]);
                shift(&corse[j], &corse[j+1]);
                shift(&corse[j+1], &tmp);
            }
        }
    }
    printf("Ordinato per arrivi!\n");

}

void ordinaDate(Corse *corse, int nRighe) { //in realtà non è più corse, bensi il vettore speciale per l'ordinamento
    int i, j, l=0, r = nRighe -1;
    Corse tmp;

    int giorno1, mese1, anno1;
    int giorno2, mese2, anno2;
    int k = 0;
    for (i=l; i<r; i++) {
        for (j=l; j<r-(i-l); j++) {
            giorno1 = 0;
            mese1 = 0;
            anno1 = 0;
            giorno2 = 0;
            mese2 = 0;
            anno2 = 0;
            k = 0;

            while (corse[j].data[k] != '/') {
                giorno1 = giorno1*10;
                giorno1 += corse[j].data[k]-48;
                k++;
            }
            k++;
            while (corse[j].data[k]!='/') {
                mese1 = mese1*10;
                mese1 += corse[j].data[k]-48;
                k++;
            }
            k++;
            while (corse[j].data[k]!='/'&& corse[j].data[k]!='\0') {
                anno1 = anno1*10;
                anno1 += corse[j].data[k]-48;
                k++;
            }
            k=0;
            while (corse[j+1].data[k]!='/') {
                giorno2 = giorno2*10;
                giorno2 += corse[j+1].data[k]-48;
                k++;
            }
            k++;
            while (corse[j+1].data[k]!='/') {
                mese2 = mese2*10;
                mese2 += corse[j+1].data[k]-48;
                k++;
            }
            k++;
            while (corse[j+1].data[k]!='/' && corse[j+1].data[k]!='\0') {
                anno2 = anno2*10;
                anno2 += corse[j+1].data[k]-48;
                k++;
            }

            if (anno1 > anno2) {
                shift(&tmp, &corse[j]);
                shift(&corse[j], &corse[j+1]);
                shift(&corse[j+1], &tmp);
            }
            else if (anno1 == anno2) {
                if (mese1 > mese2) {
                    shift(&tmp, &corse[j]);
                    shift(&corse[j], &corse[j+1]);
                    shift(&corse[j+1], &tmp);
                }
                else if (mese1 == mese2) {
                    if (giorno1 > giorno2) {
                        shift(&tmp, &corse[j]);
                        shift(&corse[j], &corse[j+1]);
                        shift(&corse[j+1], &tmp);
                    }
                }
            }
        }
    }
    printf("Ordinato per date!\n");

}



void shift(Corse *x1, Corse *x2) {
    strcpy(x1[0].codice_tratta, x2[0].codice_tratta);
    strcpy(x1[0].partenza, x2[0].partenza);
    strcpy(x1[0].destinazione, x2[0].destinazione);
    strcpy(x1[0].data, x2[0].data);
    strcpy(x1[0].ora_partenza, x2[0].ora_partenza);
    strcpy(x1[0].ora_arrivo, x2[0].ora_arrivo);
    x1[0].ritardo = x2[0].ritardo;
}

void stampa(Corse corse[MAX], int nRighe) {
    scelta s;
    int i, continua = 1;
    FILE *fp;
    fp = fopen("log.txt", "w");
    char scl[MAX];
    char *tabella[s_err] = {"Video", "File"};

    while (continua) {
        printf("Dove stampare? File/Video\n----> ");
        scanf("%s", scl);

        s = s_video;
        while (s<s_err && strcmp(scl, tabella[s])!=0) {
            s++;
        }
        switch (s) {
        case s_video:
            for (i=0; i<nRighe; i++) {
                printf("%s %s %s %s %s %s %d\n", corse[i].codice_tratta, corse[i].partenza, corse[i].destinazione, corse[i].data, corse[i].ora_arrivo, corse[i].ora_partenza, corse[i].ritardo);
                continua = 0;
            }
            break;
        case s_file:
            for (i=0; i<nRighe; i++) {
                fprintf(fp, "%s %s %s %s %s %s %d\n", corse[i].codice_tratta, corse[i].partenza, corse[i].destinazione, corse[i].data, corse[i].ora_arrivo, corse[i].ora_partenza, corse[i].ritardo);
                continua = 0;
            }
            break;
        case s_err:
        default:
            printf("Comando errato (case sensitive)\n");
        }
    }
}
void ricercaLineare(Corse corse[MAX], int nRighe) {
    char str[MAX];
    int i = 0;
    int r = nRighe;
    int found = 0;

    printf("Ricerca stazione partenza: ");
    scanf("%s", str);

    while (i <=r && found == 0) {
        if (strstr(corse[i].partenza, str)) {
            found = 1;
        }
        else
            i++;

    }

    if (found == 0)
        printf("Non trovato");
    else
        printf("%s %s %s %s %s %s %d\n", corse[i].codice_tratta, corse[i].partenza, corse[i].destinazione, corse[i].data, corse[i].ora_arrivo, corse[i].ora_partenza, corse[i].ritardo);
}

void ricercaDicotomica(Corse corse[MAX], int nRighe) {
    int m, flag = 0;
    int l = 0;
    int r = nRighe-1;
    char str[MAX];
    printf("Ricerca stazione partenza: ");
    scanf("%s", str);

    while (l<r && flag == 0) {
        m = (l+r)/2;
        if (strstr(corse[m].partenza, str)) {
            printf("%s %s %s %s %s %s %d\n", corse[m].codice_tratta, corse[m].partenza, corse[m].destinazione, corse[m].data, corse[m].ora_arrivo, corse[m].ora_partenza, corse[m].ritardo);
            flag = 1;
        }
        else
            r = m-1;
    }
    if(flag == 0) {
        printf("Non trovato");
    }
}

void copiaCorse (Corse corse[MAX], Corse *ord, int nRighe) {
    int i;
    for (i=0; i<nRighe; i++) {
        strcpy(ord[i].codice_tratta, corse[i].codice_tratta);
        strcpy(ord[i].partenza, corse[i].partenza);
        strcpy(ord[i].destinazione, corse[i].destinazione);
        strcpy(ord[i].data, corse[i].data);
        strcpy(ord[i].ora_partenza, corse[i].ora_partenza);
        strcpy(ord[i].ora_arrivo, corse[i].ora_arrivo);
        ord[i].ritardo = corse[i].ritardo;
    }

}

void leggiFile(FILE *fp, Corse corse[MAX]){
    int i;
    fscanf(fp, "%d", &nRighe);
    for (i=0; i<nRighe; i++) {
        fscanf(fp, "%s", corse[i].codice_tratta);
        fscanf(fp, "%s", corse[i].partenza);
        fscanf(fp, "%s", corse[i].destinazione);
        fscanf(fp, "%s", corse[i].data);
        fscanf(fp, "%s", corse[i].ora_partenza);
        fscanf(fp, "%s", corse[i].ora_arrivo);
        fscanf(fp, "%d", &corse[i].ritardo);
        printf("%s %s %s %s %s %s %d \n", corse[i].codice_tratta, corse[i].partenza, corse[i].destinazione, corse[i].data, corse[i].ora_arrivo, corse[i].ora_partenza, corse[i].ritardo);
    }

    ordTratta = malloc(nRighe*sizeof(Corse));
    copiaCorse(corse, ordTratta, nRighe);

    ordArrivo = malloc(nRighe*sizeof(Corse));
    copiaCorse(corse, ordArrivo, nRighe);

    ordDate = malloc(nRighe*sizeof(Corse));
    copiaCorse(corse, ordDate, nRighe);

    ordPartenza = malloc(nRighe*sizeof(Corse));
    copiaCorse(corse, ordPartenza, nRighe);
}
