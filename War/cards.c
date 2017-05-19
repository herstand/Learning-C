#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include "cards.h"

char* convertIntCardToString(int card) {
  char* output = calloc(18, sizeof(char));
  strcat(output,FACES[card % 13]);
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
//TODO: Assumes human and computer only right now
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

    printf("You flipped the [%s].\n", humanCardToString);
    printf("Machine flipped the [%s].\n", machineCardToString);
    free(machineCardToString);

    if (winner > 0) {
      printf("**You won the hand!**\n");
      sendTopCardToBottom(&(*game).players[0]);
      captureTopCardFrom(&(*game).players[0], &(*game).players[1]);
      printf("\nScore: You(%d), Machine(%d)\nPress enter to continue.\n",(*game).players[0].hand.size,(*game).players[1].hand.size);
      while (enter != '\r' && enter != '\n') { enter = getchar(); }
      playHand(game);
    } else if (winner < 0) {
      printf("**You lost the hand!**\n");
      sendTopCardToBottom(&(*game).players[1]);
      captureTopCardFrom(&(*game).players[1], &(*game).players[0]);
      printf("\nScore: You(%d), Machine(%d)\nPress enter to continue.\n",(*game).players[0].hand.size,(*game).players[1].hand.size);
      while (enter != '\r' && enter != '\n') { enter = getchar(); }
      playHand(game);
    } else {
      printf("**You both flipped %s! It's war time! Press enter to continue.\n", humanCardToString);
      while (enter != '\r' && enter != '\n') { enter = getchar(); }
      playWarHand(game);
    }
    free(humanCardToString);
  } else if ((*game).players[0].hand.size > 0) {
    printf("You won the game!\n\n");
  } else {
    printf("Machine won the game!\n\n");
  }
}

void playWarHand(struct Game* game) {
  int enter = 0;
  int flippedHumanCard = removeTopCardFromHand(&(*game).players[0]);
  int flippedMachineCard = removeTopCardFromHand(&(*game).players[1]);
  int downHumanCard = removeTopCardFromHand(&(*game).players[0]);
  int downMachineCard = removeTopCardFromHand(&(*game).players[1]);
  int humanWarriorCard = removeTopCardFromHand(&(*game).players[0]);
  char * humanWarriorCardToString = convertIntCardToString(humanWarriorCard);
  int machineWarriorCard = removeTopCardFromHand(&(*game).players[1]);
  char * machineWarriorCardToString = convertIntCardToString(machineWarriorCard);
  int winner = compareHands(humanWarriorCard,machineWarriorCard);

  printf("Your warrior card is the [%s].\n", humanWarriorCardToString);
  printf("The machine's warrior card is the [%s].\n", machineWarriorCardToString);
  free(humanWarriorCardToString);
  free(machineWarriorCardToString);

  if (winner > 0) {
    printf("**You won the hand!**\n");
    addCardToHand(&(*game).players[0], flippedHumanCard);
    addCardToHand(&(*game).players[0], flippedMachineCard);
    addCardToHand(&(*game).players[0], downHumanCard);
    addCardToHand(&(*game).players[0], downMachineCard);
    addCardToHand(&(*game).players[0], humanWarriorCard);
    addCardToHand(&(*game).players[0], machineWarriorCard);
    printf("\nScore: You(%d), Machine(%d)\nPress enter to continue.\n",(*game).players[0].hand.size,(*game).players[1].hand.size);
    while (enter != '\r' && enter != '\n') { enter = getchar(); }
    playHand(game);
  } else if (winner < 0) {
    printf("**You lost the hand!**\n");
    addCardToHand(&(*game).players[1], flippedHumanCard);
    addCardToHand(&(*game).players[1], flippedMachineCard);
    addCardToHand(&(*game).players[1], downHumanCard);
    addCardToHand(&(*game).players[1], downMachineCard);
    addCardToHand(&(*game).players[1], humanWarriorCard);
    addCardToHand(&(*game).players[1], machineWarriorCard);
    printf("\nScore: You(%d), Machine(%d)\nPress enter to continue.\n",(*game).players[0].hand.size,(*game).players[1].hand.size);
    while (enter != '\r' && enter != '\n') { enter = getchar(); }
    playHand(game);
  } else {
    printf("**You both flipped %s! The war goes on! Press enter to continue.\n", humanWarriorCardToString);
    while (enter != '\r' && enter != '\n') { enter = getchar(); }
    //TODO: recursive WAR playWarHand(game);
  }
}

void initializeDeck(struct Deck *deck) {
  int cardIndex;
  int numCardsInDeck = sizeof((*deck).cards)/sizeof((*deck).cards[0]);
  int deckLength = sizeof((*deck).cards)/sizeof(int);
  srand(time(NULL));
  for (cardIndex = 0; cardIndex < deckLength; cardIndex++) {
    (*deck).cards[cardIndex-1] = cardIndex;
  }
  // shuffle
  for (cardIndex = numCardsInDeck - 1; cardIndex > 0; cardIndex--) {
    int destinationOfSwap = rand() % cardIndex;
    int originOfSwap = (*deck).cards[cardIndex];
    (*deck).cards[cardIndex] = (*deck).cards[destinationOfSwap];
    (*deck).cards[destinationOfSwap] = originOfSwap;
  }
}

void captureTopCardFrom(struct Player *winner, struct Player *loser) {
  addCardToHand(
    winner,
    removeTopCardFromHand(loser)
  );
}
void sendTopCardToBottom(struct Player *player) {
  addCardToHand(
    player,
    removeTopCardFromHand(player)
  );
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
    printf("ERROR"); // realloc can sometimes cause an error
  }
  (*player).hand.size -= 1;
  for (int card_index = 0; card_index < (*player).hand.size - 1; card_index++){
    (*player).hand.cards[card_index] = (*player).hand.cards[card_index + 1];
  }
  (*player).hand.cards[(*player).hand.size - 1] = lastCard;
  return topCard;
}

void initializeHand(struct Hand* hand, int card) {
  (*hand).size = 1;
  (*hand).cards = malloc(1 * sizeof(int));
  (*hand).cards[0] = card;
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
    initializeHand(
      &((*game).players[player_index].hand),
      (*game).deck.cards[(deckLength * player_index) / 2]
    );

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
