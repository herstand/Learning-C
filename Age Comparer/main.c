#include <stdio.h>
#include <stdlib.h>
#include "../User Input Utilities/util.h"

int main(void) {
  int my_age = 28;
  int c;
  int i = 0;
  char your_age_str[3];
  int your_age = 0;
  int error = 0;
  int* error_ptr = &error;

  printf(
    "I am %d years old until Thursday March 9th, 2017.\n\
How old are you? (Please just enter the closest year value.) ",
    my_age
  );

  loadIntRepresentedAsCharArrayFromUser(your_age_str, error_ptr);
  if (*error_ptr == 1) {
    return 1;
  }

  your_age = strtol_strict(your_age_str, error_ptr);
  if (*error_ptr == 1) {
    return 1;
  }

  if (your_age > my_age) {
   printf("You are %d years older than me!\n", your_age - my_age);
  } else if (your_age < my_age) {
   printf("I am %d years older than you!\n", my_age - your_age);
  } else {
   printf("Hello, twin!\n");
  }
  return 0;
}
