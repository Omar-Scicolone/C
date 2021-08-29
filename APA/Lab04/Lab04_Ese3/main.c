#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX 50

char *cercaRegexp(char *src, char *regexp);
int reLen(char *regexp);
int controllaParola(char *src, char *regexp, int len);

int main() {
    char regexp [MAX] = "ABC[CDE]./a/A/a.[^cde]abc";
    char src [MAX] = "lololoABC[C]lololABCEqzScQfabclololo";
    char *toP;
    int len = reLen(regexp), i;

    printf("Espressione regolare: %s", regexp);
    printf("\nNella stringa: %s", src);

    toP = cercaRegexp(src, regexp);

    if (toP != NULL){
        printf("\nTrovata sottostringa: ");
        for (i=1; i<=len; i++){
            printf("%c", *toP);
            toP++;
        }
    }
    else {
        printf("\nNon trovata sottostringa");
    }


    return 0;
}

char *cercaRegexp(char *src, char *regexp) {
    int len = reLen(regexp);
    int controllo = 0;
    int i=0, flag = 0;
    char *toR;
    while(*src != '\0' && controllo == 0) {
        toR = src;

        if (*regexp == '.') {

            controllo = controllaParola(src, regexp, len);
        }
        else if (isalpha(*regexp) != 0) {
            if (*regexp == *src) {
                controllo = controllaParola(src, regexp, len);
            }
        }
        else if (*regexp == '[') {
                flag = 0;
                i = 0;
                if (*(regexp+1) == '^') {
                while(*(regexp+i) != ']') {
                    if(*(regexp+i) != *src) {
                        i++;
                    }
                    else {
                        flag = 1;
                    }
                }
                if (flag == 0) {
                    controllo = controllaParola(src, regexp, len);
                }

            }
            else {
                while(*(regexp+i) != ']') {
                    if(*(regexp+i) != *src) {
                        i++;
                    }
                    else {
                        flag = 1;
                    }
                }
                if (flag == 1) {
                    controllo = controllaParola(src, regexp, len);
                }
            }
        }
        else {
            if (*(regexp) == 'a'){
                if (islower(*src) != 0){
                    controllo = controllaParola(src, regexp, len);
                }
            }
            else {
                if (isupper(*src) != 0){
                    controllo = controllaParola(src, regexp, len);
                }
            }
        }
        src = src+ 1;
        }


    if (controllo == 1){
        return toR;
    }
    else {
        return NULL;
    }
    return NULL;
}

int reLen(char *regexp) {
    int count = 0;

    while(*regexp != '\0') {

        if (*regexp == '.' || isalpha(*regexp) != 0) {
            count++;
            regexp += 1;

        }

        else if (*regexp == '[') {
            while(*regexp != ']') {
                regexp += 1;
            }
            count++;
            regexp += 1;

        }

        else {
            count++;
            regexp += 2;

        }

    }
    return count;
}

int controllaParola(char *src, char *regexp, int len) {
    int i, j;
    int flag = 0, flag2 = 1;


    for (i=0; i<len && flag2==1; i++){
        flag2 = 0;

        if (*regexp == '.') {
            flag2 = 1;
            src = src + 1;
            regexp = regexp+ 1;
        }
        else if (isalpha(*regexp) != 0) {
            if (*regexp == *src) {
                flag2 = 1;
                src = src + 1;
                regexp = regexp+ 1;
            }
        }
        else if (*regexp == '[') {
                j = 0;
                flag = 0;

                if (*(regexp+1) == '^') {
                while(*(regexp+j) != ']') {
                    if(*(regexp+j) != *src) {
                        j++;
                    }
                    else {
                        flag = 1;
                        j++;
                    }
                }
                if (flag == 0) {
                    flag2 = 1;
                    src = src + 1;
                    regexp = regexp + j+1;
                }

            }
            else {
                j = 0;
                flag = 1;
                while(*(regexp+j) != ']') {
                    if(*(regexp+j) == *src) {
                        flag = 0;
                    }
                    j++;
                }
                if (flag == 0) {
                    flag2 = 1;
                    src = src + 1;
                    regexp = regexp + j+1;
                }
            }
        }
        else {
            if (*(regexp+1) == 'a'){
                if (islower(*src) != 0){
                    flag2 = 1;
                    src = src + 1;
                    regexp = regexp + 2;
                }
            }
            else {
                if (isupper(*src) != 0){
                    flag2 = 1;
                    src = src + 1;
                    regexp = regexp + 2;
                }
            }
        }
    }


    if (flag2 == 0)
        return 0;

    else return 1;

}
