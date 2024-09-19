//
// Created by Jun Wei Moo on 19/9/24.
//

#include "Chunk.h"
#include "Renderer.h"
#include "Camera.h"

Chunk::Chunk(int x, int y, int z, Renderer* renderer)
    : posX(x), posY(y), posZ(z), renderer(renderer), vertexBuffer(nullptr) {
    Initialize();
}

Chunk::~Chunk() {
    if (vertexBuffer) {
        vertexBuffer->release();
    }
}

void Chunk::Initialize() {
    GenerateVoxels();
    CreateMesh();
}

void Chunk::GenerateVoxels() {
    for (int x = 0; x < SIZE; ++x) {
        for (int y = 0; y < SIZE; ++y) {
            for (int z = 0; z < SIZE; ++z) {
                if (y < 8)
                    voxels[x][y][z] = Voxel(VoxelType::Stone);
                else if (y < 10)
                    voxels[x][y][z] = Voxel(VoxelType::Dirt);
                else if (y < 12)
                    voxels[x][y][z] = Voxel(VoxelType::Grass);
                else
                    voxels[x][y][z] = Voxel(VoxelType::Air);
            }
        }
    }
}

void Chunk::CreateMesh() {
    vertexData.clear();

    for (int x = 0; x < SIZE; ++x) {
        for (int y = 0; y < SIZE; ++y) {
            for (int z = 0; z < SIZE; ++z) {
                Voxel voxel = voxels[x][y][z];
                if (voxel.type != VoxelType::Air) {
                    AddVoxelMesh(x, y, z, voxel.type);
                }
            }
        }
    }

    // Create Metal buffer
    if (!vertexData.empty()) {
        MTL::Device* device = renderer->getDevice();
        vertexBuffer = device->newBuffer(vertexData.data(), vertexData.size() * sizeof(float), MTL::ResourceStorageModeShared);
    }
}

void Chunk::AddVoxelMesh(int x, int y, int z, VoxelType type) {
    float voxelSize = 1.0f; // Adjust as needed
    float px = posX * SIZE + x * voxelSize;
    float py = posY * SIZE + y * voxelSize;
    float pz = posZ * SIZE + z * voxelSize;

    // Front face
    vertexData.insert(vertexData.end(), {
        px,      py,      pz + voxelSize, // Vertex 1
        1.0f, 1.0f, 1.0f,
        px + voxelSize, py,      pz + voxelSize, // Vertex 2
        1.0f, 1.0f, 1.0f,
        px + voxelSize, py + voxelSize, pz + voxelSize, // Vertex 3
        1.0f, 1.0f, 1.0f,
        px,      py + voxelSize, pz + voxelSize, // Vertex 4
        1.0f, 1.0f, 1.0f
    });

    // Back face
    vertexData.insert(vertexData.end(), {
        px,      py,      pz, // Vertex 1
        1.0f, 1.0f, 1.0f,
        px + voxelSize, py,      pz, // Vertex 2
        1.0f, 1.0f, 1.0f,
        px + voxelSize, py + voxelSize, pz, // Vertex 3
        1.0f, 1.0f, 1.0f,
        px,      py + voxelSize, pz, // Vertex 4
        1.0f, 1.0f, 1.0f
    });

    // Left face
    vertexData.insert(vertexData.end(), {
        px,      py,      pz, // Vertex 1
        1.0f, 1.0f, 1.0f,
        px,      py,      pz + voxelSize, // Vertex 2
        1.0f, 1.0f, 1.0f,
        px,      py + voxelSize, pz + voxelSize, // Vertex 3
        1.0f, 1.0f, 1.0f,
        px,      py + voxelSize, pz, // Vertex 4
        1.0f, 1.0f, 1.0f
    });

    // Right face
    vertexData.insert(vertexData.end(), {
        px + voxelSize, py,      pz, // Vertex 1
        1.0f, 1.0f, 1.0f,
        px + voxelSize, py,      pz + voxelSize, // Vertex 2
        1.0f, 1.0f, 1.0f,
        px + voxelSize, py + voxelSize, pz + voxelSize, // Vertex 3
        1.0f, 1.0f, 1.0f,
        px + voxelSize, py + voxelSize, pz, // Vertex 4
        1.0f, 1.0f, 1.0f
    });

    // Top face
    vertexData.insert(vertexData.end(), {
        px,      py + voxelSize, pz, // Vertex 1
        1.0f, 1.0f, 1.0f,
        px + voxelSize, py + voxelSize, pz, // Vertex 2
        1.0f, 1.0f, 1.0f,
        px + voxelSize, py + voxelSize, pz + voxelSize, // Vertex 3
        1.0f, 1.0f, 1.0f,
        px,      py + voxelSize, pz + voxelSize, // Vertex 4
        1.0f, 1.0f, 1.0f
    });

    // Bottom face
    vertexData.insert(vertexData.end(), {
        px,      py,      pz, // Vertex 1
        1.0f, 1.0f, 1.0f,
        px + voxelSize, py,      pz, // Vertex 2
        1.0f, 1.0f, 1.0f,
        px + voxelSize, py,      pz + voxelSize, // Vertex 3
        1.0f, 1.0f, 1.0f,
        px,      py,      pz + voxelSize, // Vertex 4
        1.0f, 1.0f, 1.0f
    });
}


// Render the chunk
void Chunk::Render(Camera* camera, MTK::View* pView) {
    if (!vertexBuffer) return;

    // Get the current command buffer and render command encoder from the renderer
    MTL::CommandQueue* queue = renderer->getCommandQueue();
    MTL::CommandBuffer* cmdBuffer = queue->commandBuffer();
    MTL::RenderPassDescriptor* rpd = pView->currentRenderPassDescriptor();
    MTL::RenderCommandEncoder* renderEncoder = cmdBuffer->renderCommandEncoder(rpd);

    // Set the pipeline state
    renderEncoder->setRenderPipelineState(renderer->getPipelineState());

    // Set vertex buffer
    renderEncoder->setVertexBuffer(vertexBuffer, 0, 0);

    // Prepare transformation matrices
    Matrix4x4 viewProj = camera->GetViewProjectionMatrix();
    renderEncoder->setVertexBytes(&viewProj, sizeof(Matrix4x4), 1);

    // Draw the vertices
    renderEncoder->drawPrimitives(MTL::PrimitiveType::PrimitiveTypeTriangle, 1, vertexData.size() / 6);

    // End encoding
    renderEncoder->endEncoding();

    // Commit the command buffer for execution
    cmdBuffer->commit();
}