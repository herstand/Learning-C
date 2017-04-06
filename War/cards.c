#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include "cards.h"

char* convertIntCardToString(int card) {
  char* output = calloc(18, sizeof(char));
  strcat(output,FACES[card % 13]);
  strcat(output," of ");
  strcat(output,SUITS[(int)(card / 13.0)]);
  return output;
}

void printPlayerCards(struct Player player) {
  printf("%s Cards: ", player.name);
  for (int i = 0; i < player.hand.size; i++) {
    printf("%d, ",player.hand.cards[i]);
  }
  printf("\n");
}

/**
  card1 is smaller if returns negative,
  bigger if returns positive
  equal if 0,
*/
int compareHands(int card1, int card2) {
  return card1 % 13 - card2 % 13;
}
void playHand(struct Game* game) {
  int enter = 0;
  if (
    (*game).players[0].hand.size > 0 &&
    (*game).players[1].hand.size > 0
  ) {
    int humanCard = (*game).players[0].hand.cards[0];
    char * humanCardToString = convertIntCardToString(humanCard);
    int machineCard = (*game).players[1].hand.cards[0];
    char * machineCardToString = convertIntCardToString(machineCard);
    int winner = compareHands(humanCard,machineCard);

    printf("You flipped the %s(%d).\n", humanCardToString, humanCard);
    free(humanCardToString);
    printf("Machine flipped the %s(%d).\n", machineCardToString, machineCard);
    free(machineCardToString);

    if (winner > 0) {
      printf("**You won the hand!**\n");
      addCardToHand(
        &(*game).players[0],
        removeTopCardFromHand(&(*game).players[0])
      );
      addCardToHand(
        &(*game).players[0],
        removeTopCardFromHand(&(*game).players[1])
      );
      printf("\nScore: You(%d), Machine(%d)\nPress enter to continue.\n",(*game).players[0].hand.size,(*game).players[1].hand.size);
      while (enter != '\r' && enter != '\n') { enter = getchar(); }
      playHand(game);
    } else if (winner < 0) {
      printf("**You lost the hand!**\n");
      addCardToHand(
        &(*game).players[1],
        removeTopCardFromHand(&(*game).players[1])
      );
      addCardToHand(
        &(*game).players[1],
        removeTopCardFromHand(&(*game).players[0])
      );
      printf("\nScore: You(%d), Machine(%d)\nPress enter to continue.\n",(*game).players[0].hand.size,(*game).players[1].hand.size);
      while (enter != '\r' && enter != '\n') { enter = getchar(); }
      playHand(game);
    } else {
      printf("**You tied! It's war time! Press enter to continue.\n");
      while (enter != '\r' && enter != '\n') { enter = getchar(); }
      playWarHand(game);
    }
  } else if ((*game).players[0].hand.size > 0) {
    printf("You won!\n\n");
  } else {
    printf("Machine won!\n\n");
  }
}

void playWarHand(struct Game* game) {
  // TODO
}

void initializeDeck(struct Deck *deck) {
  int cardIndex;
  int deckLength = sizeof((*deck).cards)/sizeof(int);
  srand(time(NULL));
  for (cardIndex = 0; cardIndex < deckLength; cardIndex++) {
    (*deck).cards[cardIndex-1] = cardIndex;
  }
  // shuffle
  for (cardIndex = 51; cardIndex > 0; cardIndex--) {
    int destinationOfSwap = rand() % cardIndex;
    int originOfSwap = (*deck).cards[cardIndex];
    (*deck).cards[cardIndex] = (*deck).cards[destinationOfSwap];
    (*deck).cards[destinationOfSwap] = originOfSwap;
  }
}

void addCardToHand(struct Player *player, int card) {
  (*player).hand.cards =  realloc(
                           (*player).hand.cards,
                           ((*player).hand.size + 1) * sizeof(int)
                          );
  (*player).hand.size += 1;
  (*player).hand.cards[(*player).hand.size - 1] = card;
}

int removeTopCardFromHand(struct Player *player) {
  int topCard = (*player).hand.cards[0];
  int lastCard = (*player).hand.cards[(*player).hand.size-1];
  int * tmp =  realloc(
                  (*player).hand.cards,
                  ((*player).hand.size - 1) * sizeof(int)
                );
  if (tmp != NULL) {
    (*player).hand.cards = tmp;
  } else {
    printf("ERROR");
  }
  (*player).hand.size -= 1;
  for (int card_index = 0; card_index < (*player).hand.size - 1; card_index++){
    (*player).hand.cards[card_index] = (*player).hand.cards[card_index + 1];
  }
  (*player).hand.cards[(*player).hand.size - 1] = lastCard;
  return topCard;
}

void dealCards(struct Game *game) {
  int deckLength = sizeof((*game).deck.cards) / sizeof(int);
  // Because deck is shuffled, we deal 1 / numOfPlayer cards to each player at a time
  for (
    int player_index = 0;
    player_index < (*game).numberOfPlayers;
    player_index++
  ) {
    // Deal first card to player
    (*game).players[player_index].hand.size = 1;
    (*game).players[player_index].hand.cards = malloc(
                                      (*game).players[player_index].hand.size
                                      *
                                      sizeof(int)
                                    );
    (*game).players[player_index].hand.cards[0] = (*game).deck.cards[(deckLength * player_index) / 2];

    // Deal rest of cards to player
    for (
      int cardInDeck = (deckLength * player_index) / 2 + 1;
      cardInDeck < deckLength / ((*game).numberOfPlayers - player_index);
      cardInDeck++
    ) {
      addCardToHand(
        &(*game).players[player_index],
        (*game).deck.cards[cardInDeck]
      );
    }
  }
}
void beginGame(struct Game* game) {
  char enter = 0;
  printf("The game is War! You are competing against the computer. Press enter to begin.\n");
  while (enter != '\r' && enter != '\n') { enter = getchar(); }
  playHand(game);
}
struct Game* initializeGame() {
  struct Game* game = malloc(sizeof(struct Game));
  (*game).numberOfPlayers = 2;
  strcpy((*game).players[0].name, "User");
  strcpy((*game).players[1].name, "Computer");
  initializeDeck(&((*game).deck));
  dealCards(game);
  return game;
}
