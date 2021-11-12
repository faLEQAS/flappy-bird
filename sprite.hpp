#include <SDL.h>
#include <SDL_image.h>

struct Sprite
{
    Sprite(SDL_Renderer* renderer, const char* path);
    ~Sprite();
    void draw(SDL_Renderer* renderer, const int x, const int y, const int width, const int height, const int angle) const;
    SDL_Texture* _texture;
};