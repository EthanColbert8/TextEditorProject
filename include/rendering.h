#pragma once

#include <string>
#include <SDL.h>
#include <SDL_ttf.h>

bool initialize(int width, int height, SDL_Window** window, SDL_Renderer** renderer);
//SDL_Texture* load_texture(std::string path, SDL_Renderer* renderer);
TTF_Font* load_font(std::string path, int ptsize);
SDL_Texture* load_font_texture(std::string text, SDL_Color color, TTF_Font* font, SDL_Renderer* renderer);
void cleanup(TTF_Font* font, SDL_Texture* texture, SDL_Renderer* renderer, SDL_Window* window);
