#ifndef RENDERING_H
#define RENDERING_H

#include "card.h"
#include "deck.h"

#include <raylib.h>

extern Texture2D heart;
extern Texture2D diamond;
extern Texture2D club;
extern Texture2D spade;

// Deklaration av RenderCardSuit
void LoadTextures();
void UnloadTextures();
void RenderCard(Card card, int posX, int posY);
void RenderCardSuit(Card card, int x, int y);
void DrawCardBackground(int posX, int posY, int cardWidth, int cardHeight);
bool DrawTexturedButton(Rectangle bounds, Texture2D texture);
bool Button(Rectangle bounds, const char *text, Color color);
Suit ChooseNewSuit(void);
void RenderPlayerHand(CardPile *hand);

#endif // RENDERING_H