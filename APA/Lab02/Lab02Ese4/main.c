#include <stdio.h>
#include <stdlib.h>
#define MAX 50
void selectionSort(int selSort[MAX], int k);
void insertionSort(int insSort[MAX], int k);
void shellSort(int sheSort[MAX], int k);

int main() {
    int nSeq, i=0, j, k;
    int selSort[MAX], sheSort[MAX], insSort[MAX];
    FILE *fp;

    fp = fopen("sort.txt", "r");
    fscanf(fp, "%d", &nSeq);

    while(i<nSeq) {
        fscanf(fp, "%d", &k);
        for (j=0; j<k; j++) {
            fscanf(fp, "%d", &selSort[j]);
        }

        for (j=0; j<k; j++) {
            insSort[j] = selSort[j];
            sheSort[j] = selSort[j];
        }

        printf("Per la sequenza: ");
        for (j=0; j<k; j++) {
            printf(" %d ", selSort[j]);
        }
        printf("\n");

        selectionSort(selSort, k);
        insertionSort(insSort, k);
        shellSort(sheSort, k);

        printf("Sequenza ordinata: \n");
        for (j=0; j<k; j++) {
            printf("%d ", sheSort[j]);
        }
        printf("\n \n");

        i++;
        printf("***********************************************\n");
    }

    return 0;
}

void selectionSort(int selSort[MAX], int k) {
    int i, j, l=0, r=k-1, min;
    int tmp;
    int contI=0, contJ=0, contScambi=0;
    printf("Selection Sort: \n");

    for (i=l; i<r; i++) {
        contI++;
        min = i;
        contJ = 0;
        for (j=i+l; j<= r; j++) {
             contJ++;
            if (selSort[j] < selSort[min])
                min = j;
        }

        if (min != i) {
            tmp = selSort[i];
            selSort[i] = selSort[min];
            selSort[min] = tmp;
            contScambi++;
        }
        printf("Iterazioni ciclo interno nel ciclo esterno %d = %d\n", contI, contJ);
    }
    printf("Numero scambi: %d\n\n", contScambi);
}

void insertionSort(int insSort[MAX], int k){
    int i, j, l=0, r=k-1;
    int x;
    int contI=0, contJ=0, contScambi=0;
    printf("Insertion Sort: \n");

    for (i=l+1; i<=r; i++){
        contI++;
        x = insSort[i];
        j = i-1;
        contJ = 0;
        while(j>= l && x < insSort[j]){
            contJ++;
            insSort[j+1] = insSort[j];
            contScambi++;
            j--;
        }
        insSort[j+1] = x;
        printf("Iterazioni ciclo interno nel ciclo esterno %d = %d\n", contI, contJ);
    }
    printf("Numero scambi: %d\n\n", contScambi);
}



void shellSort(int sheSort[MAX], int k){
    int i, j, l=0, r=k-1, h=1;
    int contI=0, contJ=0, contScambi=0;
    printf("Shell Sort: \n");
    int tmp;
    while (h<k/3){
        h = 3*h+1;
    }
    while (h >= 1){
        for(i=l+h; i<=r; i++){
            contI++;
            j = i;
            tmp = sheSort[i];
            while (j>= l+h && tmp < sheSort[j-h]){
                contJ++;
                sheSort[j] = sheSort[j-h];
                contScambi++;
                j -= h;
            }
            sheSort[j] = tmp;
            printf("Iterazioni ciclo interno nel ciclo esterno %d = %d\n", contI, contJ);
        }
        h = h/3;
    }
    printf("Numero scambi: %d\n\n", contScambi);
}
