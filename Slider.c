#include "Slider.h"

void SliderWindowSetup(struct SliderWindow* sliderWindow, const char* name, int numSliders, int width, int textSize)
{
    int ret;

	SDL_DisplayMode DM;
	const int ScreenWidth = DM.w;
	const int ScreenHeight = DM.h;
    const int height = numSliders * DEFAULT_SLIDER_HEIGHT;

	SDL_Window* win = SDL_CreateWindow( name, (ScreenWidth / 2) - (width / 2), (ScreenHeight / 2) - (height / 2), width, height, SDL_WINDOW_SHOWN );

	SDL_Renderer* renderer = SDL_CreateRenderer( win, -1, SDL_RENDERER_ACCELERATED );

    TTF_Init();

    TTF_Font* font;

    font = TTF_OpenFont("LiberationMono-Regular.ttf", textSize);
    if ( !font ) {
        printf("Failed to load font: %s\n", TTF_GetError());
    }

    struct Slider* sliders = malloc(numSliders * sizeof(struct Slider));

	*sliderWindow = (struct SliderWindow){numSliders, sliders, win, width, height, font};
}

void SliderWindowClose(struct SliderWindow* sliderWindow)
{
	SDL_DestroyRenderer(SDL_GetRenderer(sliderWindow->window));
	SDL_DestroyWindow(sliderWindow->window);
    free(sliderWindow->sliders);
    TTF_CloseFont(sliderWindow->font);
}

void SliderWindowHandleEvent(struct SliderWindow* sliderWindow, SDL_Event* event)
{
    if(event->type == SDL_MOUSEBUTTONDOWN)
    {
        for(int i = 0; i < sliderWindow->numSliders; i++)
        {
            if(sqrt(pow(
                event->button.x - 
                map(*(sliderWindow->sliders[i].variable),sliderWindow->sliders[i].start, sliderWindow->sliders[i].end, 0 + X_OFFSET, sliderWindow->width - X_OFFSET)
                , 2) 
                +
                pow(event->button.y - ((DEFAULT_SLIDER_HEIGHT* i) + 30), 2)
                )
                < BALL_RADIUS

            )
            {
                if(event->type == SDL_MOUSEBUTTONDOWN)
                {
                    sliderWindow->sliders[i].selected = true;
                }
                else if(event->type == SDL_MOUSEBUTTONUP)
                {
                    sliderWindow->sliders[i].selected = false;
                }
            }
        }
    }
    else if(event->type == SDL_MOUSEBUTTONUP)
    {
        for(int i = 0; i < sliderWindow->numSliders; i++)
        {
            sliderWindow->sliders[i].selected = false;
        }
    }
    else if(event->type == SDL_MOUSEMOTION)
    {
        for(int i = 0; i < sliderWindow->numSliders; i++)
        {
            if(sliderWindow->sliders[i].selected)
            {
                int pos = min(max(X_OFFSET, event->motion.x), sliderWindow->width - X_OFFSET);
                struct Slider* currentSlider = &(sliderWindow->sliders[i]);
                *(currentSlider->variable) = map(pos, X_OFFSET, sliderWindow->width - X_OFFSET, currentSlider->start, currentSlider->end);
            }
        }
    }
}

void SliderSetup(struct SliderWindow *sliderWindow, int id, float minValue, float maxValue,const char* name, float *variable)
{
    sliderWindow->sliders[id] = (struct Slider){name ,minValue, maxValue, variable};
}

void SliderWindowDraw(struct SliderWindow* sliderWindow)
{
    SDL_Renderer* renderer = SDL_GetRenderer(sliderWindow->window);

    SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
    SDL_RenderClear( renderer );

    int heightBuffer = 0;
    for(int i = 0; i < sliderWindow->numSliders; i++)
    {
        struct Slider* currentSlider = &(sliderWindow->sliders[i]);

        //Text
        SDL_Surface* text;
        SDL_Color color = { 0x00, 0x00, 0x00 };

        char* name = malloc(MAX_NAME_LENGTH);
        snprintf(name, MAX_NAME_LENGTH, "%s: %f", currentSlider->name, *(currentSlider->variable));

        text = TTF_RenderText_Solid( sliderWindow->font, name, color );
        if ( !text ) {
            printf("Failed to render text: %s\n", TTF_GetError());
        }
        free(name);


        SDL_Texture* text_texture;
        text_texture = SDL_CreateTextureFromSurface( renderer, text );
        SDL_Rect dest = { 0, heightBuffer, text->w, text->h };
        SDL_RenderCopy( renderer, text_texture, NULL, &dest );
        SDL_DestroyTexture(text_texture);
        SDL_FreeSurface(text);

        //Line
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xff);
        SDL_RenderDrawLine(renderer, X_OFFSET, heightBuffer + 30, sliderWindow->width - X_OFFSET, heightBuffer + 30);

        //Circle
        SDL_Point point = (SDL_Point){
            map(*(currentSlider->variable), currentSlider->start, currentSlider->end, 0 + X_OFFSET, sliderWindow->width - X_OFFSET),
            heightBuffer + 30
            };
        DrawCircle(renderer, point, BALL_RADIUS);

        heightBuffer += DEFAULT_SLIDER_HEIGHT;
    }

    SDL_RenderPresent( renderer);
	SDL_UpdateWindowSurface(sliderWindow->window);
}