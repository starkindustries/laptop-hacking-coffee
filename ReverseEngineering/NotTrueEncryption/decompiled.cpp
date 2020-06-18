#include <stdio.h>

/********************************************************
 * 
 * This compile command:
 * $ g++ -m32 decompiled.cpp
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
    unsigned char bVar1;
    FILE *_File;
    char *resultString;
    char *userInput;
    unsigned int uVar2;
    char *byte0;
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

    // https://stackoverflow.com/questions/202463/what-does-the-caret-mean-in-c-cli
    // local_8 = DAT_00403004 ^ (uint)&stack0xfffffffc; // ^ is a pointer
    local_60 = 0x3c040f0b;
    uStack92 = 0x835773f;
    uStack88 = 0x7a3e7629;
    uStack84 = 0x3a030605;
    local_50 = 0x4d;
    // printf("Enter your password: ",unaff_SI);
    printf("Enter your password: ");
    // https://stackoverflow.com/questions/30412951/unresolved-external-symbol-imp-fprintf-and-imp-iob-func-sdl2
    _File = (FILE *)stdin; // (FILE *)__acrt_iob_func(0);
    fgets((char *)userInputBuffer, 0x40, _File);
    userInput = userInputBuffer;
    byte0 = 0x0; // (byte *)0x0;
    do
    {
        bVar1 = *userInput;
        userInput = userInput + 1;
    } while (bVar1 != 0);
    if (userInput != userInputBuffer + 1)
    {
        do
        {
            userInputBuffer[(int)byte0] = userInputBuffer[(int)byte0] ^ 0x47;
            userInput = userInputBuffer;
            byte0 = byte0 + 1;
            do
            {
                bVar1 = *userInput;
                userInput = userInput + 1;
            } while (bVar1 != 0);
        } while (byte0 < userInput + -(int)(userInputBuffer + 1));
    }
    // userInput = &stack0xffffffa0;
    byte0 = userInputBuffer;
    do
    {
        bVar1 = *byte0;
        bVar3 = bVar1 < *userInput;
        if (bVar1 != *userInput)
        {
        LAB_004010e4:
            uVar2 = -(unsigned int)bVar3 | 1;
            goto LAB_004010e9;
        }
        if (bVar1 == 0)
            break;
        bVar1 = byte0[1];
        bVar3 = bVar1 < userInput[1];
        if (bVar1 != userInput[1])
            goto LAB_004010e4;
        byte0 = byte0 + 2;
        userInput = userInput + 2;
    } while (bVar1 != 0);
    uVar2 = 0;
LAB_004010e9:
    resultString = "\nWrong password n00b";
    if (uVar2 == 0)
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