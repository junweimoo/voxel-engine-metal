//
// Created by Jun Wei Moo on 19/9/24.
//

#ifndef VOXEL_H
#define VOXEL_H

enum class VoxelType {
    Air,
    Grass,
    Dirt,
    Stone,
};

struct Voxel {
    VoxelType type;

    Voxel(VoxelType type = VoxelType::Air) : type(type) {}
};

#endif // VOXEL_H
