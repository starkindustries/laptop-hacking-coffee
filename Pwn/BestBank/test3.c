#include <stdio.h>

// First remote root exploit - bin 0x1D
// https://youtu.be/HAN8Qun26cQ
void main()
{
    char input[16];
    char *hello = "helloworld";
    printf("Enter a string: ");
    scanf("%s", input);
    puts(hello);
}
