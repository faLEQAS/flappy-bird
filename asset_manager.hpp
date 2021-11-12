#include "hash_table.hpp"
struct SDL_Renderer;
struct Sprite;

struct AssetManager
{
    HashTable* _sprite_table = nullptr;
    SDL_Renderer* _renderer = nullptr;
    AssetManager(SDL_Renderer* renderer, const char* path);
    ~AssetManager();
	void load_assets(const char* path);
    Sprite* get_sprite(const char* name) const;
};
