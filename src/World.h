//
// Created by Jun Wei Moo on 16/9/24.
//

#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include "Chunk.h"
#include "Camera.h"
#include "World.h"

class World {
public:
    World(Renderer* renderer_, Camera* camera_);
    ~World();

    bool Initialize();
    void Render(MTK::View* view);
    void Update(float deltaTime);

private:
    Renderer* renderer;
    Camera* camera;

    // TODO: make this multiple chunks with load and unload ability
    Chunk* chunk;
};

#endif // WORLD_H
