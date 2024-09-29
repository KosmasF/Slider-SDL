#include "Circle.h"

// rounding helper, simplified version of the function I use
int roundUpToMultipleOfEight( int v )
{
    return (v + (8 - 1)) & -8;
}

void DrawCircle( SDL_Renderer * renderer, SDL_Point center, int radius )
{
    SDL_Point* points = malloc(radius * radius * 2 * 2 * sizeof(SDL_Point));
    int buffer = 0;
    for(int x = -radius; x < radius; x++)
    {
        for(int y = -radius; y < radius; y++)
        {
            if(sqrt((x * x) + (y * y)) < radius)
            {
                points[buffer] = (SDL_Point){center.x - x, center.y - y};
                buffer++;
            }
        }
    }

    SDL_RenderDrawPoints( renderer, points, buffer );
    free(points);
}