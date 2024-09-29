#ifndef CIRCLE_H
#define CIRCLE_H

#include "SDL2/SDL.h"
#include "math.h"

int roundUpToMultipleOfEight( int v );
void DrawCircle( SDL_Renderer * renderer, SDL_Point center, int radius );

#endif