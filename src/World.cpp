//
// Created by Jun Wei Moo on 16/9/24.
//

#include <iostream>
#include "World.h"

World::World(Renderer* renderer_, Camera* camera_)
    : renderer(renderer_), camera(camera_) {
    Initialize();
}

// Destructor
World::~World() {
    delete chunk;
}

// Initialize the world by loading initial chunks
bool World::Initialize() {
    chunk = new Chunk(1, 1, 0, renderer);
    return true;
}

// Render all loaded chunks
void World::Render(MTK::View* view) {
    chunk->Render(camera, view);
}

// Update the world (e.g., load/unload chunks based on camera position)
void World::Update(float deltaTime) {

}