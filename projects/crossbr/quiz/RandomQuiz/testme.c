#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

//Valid Ascii characters are:
/*

[ = 91	' ' = 32	} = 125
( = 40	a = 97		) = 41
{ = 123	x = 120		] = 93

For testing, 0 = 48 will be added

*/

int characterValues[10] = {91, 40, 123, 32, 97, 120, 125, 41, 93, 48};

char inputChar()
{
	//Select a random char out of the array and return it
	//It has a 1/10 chance of beig correct
    return characterValues[rand()%10];
}

//randomly return reset or not
char *inputString()
{
	//As this is not dynamic (and most ways to return a char* are) this is one way to have a random variable test the fails or successes
	return ((rand()%2) == 1) ? "reset" : "failed";
}

void testme()
{
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;
  while (1)
  {
    tcCount++;
    c = inputChar();
    s = inputString();
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' '&& state == 3) state = 4;
    if (c == 'a' && state == 4) state = 5;
    if (c == 'x' && state == 5) state = 6;
    if (c == '}' && state == 6) state = 7;
    if (c == ')' && state == 7) state = 8;
    if (c == ']' && state == 8) state = 9;
    if (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
       && state == 9)
    {
      printf("error ");
      exit(200);
    }
  }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}
