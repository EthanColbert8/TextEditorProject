#include <SDL.h>
#include <SDL_image.h>

#include "rendering.h"

int main (int argc, char* argv[]) {
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    //SDL_Texture* imageTexture = nullptr;
    SDL_Rect rect;

    int width = 800;
    int height = 600;

    // Do SDL and renderer initialization
    if (!initialize(width, height, &window, &renderer)) { return 1; }

    // Load the image as a texture for the renderer.
    // std::string imagePath = "/home/emcol/Pictures/wallpapers/Sarah_Morgan.jpg";
    // imageTexture = load_texture(imagePath, renderer);
    // if (imageTexture == NULL) { return 1; }

    SDL_Event e;
    bool keepGoing = true;
    while(keepGoing) {
        while(SDL_PollEvent(&e) != 0) {
            switch (e.type) {
                case SDL_QUIT:
                    keepGoing = false;
                break;

                case SDL_WINDOWEVENT:
                    if (e.window.event == SDL_WINDOWEVENT_RESIZED) {
                        SDL_GetWindowSize(window, &width, &height);
                    }
                break;
            }
        }

        rect = {
            width/4,
            height/4,
            width/2,
            height/2
        };

        SDL_SetRenderDrawColor(renderer, 0x14, 0x08, 0x40, 0xFF);
        SDL_RenderClear(renderer);

        //SDL_RenderCopy(renderer, imageTexture, NULL, NULL);
        SDL_SetRenderDrawColor(renderer, 0x18, 0x98, 0xDC, 0xFF);
        SDL_RenderFillRect(renderer, &rect);

        SDL_RenderPresent(renderer);
    }

    // Cleanup
    // REMEMBER: All these pointers point to null now (doesn't matter in this case, but still)
    cleanup(nullptr, renderer, window);

    return 0;
}
