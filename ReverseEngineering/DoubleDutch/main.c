
int main(void)

{
  int returnValue;
  long in_FS_OFFSET;
  int counter1;
  uint counter2;
  int randLetters[12];
  char userInputString[5];
  long offsetPlusHex28;

  offsetPlusHex28 = *(long *)(in_FS_OFFSET + 0x28);
  /* "a" */
  randLetters[0] = 0x61;
  /* "j" */
  randLetters[1] = 0x6a;
  /* "s" */
  randLetters[2] = 0x73;
  /* "h" */
  randLetters[3] = 0x68;
  /* "f" */
  randLetters[4] = 0x66;
  /* "j" */
  randLetters[5] = 0x6a;
  /* "a" */
  randLetters[6] = 0x61;
  /* "h" */
  randLetters[7] = 0x68;
  /* "j" */
  randLetters[8] = 0x6a;
  /* "f" */
  randLetters[9] = 0x66;
  printf("Insert a string of 5 characters: ");
  scanf("%5s", userInputString);
  counter1 = 0;
  counter2 = 0;
  do
  {
    /* if counter2 > 9: access granted! */
    if (9 < (int)counter2)
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
    /* (counter2 bitwise AND 1) == 0 // only even numbers AND 1 result in 0 (e.g. 0, 2, 4, 6, etc) */
    if ((counter2 & 1) == 0)
    {
      /* if userInput[0] != ajsh[0]: deny. [c1=1, c2=2] [c1=2, c2=4] */
      if ((int)userInputString[counter1] != randLetters[(int)counter2])
      {
        puts("Access Denied!");
        returnValue = 1;
        goto LAB_0010082a;
      }
      /* increment counter1 */
      counter1 = counter1 + 1;
    }
    counter2 = counter2 + 1;
  } while (true);
}
