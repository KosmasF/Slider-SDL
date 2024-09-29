#ifndef SLIDER_H
#define SLIDER_H

#include "SDL2/SDL.h"
#include <SDL2/SDL_ttf.h>
#include "Exceptions.h"
#include "Map.h"
#include "Circle.h"
#include <math.h>
#include <stdbool.h>


#define DEFAULT_SLIDER_HEIGHT 50
#define X_OFFSET 5
#define BALL_RADIUS 7
#define MAX_NAME_LENGTH 128

static inline int min(const int a, const int b) {
    return a < b ? a : b;
}
static inline int max(const int a, const int b) {
    return a > b ? a : b;
}

struct SliderWindow
{
    int numSliders;
    struct Slider* sliders;
    struct SDL_Window* window;
    int width;
    int height;
    TTF_Font* font;
};

struct Slider
{
    const char* name;
    float start;
    float end;
    float* variable;
    bool selected;
};


void SliderWindowSetup(struct SliderWindow* sliderWindow, const char* name, int numSliders, int width, int textSize);
void SliderWindowHandleEvent(struct SliderWindow* sliderWindow, SDL_Event* event);
void SliderWindowClose(struct SliderWindow* sliderWindow);
void SliderWindowDraw(struct SliderWindow* sliderWindow);

void SliderSetup(struct SliderWindow* sliderWindow, int id, float minValue, float maxValue, const char* name, float* variable);



#endif