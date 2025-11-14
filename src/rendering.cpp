#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>

#include "rendering.h"
#include "SDL_render.h"

bool init_libraries();

/**
 * Need the double pointers to actually modify pointer-valued variables in calling function.
 */
bool initialize(int width, int height, SDL_Window** window, SDL_Renderer** renderer) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "Error initializing SDL: " << SDL_GetError() << "\n";
        return false;
    }

    // Create a window
    *window = SDL_CreateWindow("First window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (window == NULL) {
        std::cerr << "Error creating window: " << SDL_GetError() << "\n";
        return false;
    }

    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        std::cerr << "Error creating renderer: " << SDL_GetError() << "\n";
        return false;
    }
    SDL_SetRenderDrawColor(*renderer, 0x14, 0x08, 0x40, 0xFF);

    // initialize other SDL libraries
    // if (!init_libraries()) { return false; }

    return true;
}

SDL_Texture* load_texture(std::string path, SDL_Renderer* renderer) {
    SDL_Texture* texture = NULL;

    SDL_Surface* imageSurface = IMG_Load(path.c_str());
    if (imageSurface == NULL) {
        std::cerr << "Error loading image: " << IMG_GetError() << "\n";
        return texture;
    }

    texture = SDL_CreateTextureFromSurface(renderer, imageSurface);
    if (texture == NULL) {
        std::cerr << "Error creating texture: " << SDL_GetError() << "\n";
        //return texture;
    }

    SDL_FreeSurface(imageSurface);
    return texture;
}

void cleanup(SDL_Texture* texture, SDL_Renderer* renderer, SDL_Window* window) {
    //SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    //IMG_Quit();
    SDL_Quit();
}

/*
 * Helper function to load additional libraries.
 */
bool init_libraries() {
    int imgFlags = IMG_INIT_JPG;
    // Weird logic to test whether the flags we need are returned,
    // which happens if the library initialized them successfully.
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        std::cerr << "Error initializing image library: " << IMG_GetError() << "\n";
        return false;
    }

    return true;
}
