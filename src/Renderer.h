//
// Created by Jun Wei Moo on 16/9/24.
//

#ifndef RENDERER_H
#define RENDERER_H

#include <Metal/Metal.hpp>
#include <AppKit/AppKit.hpp>
#include <MetalKit/MetalKit.hpp>

#include "Camera.h"

class World;

class Renderer {
public:
    Renderer(MTL::Device* pDevice);
    ~Renderer();

    void beginFrame();
    void endFrame();
    void draw(MTK::View* pView, World* world, Camera* camera);

    MTL::Device* getDevice();
    MTL::CommandQueue* getCommandQueue();
    MTL::RenderPipelineState* getPipelineState();

private:
    MTL::Device* device;
    MTL::CommandQueue* commandQueue;
    MTL::Library* defaultLibrary;
    MTL::RenderPipelineState* pipelineState;
    MTL::VertexDescriptor* vertexDescriptor;

    bool loadShaders();
    bool createPipelineState();
    MTL::VertexDescriptor* createVertexDescriptor();
};

#endif //RENDERER_H
