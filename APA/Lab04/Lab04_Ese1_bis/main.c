#include <stdio.h>
#include <stdlib.h>

int gcd(int a, int b);

int main()
{
    printf("M C D = %d", gcd(10, 5));
    return 0;
}

int gcd(int a, int b){
    int tmp;
    if (b>a){
        tmp = a;
        a = b;
        b = tmp;
    }

    if(b == 0)
        return a;

    if (a%2 == 0 && b%2 == 0)
        return 2*gcd(a/2, b/2);
    else if(a%2 != 0 && b%2 == 0)
        return gcd(a, b/2);
    else if(a%2 != 0 && b%2 != 0)
        return gcd((a-b)/2, b);
    else if(a%2 == 0 && b%2 != 0)
        return gcd(a/2, b);

}
