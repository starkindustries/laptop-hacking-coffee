#include <stdio.h>

int main(int argc, char **argv)
{
    char letter[1];
    char buffer[8]; 
    printf("Enter a letter: ");
    int result = scanf("%s", letter);
    printf("You entered: %s\n", letter);
}
