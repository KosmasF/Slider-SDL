#include <stdio.h>
#include <stdlib.h>
#include "SDL2/SDL.h"
#include "Slider.h"
#include <stdbool.h>

struct SliderWindow* sliderWindow;
SDL_Window* win;
SDL_Renderer* renderer;

bool Loop() {
	SDL_Event e;

	while( SDL_PollEvent( &e ) != 0 ) {
        if(e.type == SDL_QUIT)
        {
            return false;
        }
        else if( e.type == SDL_WINDOWEVENT)
        {
            if(e.window.windowID == SDL_GetWindowID(win))
            {
                if(e.window.event == SDL_WINDOWEVENT_CLOSE)
                    return false;
            }
            else if(sliderWindow != NULL)
            {
                if(e.window.windowID == SDL_GetWindowID(sliderWindow->window))
                {
                    if(e.window.event == SDL_WINDOWEVENT_CLOSE)
                    {
                        SliderWindowClose(sliderWindow);
                        sliderWindow = NULL;
                    }
                }
            }

		}
        else if(e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP)
        {
            if(e.button.windowID == SDL_GetWindowID(win))
            {
                ;
            }
            else if(e.button.windowID == SDL_GetWindowID(sliderWindow->window))
            {
                SliderWindowHandleEvent(sliderWindow, &e);
            }
        }
        else if(e.type == SDL_MOUSEMOTION)
        {
            if(e.button.windowID == SDL_GetWindowID(win))
            {
                ;
            }
            else if(e.button.windowID == SDL_GetWindowID(sliderWindow->window))
            {
                SliderWindowHandleEvent(sliderWindow, &e);
            }            
        }
	}

    return true;
}

int main()
{
    int ret;
    ret = SDL_Init(SDL_INIT_EVERYTHING);

	SDL_DisplayMode DM;
	ret = SDL_GetDesktopDisplayMode(0, &DM);
	if( ret != 0 ){
		SDL_Log("SDL_GetDesktopDisplayMode failed: %s\n", SDL_GetError());
		int64_t * p = (int64_t*)__cxa_allocate_exception(8);
		__cxa_throw(p, &_ZTIl, 0);
	}
	const int ScreenWidth = DM.w;
	const int ScreenHeight = DM.h;
    int width = 1920/2;
    int height = 1080/2;

	SDL_Window* win = SDL_CreateWindow( "a", (ScreenWidth / 2) - (width / 2), (ScreenHeight / 2) - (height / 2), width, height, SDL_WINDOW_SHOWN );

	if ( win == NULL ) {
		SDL_Log("Failed to create a window! Error: %s\n", SDL_GetError());
		int64_t * p = (int64_t*)__cxa_allocate_exception(8);
		__cxa_throw(p, &_ZTIl, 0);
	}

	SDL_Renderer* renderer = SDL_CreateRenderer( win, -1, SDL_RENDERER_ACCELERATED );

    float red = 0x00;
    float green = 0x00;
    float blue = 0x00;

    sliderWindow = malloc(sizeof(struct SliderWindow));
    SliderWindowSetup(sliderWindow, "Color", 3, 255, 24);
    SliderSetup(sliderWindow, 0, 0x00, 0xff, "Red", &red);
    SliderSetup(sliderWindow, 1, 0x00, 0xff, "Green", &green);
    SliderSetup(sliderWindow, 2, 0x00, 0xff, "Blue", &blue);

    while(Loop())
    {
        if(sliderWindow != NULL)
            SliderWindowDraw(sliderWindow);

        SDL_SetRenderDrawColor(renderer, red, green, blue, 0xff);
        SDL_RenderPresent(renderer);
        SDL_RenderClear(renderer);
        SDL_UpdateWindowSurface(win);
    }

   



    if(sliderWindow != NULL)
        SliderWindowClose(sliderWindow);
    free(sliderWindow);
    SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}