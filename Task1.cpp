#include <stdio.h>
#include <stdlib.h>

void printBin(const int number)
{
    for (unsigned int i = 1 << 31; i > 0; i = i >> 1)
    {
        if (number & i)
            printf("1");
        else
            printf("0");
    }
    printf("\n");
}

int main(int args, char* argv[])
{
    if (args < 2)
    {
        perror("Provide number!");
        return 0;
    }
    printBin(atoi(argv[1]));
    return 0;
}
