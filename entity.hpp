#include "sprite.hpp"
#include "vector.hpp"
struct Game;

//states
enum
{
	MOVE = 1,
    DEATH = 2
};

//flags
enum
{
	IS_JUMPING = 1
};

struct Entity
{
    Vector pos;
    Vector dim;
	Vector speed;
	Vector velocity;
	float gravity;
    int angle;
	int flags;
	int state;
	int prev_state;
	char* sprite;
	Game* parent;
    Entity(Game* parent, char* sprite, Vector pos, Vector dim, Vector velocity, Vector speed, float gravity, int angle, int init_state, int flags, void (*thinker)(Entity* entity));
    Entity* get_collider(Vector a_pos, Vector b_pos);
	void start_jump();
	void set_state(int new_state);
    void (*think)(Entity* entity);
};


bool is_colliding_with(Vector a_pos, Vector a_dim, Vector b_pos, Vector b_dim);
void bird_think(Entity* entity);
void bird_set_move_sprite(Entity* entity);