#include <stdio.h>
#include <stdlib.h>

int main()
{
    float a,b,c, delta, x;
    printf("Enter a, b, c of ax^2+bx+c=0:\n");
    scanf("%f%f%f", &a, &b, &c);
    delta = (b*b)-(4*a*c);
    if (a==0)
    {
        x = (-c/b);
        printf("Per a = 0, la x vale %.1f", x);
    }
    else
    {
    if (delta > 0)
    printf("The equation has two distinct real solutions");
    if (delta == 0)
    printf("The equation has two coincident real solutions");
    if (delta < 0)
    printf("The equation has no real solutions");
    }
    return 0;
}
