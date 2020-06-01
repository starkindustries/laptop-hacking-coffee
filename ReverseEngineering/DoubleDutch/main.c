
int main(void)

{
  int returnValue;
  long in_FS_OFFSET;
  int userInputIndex;
  uint randLetterIndex;
  int randLetters[12];
  char userInputString[5];
  long offsetPlusHex28;

  offsetPlusHex28 = *(long *)(in_FS_OFFSET + 0x28);  
  randLetters[0] = 0x61; // a
  randLetters[1] = 0x6a; // j
  randLetters[2] = 0x73; // s
  randLetters[3] = 0x68; // h
  randLetters[4] = 0x66; // f
  randLetters[5] = 0x6a; // j
  randLetters[6] = 0x61; // a
  randLetters[7] = 0x68; // h
  randLetters[8] = 0x6a; // j
  randLetters[9] = 0x66; // f
  printf("Insert a string of 5 characters: ");
  scanf("%5s", userInputString);
  userInputIndex = 0;
  randLetterIndex = 0;
  do
  {
    // if randLetterIndex > 9 then access granted!
    if (9 < (int)randLetterIndex)
    {
      puts("Access Granted");
      returnValue = 0;
    LAB_0010082a:
      if (offsetPlusHex28 != *(long *)(in_FS_OFFSET + 0x28))
      {
        /* WARNING: Subroutine does not return */
        __stack_chk_fail();
      }
      return returnValue;
    }
    // (randLetterIndex bitwise-AND 1) == 0 
    // only even numbers AND 1 result in 0 
    // (e.g. 0, 2, 4, 6, etc)
    if ((randLetterIndex & 1) == 0)
    {
      // if userInput[0] != randLetters[0]: deny. [c1=1, c2=2] [c1=2, c2=4]
      if ((int)userInputString[userInputIndex] != randLetters[(int)randLetterIndex])
      {
        puts("Access Denied!");
        returnValue = 1;
        goto LAB_0010082a;
      }
      // increment userInputIndex
      userInputIndex = userInputIndex + 1;
    }
    randLetterIndex = randLetterIndex + 1;
  } while (true);
}
