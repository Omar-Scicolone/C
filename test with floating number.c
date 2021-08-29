#include <stdio.h>
#include <stdlib.h>

int main()
{   int int_1, int_2;
    float float_1, float_2;

    printf("Enter four number, two integers and two real:\n");
    scanf("%d%d%f%f", &int_1, &int_2, &float_1, &float_2);
    
    printf("-%5d -%5d\n", int_1,int_2);
    printf("-%5.2f\n", float_1);
    printf("-%.3f\n", float_2);
    return 0;
}
