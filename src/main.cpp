#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>

#include "rendering.h"

float get_framerate(int numFrames);

int main (int argc, char* argv[]) {
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_Texture* textTexture = nullptr;
    TTF_Font* font = nullptr;
    SDL_Color textColor = {0xFF, 0xFF, 0xFF, 0xFF};
    SDL_Rect rect, textRect;
    std::string displayText;

    int width = 800;
    int height = 600;
    int framesRendered = 0;

    // Do SDL and renderer initialization
    if (!initialize(width, height, &window, &renderer)) { return 1; }

    // Load font from system font installation - should do this dynamically in
    // some way later I guess.
    font = load_font("/usr/share/fonts/OTF/CommitMonoNerdFont-Regular.otf", 24);
    if (font == nullptr) { return 1; }

    displayText = "Here we go.";
    textTexture = load_font_texture(displayText, textColor, font, renderer);

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

        framesRendered += 1;
        if (framesRendered % 10000 == 0) {
            std::cout << "Avg framerate after " << framesRendered << " frames: " << get_framerate(framesRendered) << "\n";
        }

        rect.x = width/4;
        rect.y = height/4;
        rect.w = width/2;
        rect.h = height/2;

        textRect.x = width/4;
        textRect.y = height/4;
        SDL_QueryTexture(textTexture, NULL, NULL, &textRect.w, &textRect.h);

        SDL_SetRenderDrawColor(renderer, 0x14, 0x08, 0x40, 0x22);
        SDL_RenderClear(renderer);

        //SDL_RenderCopy(renderer, imageTexture, NULL, NULL);
        SDL_SetRenderDrawColor(renderer, 0x18, 0x98, 0xDC, 0x4A);
        SDL_RenderFillRect(renderer, &rect);

        SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);

        SDL_RenderPresent(renderer);
    }

    // Cleanup
    // REMEMBER: All these pointers point to null now (doesn't matter in this case, but still)
    cleanup(font, textTexture, renderer, window);

    return 0;
}

float get_framerate(int numFrames) {
    float milliSeconds = (float)SDL_GetTicks();
    return (numFrames / milliSeconds) * 1000.0f;
}
