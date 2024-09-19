//
// Created by Jun Wei Moo on 19/9/24.
//

#ifndef CHUNK_H
#define CHUNK_H

#include "Voxel.h"
#include "Renderer.h"
#include "Camera.h"
#include "utils/Math.h"
#include <vector>

class Chunk {
public:
    static const int SIZE = 16;

    Chunk(int x, int y, int z, Renderer* renderer);
    ~Chunk();

    void Initialize();
    void GenerateVoxels();
    void CreateMesh();
    void Render(Camera* camera, MTK::View* pView);

private:
    int posX, posY, posZ;
    Voxel voxels[SIZE][SIZE][SIZE];
    Renderer* renderer;

    // Mesh data
    std::vector<float> vertexData;

    MTL::Buffer* vertexBuffer;

    void AddVoxelMesh(int x, int y, int z, VoxelType type);
};

#endif // CHUNK_H
