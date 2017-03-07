#include <stdio.h>
#include <stdlib.h>

int main(void) {
  int my_age = 28;
  int c;
  int i = 0;
  char your_age_str[3];
  int your_age = 0;

  printf("I am %d years old until Thursday March 9th, 2017.\n", my_age);
  printf("How old are you? (Please just enter the closest year value.) ");

  while ( (c = getchar()) != '\n' && c != EOF) {
    your_age_str[i++] += c;
  }
  your_age = strtol(your_age_str, NULL, 10);

  if (your_age > my_age) {
   printf("You are %d years older than me!\n", your_age - my_age);
  } else if (your_age < my_age) {
   printf("I am %d years older than you!\n", my_age - your_age);
  } else {
   printf("Hello, twin!\n");
  }
  return 0;
}
