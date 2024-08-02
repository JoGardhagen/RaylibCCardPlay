#ifndef CARD_H
#define CARD_H

typedef enum {
    TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, ACE
} Rank;

typedef enum {
    HEARTS, DIAMONDS, CLUBS, SPADES
} Suit;

typedef struct {
    Rank rank;
    Suit suit;
} Card;

const char* rankToString(Rank rank);
const char* suitToString(Suit suit);

void printCard(Card card); 
//void printCardIllustrationASCII(Card card);


#endif