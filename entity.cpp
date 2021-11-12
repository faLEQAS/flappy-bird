#include "camera.hpp"
#include <stdio.h>
#include <string.h>


Entity::Entity(Game* parent, char* sprite, Vector pos, Vector dim, Vector velocity, Vector speed, float gravity, int angle, int init_state, int flags, void (*thinker)(Entity* entity))
{
	this->flags = flags;
	this->sprite = sprite;
	this->gravity = gravity;
	this->parent = parent;
	this->speed = speed;
    this->pos = pos;
    this->dim = dim;
    this->angle = angle;
	this->state = init_state;
    this->think = thinker;
	if (this->parent)
	{
		this->parent->add_entity(this);
	}
}


void Entity::set_state(int new_state)
{
	this->prev_state = this->state;
	this->state = new_state;
}


void bird_think(Entity* entity)
{
	const Uint8* key_state = SDL_GetKeyboardState(nullptr);
	switch (entity->state)
	{
		case MOVE:
		{
            bird_set_move_sprite(entity);
			entity->velocity.x = entity->speed.x;
            if (entity->velocity.y < 0)
            {
                entity->angle = -30;
            }
            else
            {
                if (entity->angle != 90)
                {
                    entity->angle += 10;
                }
            }
			if (entity->flags & IS_JUMPING || entity->pos.y < entity->parent->screen_height-entity->dim.y)
			{
				if (entity->velocity.y < 0)
				{
					entity->velocity.y += (entity->gravity * 0.75);
				}
				else
				{
					entity->velocity.y += entity->gravity;
				}
			}
			entity->pos += entity->velocity;
            if (entity->pos.y < 0)
            {
                entity->pos.y -= entity->velocity.y;
            }
            Entity* collider = entity->get_collider(entity->pos, entity->dim);
            if (collider)
            {
                entity->set_state(DEATH);
            }
			if (entity->pos.y > entity->parent->screen_height-entity->dim.y)
			{
                entity->set_state(DEATH);
			}
		} break;

        case DEATH:
        {
            entity->pos.y = 0;
            entity->pos.x = 0;
            entity->velocity = 0;
            entity->state = MOVE;
            for (int i = 0; i < MAX_ENTITIES; i++)
            {
                Entity* e = entity->parent->entities[i];
                if (e && e != entity)
                {
                    delete e;
                    entity->parent->entities[i] = nullptr;
                }
            }
            entity->parent->frames = 0;
        } break;
	}
}

void bird_set_move_sprite(Entity* entity)
{
    if (!entity->sprite)
    {
	    entity->sprite = "bird_mid_flap";
    }
    else if (entity->parent->frames % 3 == 0)
    {
        if (strcmp(entity->sprite, "bird_mid_flap") == 0)
        {
            entity->sprite = "bird_up_flap";
        }
        else if (strcmp(entity->sprite, "bird_up_flap") == 0)
        {
            entity->sprite = "bird_down_flap";
        }
        else
        {
            entity->sprite = "bird_mid_flap";
        }
    }
}

void Entity::start_jump()
{
	this->flags |= IS_JUMPING;
	this->velocity.y = -this->speed.y;
}


Entity* Entity::get_collider(Vector a_pos, Vector a_dim)
{
    if (!this->parent)
    {
        return nullptr;
    }
    for (int i = 0; i < MAX_ENTITIES; i++)
    {
        Entity* entity = this->parent->entities[i];
        if (entity && entity != this)
        {
            if (is_colliding_with(a_pos, a_dim, entity->pos, entity->dim))
            {
                return entity;
            }
        }
    }
    return nullptr;
}

bool is_colliding_with(Vector a_pos, Vector a_dim, Vector b_pos, Vector b_dim)
{
	return
	(
		a_pos.x < b_pos.x + b_dim.x &&
		a_pos.x + a_dim.x > b_pos.x &&
		a_pos.y < b_pos.y + b_dim.y &&
		a_pos.y + a_dim.y > b_pos.y
	);
}