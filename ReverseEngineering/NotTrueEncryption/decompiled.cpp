#include <stdio.h>

/********************************************************
 * 
 * This compile command:
 * $ g++ -ggdb -m32 decompiled.cpp
 * Gives this error:
 * /usr/bin/ld: skipping incompatible /usr/lib/gcc/x86_64-linux-gnu/7/libstdc++.so when searching for -lstdc++
 * /usr/bin/ld: skipping incompatible /usr/lib/gcc/x86_64-linux-gnu/7/libstdc++.a when searching for -lstdc++
 * /usr/bin/ld: cannot find -lstdc++
 * collect2: error: ld returned 1 exit status
 * 
 * To fix this error, install multilib.
 * $ sudo apt-get install gcc-multilib g++-multilib
 * https://askubuntu.com/questions/453681/gcc-wont-link-with-m32
 * 
 ********************************************************/

void func_00401126(void)
{
    return;
}

void checkPassword(void)
{
    unsigned char pwChar;
    FILE *_File;
    char *resultString;
    char *userInput;
    unsigned int winCondition;
    char *counter;
    char unaff_SI;
    bool bVar3;
    char abStack95[3];
    int local_60;
    int uStack92;
    int uStack88;
    int uStack84;
    int local_50;
    char userInputBuffer[64];
    unsigned int local_8;

    // https://www.geeksforgeeks.org/bitwise-operators-in-c-cpp/
    // The ^ (bitwise XOR) in C or C++ 
    // local_8 = DAT_00403004 ^ (uint)&stack0xfffffffc; 
    local_60 = 0x3c040f0b;
    uStack92 = 0x835773f;
    uStack88 = 0x7a3e7629;
    uStack84 = 0x3a030605;
    local_50 = 0x4d;
    
    // printf("Enter your password: ",unaff_SI);
    printf("Enter your password: ");

    // Enter your password: mypassword
    //    m     y     p     a     s     s     w     o     r     d    \n
    // 0x6d  0x79  0x70  0x61  0x73  0x73  0x77  0x6f  0x72  0x64  0x0a
    
    // https://stackoverflow.com/questions/30412951/unresolved-external-symbol-imp-fprintf-and-imp-iob-func-sdl2
    _File = (FILE *)stdin; // (FILE *)__acrt_iob_func(0);
    fgets((char *)userInputBuffer, 0x40, _File);
    userInput = userInputBuffer;
    counter = 0x0; // (byte *)0x0;
    
    do
    {
        pwChar = *userInput;
        // x bVar1  0x6d ('m')
        // x/s userInput   0xffffcfdc: "mypassword\n"
        userInput = userInput + 1;
        // x/s userInput   0xffffcfdd: "ypassword\n"
    } while (pwChar != 0);
    // At the end of this do-while, userInput is pointing to an empty string:
    // >>> x/s userInput
    // 0xffffcfe8:	""
    // >>> x/10bx userInput
    // 0xffffcfe8:	0x00	0x00	0x00	0x00	0x00	0xf4	0x70	0x0b

    // Examine userInputBuffer:
    // >>> x/s userInputBuffer
    // 0xffffcfdc:	"mypassword\n"
    // >>> x/s userInputBuffer+1
    // 0xffffcfdd:	"ypassword\n"
    if (userInput != userInputBuffer + 1)
    {
        do
        {
            userInputBuffer[(int)counter] = userInputBuffer[(int)counter] ^ 0x47;
            userInput = userInputBuffer;
            counter = counter + 1;
            do
            {
                pwChar = *userInput;
                userInput = userInput + 1;
            } while (pwChar != 0);
        } while (counter < userInput + -(int)(userInputBuffer + 1));
    }

    // 004010bd 8d 4d a4    LEA    userInput=>local_60,[EBP + -0x5c]
    // userInput = &stack0xffffffa0;
    counter = userInputBuffer;

    do
    {
        pwChar = *counter;
        bVar3 = pwChar < *userInput;

        // lose condition branch
        if (pwChar != *userInput)
        {
        LAB_004010e4:
            // set winCondition to 1 (i.e. lose)
            winCondition = -(unsigned int)bVar3 | 1;
            goto LAB_004010e9;
        }
        // win condition branch
        if (pwChar == 0)
        {            
            break;
        }
        pwChar = counter[1];
        bVar3 = pwChar < userInput[1];
        if (pwChar != userInput[1])
        {
            // go to lose condition
            goto LAB_004010e4;
        }
        counter = counter + 2;
        userInput = userInput + 2;
    } while (pwChar != 0);

    // if you make it here, then you win
    winCondition = 0;
LAB_004010e9:
    resultString = "\nWrong password n00b";
    
    if (winCondition == 0)
    {
        resultString = "\nFiles Decrypted!";
    }

    printf(resultString, local_60);
    _File = (FILE *)stdin; // (FILE *)__acrt_iob_func(0);
    fgets((char *)userInputBuffer, 0x40, _File);
    func_00401126();
    
    return;
}

int main(void)
{
    checkPassword();
    return 0;
}