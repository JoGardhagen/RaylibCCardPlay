#ifndef CARD_H
#define CARD_H

typedef enum {
    HEARTS,
    DIAMONDS,
    CLUBS,
    SPADES,
    NUM_SUITS
} Suit;

typedef enum {
    TWO,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE,
    TEN,
    JACK,
    QUEEN,
    KING,
    ACE,
    NUM_RANKS
} Rank;

typedef struct {
    Rank rank;
    Suit suit;
} Card;

const char* rankToString(Rank rank);
const char* suitToString(Suit suit);

void printCard(Card card); 
void printCardIllustrationASCII(Card card);


#endif