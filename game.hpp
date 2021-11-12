#include "asset_manager.hpp"
#include "entity.hpp"
const int MAX_ENTITIES = 20;

enum
{
    RESTART = 0,
    EXIT = -1,
    RUNNING = 1
};

struct Camera;

struct Game
{
    int score = 0;
	int state;
	AssetManager* asset_manager = nullptr;
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
    Camera* camera = nullptr;
    Entity* player = nullptr;
	Entity* entities[MAX_ENTITIES];
	int frames = 0;
	int screen_width;
	int screen_height;
	char* caption;
	Game(int screen_width, int screen_height, char* caption, char* asset_file);
	~Game();
	int init_sdl2();
	void loop();
	void input();
	void update();
    void spawn_walls();
	void add_entity(Entity* entity);
    void draw_score();
};