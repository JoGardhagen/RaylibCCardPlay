#ifndef RENDERING_H
#define RENDERING_H

#include "card.h"
#include <raylib.h>

// Deklaration av RenderCardSuit
void LoadTextures();
void UnloadTextures();
void RenderCard(Card card, int posX, int posY);
void RenderCardSuit(Card card, int x, int y);
void DrawCardBackground(int posX, int posY, int cardWidth, int cardHeight);
bool DrawTexturedButton(Rectangle bounds, Texture2D texture);
bool Button(Rectangle bounds, const char *text, Color color);

#endif // RENDERING_H