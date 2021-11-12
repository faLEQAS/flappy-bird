#include "game.hpp"

struct Camera
{
    Vector pos;
    Entity* parent = nullptr;
    Camera(Vector pos, Entity* parent, void (*update)(Camera* camera));
    void (*update)(Camera* camera);
};

void player_camera_update(Camera* camera);