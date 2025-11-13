#include <SDL.h>
#include <SDL_image.h>

#include "rendering.h"

int main (int argc, char* argv[]) {
    // Declare window assets
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_Texture* imageTexture = nullptr;

    int width = 800;
    int height = 600;

    // Do SDL and renderer initialization
    if (!initialize(width, height, &window, &renderer)) { return 1; }

    // Load the image as a texture for the renderer.
    std::string imagePath = "/home/emcol/Pictures/wallpapers/Sarah_Morgan.jpg";
    imageTexture = load_texture(imagePath, renderer);
    if (imageTexture == NULL) { return 1; }

    // A proper render loop now.
    SDL_Event e;
    bool keepGoing = true;
    while(keepGoing) {
        while(SDL_PollEvent(&e) != 0) {
            if( e.type == SDL_QUIT ) {
                  keepGoing = false;
            }
        }

        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, imageTexture, NULL, NULL);
        SDL_RenderPresent(renderer);
    }

    // Cleanup
    // REMEMBER: All these pointers point to null now (doesn't matter in this case, but still)
    cleanup(imageTexture, renderer, window);

    return 0;
}
