#include    <stdio.h>

int main(void)
{
    int	    v1 = -1; 
    char    line[128];
    int     v2 = 0x12345678;
    int *   p1 = &v1;

    gets(line);
    printf(line);

    printf("\np1=%p\nv1=%d\n", p1, v1);
    return 0;
}
