#include "camera.hpp"
#include <stdio.h>
#include <time.h>
#include "util.hpp"
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

Vector NO_VECTOR = {0, 0};


Game::Game(int screen_width, int screen_height, char* caption, char* asset_file)
{
	this->screen_width = screen_width;
	this->screen_height = screen_height;
	this->caption = caption;
	this->init_sdl2();
	this->asset_manager = new AssetManager(renderer, asset_file);
	for (int i = 0; i < MAX_ENTITIES; i++)
 	{
		this->entities[i] = nullptr;
	}
}

Game::~Game()
{
	for (int i = 0; i < MAX_ENTITIES; i++)
	{
		if (this->entities[i])
		{
			delete this->entities[i];
		}
	}
	SDL_DestroyRenderer(this->renderer);
	SDL_DestroyWindow(this->window);
	delete this->asset_manager;
}

void Game::loop()
{
    srand(time(nullptr));
    Vector pos = {this->screen_width/3, 64};
    Vector dim = {48, 48};
    Vector speed = {6, 8};
    Vector velocity = {3, 0};
    Vector cam_pos = {0, 0};
    this->player = new Entity(this, "bird_mid_flap", pos, dim, velocity, speed, 0.5, 0, MOVE, 0, &bird_think);
    this->camera = new Camera(cam_pos, this->player, &player_camera_update);
    this->state = RUNNING;
    while (this->state == RUNNING)
    {
		SDL_SetRenderDrawColor(this->renderer, 60, 60, 60, 255);
		SDL_RenderClear(this->renderer);
        this->input();
		this->update();
        SDL_RenderPresent(this->renderer);
		#ifdef _WIN32
		Sleep(16);
		#else
		usleep(16);
		#endif
		this->frames++;
        if (this->frames % 100 == 0 && this->player->state)
        {
            this->spawn_walls();
        }
        this->score = this->frames;
    }
}


void Game::spawn_walls()
{
    for (int i = 0; i < 2; i++)
    {
        int angle = 0;
        Vector wall_dim = {96, 0};
        wall_dim.y = random(128, (this->screen_height/2) - this->player->dim.y);
        Vector wall_pos = this->player->pos;
        wall_pos.x *= 1.5;
        wall_pos.y = this->screen_height-wall_dim.y;
        if (i == 0)
        {
            wall_pos.y = 0;
            angle = 180;
        }
        Entity* wall = new Entity(this, "pipe", wall_pos, wall_dim, NO_VECTOR, NO_VECTOR, 0, angle, 0, 0, nullptr);
    }
}


void Game::input()
{
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		switch (e.type)
		{
			case SDL_QUIT:
			{
				this->state = EXIT;
			} break;
			
			case SDL_KEYDOWN:
			{
				switch (e.key.keysym.scancode)
				{
					case SDL_SCANCODE_SPACE:
					{
                        if (!this->player->state)
                        {
                            this->player->set_state(MOVE);
                        }
                        else if (this->player->state == MOVE)
                        {
						    this->player->start_jump();
                        }
					} break;
				}
			} break;
		}
	}
}

void Game::update()
{
    this->asset_manager->get_sprite("background")->draw(this->renderer, 0, 0, this->screen_width, this->screen_height,
                                    0);
	for (int i = 0; i < MAX_ENTITIES; i++)
	{
		if (this->entities[i])
		{
            //position on screen
			Entity* entity = this->entities[i];
            Vector pos = entity->pos - this->camera->pos;
            if (pos.x < -200)
            {
                //kill entity
                this->entities[i] = nullptr;
                delete entity;
                continue;
            }
			if (entity->think)
			{
				entity->think(entity);
			}
			Sprite* sprite = this->asset_manager->get_sprite(entity->sprite);
			if (sprite)
			{
				sprite->draw(this->renderer, pos.x, pos.y, entity->dim.x, entity->dim.y, entity->angle);
			}
		}
	}
    this->camera->update(this->camera);
    this->draw_score();
}

void Game::draw_score()
{
    int x = 0;
    char str[12]; //32 bit ints can be represented as an array of 12 chars
    sprintf(str, "%d", this->score);
    int len = strlen(str);
    for (int i = 0; i < len; i++)
    {
        char name[6] = {"num_0"};
        name[4] = str[i];
        this->asset_manager->get_sprite(name)->draw(this->renderer, x, 0, 32, 32, 0);
        x += 32;
    }
}

void Game::add_entity(Entity* entity)
{
	for (int i = 0; i < MAX_ENTITIES; i++)
	{
		if (!this->entities[i])
		{
			this->entities[i] = entity;
			break;
		}
	}
}

int Game::init_sdl2()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("Initializing SDL failed.\n");
		return 1;
	}

	this->window = SDL_CreateWindow(this->caption,
						  SDL_WINDOWPOS_CENTERED,
						  SDL_WINDOWPOS_CENTERED,
						  this->screen_width, this->screen_height,
						  0);

	if (!this->window)
	{
		printf("Initializing Window failed.\n");
		return 2;
	}
	
	this->renderer =  SDL_CreateRenderer(this->window, -1, false);
	if (!this->renderer)
	{
		printf("Initializing renderer failed.\n");
		return 3;
	}
    return 0;
}