//
// Created by Jun Wei Moo on 16/9/24.
//

#ifndef RENDERER_H
#define RENDERER_H

#include <Metal/Metal.hpp>
#include <AppKit/AppKit.hpp>
#include <MetalKit/MetalKit.hpp>

class Renderer {
public:
    Renderer(MTL::Device* pDevice);
    ~Renderer();

    void draw(MTK::View* pView);

    MTL::Device* getDevice();
    MTL::CommandQueue* getCommandQueue();
    MTL::RenderPipelineState* getPipelineState();

private:
    MTL::Device* device;
    MTL::CommandQueue* commandQueue;
    MTL::Library* defaultLibrary;
    MTL::RenderPipelineState *pipelineState;

    bool loadShaders();
    bool createPipelineState();
};

#endif //RENDERER_H
