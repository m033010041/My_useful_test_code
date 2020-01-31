#include <stdio.h>
#include <stdlib.h>

int add(int a, int b, int c)
{
        return a+b+c;
}


int main(int argc, char *argv[])
{
        int a=5;
        int b=3;
        int c=6;
        int result = 0;

        result = add(a, b, c);
        printf("result is %d\n", result);

        return 0;
}
