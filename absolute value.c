#include <stdio.h>
#include <stdlib.h>

int main()
{   float x;
    printf("Number whose number you want to know:");
    scanf("%f", &x);
    if ( x < 0 )
    {
        x = -x;
    }

    printf("%.1f", x);

    return 0;
}
