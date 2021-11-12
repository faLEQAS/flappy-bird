#include "camera.hpp"
#include <stdio.h>

Camera::Camera(Vector pos, Entity* parent, void (*update)(Camera* camera))
{
    this->pos = pos;
    this->parent = parent;
    this->update = update;
}

void player_camera_update(Camera* camera)
{
    if (!camera->parent)
    {
        return;
    }
    camera->pos.x = ((camera->parent->pos.x) + camera->parent->dim.x / 2) - camera->parent->parent->screen_width / 2;
    camera->pos.y = 0;
}