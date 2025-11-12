#include "SDL_video.h"
#include "SDL_image.h"
#include <SDL.h>
#include <iostream>

int main (int argc, char* argv[]) {
    // Declare window assets
    SDL_Window* window = nullptr;
    SDL_Surface* screenSurface = nullptr;
    SDL_Surface* imageSurface = nullptr;

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "Error initializing SDL: " << SDL_GetError() << "\n";
        return 1;
    }

    if (IMG_Init(IMG_INIT_JPG) == 0) {
        std::cerr << "Error initializing image library: " << SDL_GetError() << "\n";
        return 1;
    }

    // Create a window
    window = SDL_CreateWindow("First window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (window == NULL) {
        std::cerr << "Error creating window: " << SDL_GetError() << "\n";
        return 1;
    }

    // Get the window's surface and fill with white
    screenSurface = SDL_GetWindowSurface(window);
    // SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
    // SDL_UpdateWindowSurface(window);

    // Load image of sarah morgan (test)
    imageSurface = IMG_Load("/home/emcol/Pictures/wallpapers/Sarah_Morgan.jpg");
    if (imageSurface == NULL) {
        std::cerr << "Error loading image: " << SDL_GetError() << "\n";
    }

    SDL_BlitSurface(imageSurface, NULL, screenSurface, NULL);
    SDL_UpdateWindowSurface(window);

    // Hack to get window to stay open (hopefully only used very briefly)
    // Edit: this is an actual render loop, just doesn't do any rendering lol.
    SDL_Event e; bool quit = false; while( quit == false ){ while( SDL_PollEvent( &e ) ){ if( e.type == SDL_QUIT ) quit = true; } }

    // Cleanup
    SDL_FreeSurface(imageSurface);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();

    return 0;
}
