#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 50
#define MAX_S 1000
typedef enum{
    nuovoNodoDaTastiera,
    nuoviNodiDaFile,
    ricercaConCodice,
    cancellaPerCodice, //con estrazione
    cancellaPerDate,//con estrazione
    stampaSuFile,
    fine,
    err
} Scelte;

typedef struct{
    int gg;
    int mm;
    int aaaa;
}Data;

typedef struct{
    char codice[MAX]; //univoco
    char nome[MAX];
    char cognome[MAX];
    Data data;
    char via[MAX];
    char citta[MAX];
    int cap;
}Item;

typedef struct node{
    Item val;
    struct node *next;
}node_t, *link;

Scelte leggiScelta();
link newNode(Item val, link next);
link aggiungiOrdinato(link head, Item val);
void copiaVal(link dest, Item src);
Item creaItem(char *tmp);
int datacmp(Data data1, Data data2);
int traverse(link head);
link ricercaCod(link head, char *tmp);
Item cancellaCod(link *head, char *tmp);
Item cancellaPerD(link *head, Data d1, Data d2);
int traverseF(link head);

int main()
{
    int continua = 1;
    FILE *fp = fopen("anagrafica.txt", "r");
    Scelte scelta;
    link head = NULL;
    link xt;
    Item val, res;
    char tmp[MAX_S];
    Data d1, d2;

    while(continua){
        scelta = leggiScelta();
        switch(scelta){
            case nuovoNodoDaTastiera:
                printf("Inserisci Utente:");
                gets(tmp); //why
                gets(tmp);
                val = creaItem(tmp);
                head = aggiungiOrdinato(head, val);
                traverse(head);
                break;
            case nuoviNodiDaFile:
                while (fgets(tmp, MAX_S, fp) != NULL){
                    val = creaItem(tmp);
                    head = aggiungiOrdinato(head, val);
                }
                traverse(head);
                break;

            case ricercaConCodice:
                printf("Frate' inserisci codice: ");
                scanf("%s", tmp);
                xt = ricercaCod(head, tmp);
                if (xt == NULL)
                    printf("Non trovato\n");
                else
                    printf("%s %s %s\n", xt->val.codice, xt->val.nome, xt->val.cognome);
                break;
            case cancellaPerCodice:
                printf("Frate' inserisci codice da eliminare: ");
                scanf("%s", tmp);
                res = cancellaCod(&head, tmp);
                if (res.nome == NULL)
                    printf("Non trovato\n");
                else
                    printf("Eliminato: %s %s %s\n", res.codice, res.nome, res.cognome);
                traverse(head);
                break;
            case cancellaPerDate:
                printf("Inserisci Data Inizio: ");
                scanf("%d/%d/%d", &d1.gg, &d1.mm, &d1.aaaa);
                printf("Inserisci Data Fine: ");
                scanf("%d/%d/%d", &d2.gg, &d2.mm, &d2.aaaa);

                while(1){
                res = cancellaPerD(&head, d1, d2);
                    if (strcmp(res.nome, "xxx") == 0){
                        printf("Fine\n");
                        break;
                    }
                    else
                        printf("Eliminato: %s %s %s %d/%d/%d\n", res.codice, res.nome, res.cognome, res.data.gg, res.data.mm, res.data.aaaa);
                }
                traverse(head);
                break;
            case stampaSuFile:
                traverseF(head);
                break;
            case fine:
                continua = 0;
                printf("\nCia'");
                break;
            case err:
            default:
                printf("Comando Incorretto! (Case Sensitive)\n");
        }
    }



    return 0;
}

Scelte leggiScelta(){
    Scelte s;
    char scl[MAX];
    char *tab[err] = {"nuovoNodoDaTastiera", "nuoviNodiDaFile", "ricercaConCodice", "cancellaPerCodice", "cancellaPerDate", "stampaSuFile", "fine"};
    printf("\nScegli: \n-nuovoNodoDaTastiera\n-nuoviNodiDaFile\n-ricercaConCodice\n-cancellaPerCodice\n-cancellaPerDate\n-stampaSuFile\n-fine\n=>");
    scanf("%s", scl);

    s = nuovoNodoDaTastiera;
    while (s<err && strcmp(scl, tab[s])!=0)
        s++;

    return s;
}

