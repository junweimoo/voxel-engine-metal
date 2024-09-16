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

private:
    MTL::Device* _pDevice;
    MTL::CommandQueue* _pCommandQueue;
};

#endif //RENDERER_H
