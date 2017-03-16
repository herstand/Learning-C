#include <stdlib.h>
#include <stdio.h>
#include "cards.h"

int main(void) {
  struct Game* game = initializeGame();
  beginGame(game);

  free((*game).players[0].hand.cards);
  free((*game).players[1].hand.cards);
  free(game);
}
/**
printf("Player 1's cards are:\n");
for (int i = 0; i < (*game).players[0].hand.size; i++) {
  printf("%s\n", convertIntCardToString((*game).players[0].hand.cards[i]));
}
printf("Player 2's cards are:\n");
for (
  int i = 0;
  i < (*game).players[1].hand.size;
  i++)
{
  printf("%s\n", convertIntCardToString((*game).players[1].hand.cards[i]));
}
*/
