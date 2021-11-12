#include "asset_manager.hpp"
#include <stdio.h>
#include "util.hpp"
#include <stdlib.h>
#include "sprite.hpp"
#include <string.h>

AssetManager::AssetManager(SDL_Renderer* renderer, const char* path)
{
    this->_renderer = renderer;
    this->_sprite_table = new HashTable();
	this->load_assets(path);
}

AssetManager::~AssetManager()
{
	for (int i = 0; i < this->_sprite_table->len; i++)
	{
		delete (Sprite*)this->_sprite_table->_arr[i];
	}
    delete this->_sprite_table;
}

void AssetManager::load_assets(const char* path)
{
    FILE* fp = fopen(path, "r");
    if (!fp)
    {
        return;
    }
    for (char* s = fgetline(fp); s; s = fgetline(fp))
    {
        int len;
        char** arr = split_str(s, '=', &len);
        printf("%s\n", arr[1]);
		if (len == 3)
		{
			if (strcasecmp(arr[0], "sprite") == 0)
			{
				Sprite* sprite = new Sprite(this->_renderer, arr[2]);
                if (sprite)
                {
				    this->_sprite_table->add(arr[1], (void*)sprite);
                }
                else
                {
                    printf("loading sprite failed\n");
                }
			}
		}
        free(s);
        for (int i = 0; i < len; i++)
        {
            free(arr[i]);
        }
        free(arr);
    }
    fclose(fp);
}

Sprite* AssetManager::get_sprite(const char* name) const
{
	void* thing = this->_sprite_table->get(name);
    if (thing)
	{
		return (Sprite*)thing;
	}
	return nullptr;
}