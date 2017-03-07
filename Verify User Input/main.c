/* Ensures user input is a valid positive integer. */
#include <stdio.h>
#include <string.h>
#include "util.h"

int main(void) {
  int i;
  int error = 0;
  int* error_ptr = &error;
  char userInput[10];
  int enteredNumber;

  printf("Enter a positive integer: ");

  loadCharArrayFromUser(userInput, error_ptr);
  if (*error_ptr == 1) {
    return 1;
  }

  enteredNumber = strtol_strict(userInput, error_ptr);
  if (*error_ptr == 1) {
    return 1;
  }

  printf("You entered the positive integer %d\n", enteredNumber);
  return 0;
}
