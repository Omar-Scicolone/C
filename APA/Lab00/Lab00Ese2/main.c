#include <stdio.h>
#include <stdlib.h>
#define LEN 20

int conta(char tmp[20], int n){
    int i, j, voc = 0, sub = 0, flag1 = 0;
    for (i=0; i<LEN && /*tmp[i] != '\0' &&*/ flag1 == 0; i++){
        for (j = 0; j<n; j++){
            if (tmp[i+j] != '\0'){
           switch (tmp[i+j]){
               case 'A':
               case 'E':
               case 'I':
               case 'O':
               case 'U':
               case 'a':
               case 'e':
               case 'i':
               case 'o':
               case 'u':
                   voc++;
                   break;
           }
            }
            else{
                flag1 = 1;
            }
        }
        if (voc == 2){
            sub++;
        }
        voc = 0;
    }
    printf("Word %s have %d subString with 2 vocal \n", tmp, sub);
    return  0;
}

int main()
{
    char name[LEN], tmp [LEN];
    int n, N, val = 0;
    FILE *fp;

    printf("Insert name's file: ");
    scanf("%s", name);
    printf("Insert lenght's substr: ");
    scanf("%d", &n);

    fp = fopen (name, "r");
    fscanf(fp, "%d", &N);

    while (fscanf(fp, "%s", tmp) != EOF){
       val += conta(tmp, n);
    }

    return 0;
}