link newNode(Item val, link next){
    link x;
    x = malloc(sizeof(*x));
    copiaVal(x, val);
    x->next = next;
    return x;
}

void copiaVal(link dest, Item src){
    strcpy(dest->val.codice, src.codice);
    strcpy(dest->val.nome, src.nome);
    strcpy(dest->val.cognome, src.cognome);
    strcpy(dest->val.citta, src.citta);
    strcpy(dest->val.via, src.via);

    dest->val.data.gg = src.data.gg;
    dest->val.data.mm = src.data.mm;
    dest->val.data.aaaa = src.data.aaaa;

    dest->val.cap = src.cap;

}

Item creaItem(char *tmp){
    Item val;
    sscanf(tmp, "%s %s %s %d/%d/%d %s %s %d", val.codice, val.nome, val.cognome, &val.data.gg, &val.data.mm, &val.data.aaaa, val.via, val.citta, &val.cap);
    return val;
}

link aggiungiOrdinato(link head, Item val){
    link x, p;
    int prova = 0;

    if (head == NULL || datacmp(val.data, head->val.data)>0){
        return newNode(val, head);
    }

    for(x=head->next, p=head; x!=NULL && datacmp(val.data, x->val.data)<0; p=x, x=x->next){
        prova++;
    }
    p->next = newNode(val, x);
    return head;
}

int datacmp(Data data1, Data data2){
    if (data1.aaaa > data2.aaaa){
        return 1;
    }
    else if (data1.aaaa == data2.aaaa){
        if (data1.mm > data2.mm){
            return 1;
        }
        else if(data1.mm == data2.mm){
            if (data1.gg > data2.gg){
                return 1;
            }
            else if (data1.gg == data2.gg){
                 return 0;
            }
        }
    }

    return -1;
}

int traverse(link head){
    link x;
    int len = 0;
    for(x=head; x!=NULL; x=x->next){
        printf("%s %s %d/%d/%d\n", x->val.nome, x->val.cognome, x->val.data.gg, x->val.data.mm, x->val.data.aaaa);
        len++;
    }
    return len;
}

link ricercaCod(link head, char *tmp){
    link x;
    for(x=head; x!=NULL; x=x->next){
        if (strcmp(tmp, x->val.codice) == 0){
            return x;
        }
    }
    return NULL;
}

Item cancellaCod(link *head, char *tmp){
    link *x, *p, t;
    Item temp;

    for(x=head, p=NULL; (*x)!=NULL; p=&(*x), x=&((*x)->next)){
        if (strcmp(tmp, (*x)->val.codice) == 0){
            if (*x == *head){
                t = *head;
                *head = (*head)->next;
                temp = t->val;
                free(t);
            }
            else{
                t = *x;
                (*p)->next = (*x)->next;
                temp = t->val;
                free(t);
                }
        }
    }
    return temp;
}

Item cancellaPerD(link *head, Data d1, Data d2){
    link *x, *p, t;
    Item res;
    Item null;
    strcpy(null.nome, "xxx");

    for(x=head, p=NULL; (*x)!=NULL; p=&(*x), x=&((*x)->next)){

        if (datacmp(d1, (*x)->val.data) < 0){
            if (datacmp(d2, (*x)->val.data) > 0){
                if (*x == *head){
                    t = *head;
                    *head = (*head)->next;
                    res = t->val;
                    free(t);
                }
                else{
                    t = *x;
                    (*p)->next = (*x)->next;
                    res = t->val;
                    free(t);
                }
                return res;
            }

        }
    }
    return null;
}

int traverseF(link head){
    link x;
    int len = 0;
    FILE *fo = fopen("FileStampa.txt", "w");
    for(x=head; x!=NULL; x=x->next){
        fprintf(fo, "%s %s %d/%d/%d\n", x->val.nome, x->val.cognome, x->val.data.gg, x->val.data.mm, x->val.data.aaaa);
        len++;
    }
    fclose(fo);
    return len;
}

