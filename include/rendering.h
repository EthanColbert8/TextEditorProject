#pragma once

#include <string>
#include <SDL.h>

bool initialize(int width, int height, SDL_Window** window, SDL_Renderer** renderer);
SDL_Texture* load_texture(std::string path, SDL_Renderer* renderer);
void cleanup(SDL_Texture* texture, SDL_Renderer* renderer, SDL_Window* window);
