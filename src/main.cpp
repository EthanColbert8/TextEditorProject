#include "SDL_render.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL2_gfxPrimitives.h>
#include <iostream>
// #include <cmath>

// void DrawRoundedRect(SDL_Renderer* renderer, SDL_Rect rect, int radius, SDL_Color color)
// {
//     // Fill center
//     SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
//     SDL_Rect inner = { rect.x + radius, rect.y, rect.w - 2 * radius, rect.h };
//     SDL_RenderFillRect(renderer, &inner);
//     inner = { rect.x, rect.y + radius, rect.w, rect.h - 2 * radius };
//     SDL_RenderFillRect(renderer, &inner);

//     // Draw corners as filled quarter circles (approximation)
//     for (int w = 0; w < radius; ++w)
//     for (int h = 0; h < radius; ++h)
//         if ((w*w + h*h) <= radius*radius) {
//             // Top-left
//             SDL_RenderDrawPoint(renderer, rect.x + radius - w, rect.y + radius - h);
//             // Top-right
//             SDL_RenderDrawPoint(renderer, rect.x + rect.w - radius + w - 1, rect.y + radius - h);
//             // Bottom-left
//             SDL_RenderDrawPoint(renderer, rect.x + radius - w, rect.y + rect.h - radius + h - 1);
//             // Bottom-right
//             SDL_RenderDrawPoint(renderer, rect.x + rect.w - radius + w - 1, rect.y + rect.h - radius + h - 1);
//         }
// }

int main(int argc, char** argv)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << "\n";
        return 1;
    }

    if (TTF_Init() != 0) {
        std::cerr << "TTF_Init Error: " << TTF_GetError() << "\n";
        SDL_Quit();
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow(
        "Text Editor Prototype",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        800, 600,
        SDL_WINDOW_SHOWN
    );
    if (!window) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << "\n";
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << "\n";
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    // Disable texture filtering for sharp text
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");

    int drawable_w, drawable_h;
    SDL_GetRendererOutputSize(renderer, &drawable_w, &drawable_h);
    SDL_RenderSetLogicalSize(renderer, drawable_w, drawable_h);

    // Load your font
    const char* fontPath = "/usr/share/fonts/OTF/CommitMonoNerdFont-Regular.otf";
    TTF_Font* font = TTF_OpenFont(fontPath, 24);
    if (!font) {
        std::cerr << "Failed to load font: " << TTF_GetError() << "\n";
        return 1;
    }

    SDL_Color bg = {40, 44, 52, 255};
    SDL_Color accent = {100, 150, 255, 255};
    SDL_Color textColor = {255, 255, 255, 255};
    SDL_Surface* textSurface = TTF_RenderUTF8_Blended(font, "Heyo, SDL2 with GFX!", textColor);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

    SDL_Rect textRect = {60, 80, textSurface->w, textSurface->h};
    SDL_FreeSurface(textSurface);

    bool running = true;
    SDL_Event e;
    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) { running = false; }
        }

        SDL_SetRenderDrawColor(renderer, bg.r, bg.g, bg.b, bg.a);
        SDL_RenderClear(renderer);

        // Draw rounded rect background
        // SDL_Rect rect = {200, 200, 400, 100};
        // DrawRoundedRect(renderer, rect, 20, accent);
        roundedBoxRGBA(renderer, 50, 50, 400, 200, 16, accent.r, accent.g, accent.b, accent.a);

        SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);

        // // Render text
        // SDL_Surface* textSurface = TTF_RenderUTF8_Blended(font, "Hello, SDL2 + TTF!", textColor);
        // SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

        // int textW, textH;
        // SDL_QueryTexture(textTexture, nullptr, nullptr, &textW, &textH);

        // SDL_Rect dstRect = {
        //     rect.x + (rect.w - textW) / 2,
        //     rect.y + (rect.h - textH) / 2,
        //     textW, textH
        // };
        // SDL_RenderCopy(renderer, textTexture, nullptr, &dstRect);

        // SDL_FreeSurface(textSurface);
        // SDL_DestroyTexture(textTexture);

        SDL_RenderPresent(renderer);
    }

    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
    return 0;
}
