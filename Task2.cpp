#include <stdio.h>

void removeDups(char *str)
{
    char *current = str + 1;
    while (*current != '\0')
    {
        if (*(current-1) != *current)
            *(++str) = *current;
        current++;
    }
    *(++str) = '\0';
}

int main(int args, char* argv[])
{

    char data[] = "AAA BBB AAA";
    printf("%s\n", data);
    removeDups(data);
    printf("%s\n\n", data);

    char data1[] = "AAABBB";
    printf("%s\n", data1);
    removeDups(data1);
    printf("%s\n\n", data1);

    char data2[] = "AAA";
    printf("%s\n", data2);
    removeDups(data2);
    printf("%s\n\n", data2);

    char data3[] = "A";
    printf("%s\n", data3);
    removeDups(data3);
    printf("%s\n\n", data3);

    printf("Empty string:\n");
    char data4[] = "";
    printf("%s\n", data4);
    removeDups(data4);
    printf("%s\n\n", data4);

    char data5[] = "AAABBBBBBA";
    printf("%s\n", data5);
    removeDups(data5);
    printf("%s\n\n", data5);

    char data6[] = "BBABBABB";
    printf("%s\n", data6);
    removeDups(data6);
    printf("%s\n\n", data6);

    char data7[] = "BBBABABABAAA";
    printf("%s\n", data7);
    removeDups(data7);
    printf("%s\n\n", data7);

    char data8[] = "ABABABABABAB";
    printf("%s\n", data8);
    removeDups(data8);
    printf("%s\n\n", data8);

    char data9[] = "BBBABBBAAAABBBAAABBBAP";
    printf("%s\n", data9);
    removeDups(data9);
    printf("%s\n\n", data9);

    char data10[] = "AAAB";
    printf("%s\n", data10);
    removeDups(data10);
    printf("%s\n\n", data10);

    return 0;
}
