#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int majority(int *a, int N);
int majorityR(int *a, int l, int r, int N);

int main()
{
    int v1[7] = {3, 3, 9, 4, 3, 5, 3};
    int v2[8] = {0, 1, 0, 2, 0, 4, 0, 5};


    printf("Elemento maggioritario di v1 = %d\n", majority(v1, 7));
    printf("Elemento maggioritario di v2 = %d", majority(v2, 8));


    return 0;
}

int majority(int *a, int N){
    int l = 0, r = N-1;
    return majorityR(a, l, r, N);
}

int majorityR (int *a, int l, int r, int N){
    int i;
    int cu=0, cv=0, u, v, q;

    if ((r-l) == 0){
        return a[l];
    }

    q = (r+l)/2;

    u = majorityR(a, l, q, N);
    v = majorityR(a, q+1, r, N);

    if (u == v){
        return u;
    }

    else {
        for (i=0; i<N; i++){
            if (u==a[i])
                cu++;
            else if (v==a[i])
                cv++;
        }

        if (cv>N/2)
            return v;
        else if (cu > N/2)
            return u;
        else return -1;
    }

    return -1;
}
