#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/**
 Ensure string being converted to a number
 is actually a decimal numerical string
 before converting it.
**/
int strtol_strict(char stringRepOfNumber[], int* error) {
  int i;
  for (i = 0; i < strlen(stringRepOfNumber); i++) {
    if (stringRepOfNumber[i] < '0' || stringRepOfNumber[i] > '9') {
      printf("Input `%s` is not a positive integer.\n", stringRepOfNumber);
      *error = 1;
      return 1;
    }
  }
  /* If we got here, we have a valid num-string */
  return strtol(stringRepOfNumber, NULL, 10);
}

void loadCharArrayFromUser(char userInput[], int* error) {
  int c;
  int userNumDigitLength = 0;

  while ( (c = getchar()) != '\n' && c != EOF) {
    if (userNumDigitLength > 9) {
      printf("This app cannot support that many digits.\n");
      *error = 1;
      return;
    }
    userInput[userNumDigitLength++] = c;
  }
  userInput[userNumDigitLength] = '\0';
}
