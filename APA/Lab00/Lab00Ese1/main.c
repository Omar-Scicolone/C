#include <stdio.h>
#include <stdlib.h>

int main()
{
    const int N = 30;
    int vett[N];
    int i = 0, x = 0, flag = 0, count = 0, max = 0, j = 0;
    int tmp [N];

    while (flag == 0){
        printf("Insert number\n");
        scanf("%d", &x);
        vett[i] = x;
        i++;

        printf("Continue? yes = 0, no = 1\n");
        scanf("%d", &flag);

        if (i>30){
            flag = 1;
        }

    }

    for (x=0; x<i; x++){
        if (vett[x] == 0){
            if (max < count){
                max = count;
            }
            count = 0;
        }
        else {
            count++;
        }
    }
    printf ("MAX = %d\n", max);


    flag = 0;
    for (x=0; x<i; x++){
        if (vett [x] != 0){
            tmp[0] = vett[x];

            for (j = 1; j<max && flag == 0; j++){
                if (vett [x+j] != 0) {
                    tmp[j] = vett [x+j];
                }
                else {
                    flag = 1;
                }
           }
           if (flag == 0){
                printf("[");
                for (j=0; j<max; j++){
                    if (j == max-1){
                        printf("%d", tmp[j]);
                    }
                    else {
                        printf("%d ", tmp[j]);
                    }
                }
                printf("]");
                printf(" ");
           }
           else{
                flag = 0;
            for (j=0; j<max; j++){
                    tmp[j]=0;
                }
           }
        }

       else{

       }

    }

    return 0;
}
