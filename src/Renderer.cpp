//
// Created by Jun Wei Moo on 16/9/24.
//

#include "Renderer.h"

#include <iostream>

#include "Camera.h"
#include "World.h"

Renderer::Renderer(MTL::Device *pDevice): device(pDevice->retain())  {
    commandQueue = device->newCommandQueue();
    loadShaders();
    createPipelineState();
}

Renderer::~Renderer() {
    if (pipelineState) { pipelineState->release(); }
    if (defaultLibrary) { defaultLibrary->release(); }
    if (commandQueue) { commandQueue->release(); }
    if (device) { device->release(); }
}

MTL::Device* Renderer::getDevice() {
    return device;
}

MTL::CommandQueue* Renderer::getCommandQueue() {
    return commandQueue;
}

MTL::RenderPipelineState* Renderer::getPipelineState() {
    return pipelineState;
}

void Renderer::draw(MTK::View* pView, World* world, Camera* camera) {
    NS::AutoreleasePool* pPool = NS::AutoreleasePool::alloc()->init();

    MTL::CommandBuffer* pCmd = commandQueue->commandBuffer();
    MTL::RenderPassDescriptor* pRpd = pView->currentRenderPassDescriptor();
    MTL::RenderCommandEncoder* pEnc = pCmd->renderCommandEncoder( pRpd );
    pEnc->endEncoding();

    world->Render(pView);

    pCmd->presentDrawable( pView->currentDrawable() );
    pCmd->commit();

    pPool->release();
}

// Load Metal shaders from the default library
bool Renderer::loadShaders() {
    const char* shaderSrc = R"(
        #include <metal_stdlib>
        using namespace metal;

        struct VertexIn {
            float3 position [[ attribute(0) ]];
            float3 color [[ attribute(1) ]];
        };

        struct VertexOut {
            float4 position [[ position ]];
            float3 color;
        };

        struct ViewProjection {
            float4x4 viewProjectionMatrix;
        };

        vertex VertexOut vertexMain(const VertexIn in [[ stage_in ]],
                                     constant ViewProjection& vp [[ buffer(1) ]]) {
            VertexOut out;
            float4 pos = float4(in.position, 1.0);
            out.position = vp.viewProjectionMatrix * pos;
            out.color = in.color;
            return out;
        }

        fragment float4 fragmentMain(VertexOut in [[ stage_in ]]) {
            return float4(in.color, 1.0);
        }
    )";

    NS::Error* pError = nullptr;
    defaultLibrary = device->newLibrary( NS::String::string(shaderSrc, NS::UTF8StringEncoding), nullptr, &pError );
    return true;
}

// Create the render pipeline state
bool Renderer::createPipelineState() {
    NS::Error* error = nullptr;

    MTL::Function* vertexFunction = defaultLibrary->newFunction(NS::String::string("vertexMain", NS::UTF8StringEncoding));
    MTL::Function* fragmentFunction = defaultLibrary->newFunction(NS::String::string("fragmentMain", NS::UTF8StringEncoding));

    MTL::RenderPipelineDescriptor* pipelineDescriptor = MTL::RenderPipelineDescriptor::alloc()->init();
    pipelineDescriptor->setVertexFunction(vertexFunction);
    pipelineDescriptor->setFragmentFunction(fragmentFunction);
    pipelineDescriptor->colorAttachments()->object(0)->setPixelFormat(MTL::PixelFormatBGRA8Unorm);

    vertexDescriptor = createVertexDescriptor();
    pipelineDescriptor->setVertexDescriptor(vertexDescriptor);

    pipelineState = device->newRenderPipelineState(pipelineDescriptor, &error);
    if (!pipelineState) {
        std::cerr << "Failed to create pipeline state: " << error->localizedDescription()->utf8String() << std::endl;
        return false;
    }

    pipelineDescriptor->release();
    vertexFunction->release();
    fragmentFunction->release();

    return true;
}

// Create the vertex descriptor
MTL::VertexDescriptor* Renderer::createVertexDescriptor() {
    MTL::VertexDescriptor* vd = MTL::VertexDescriptor::alloc()->init();

    // Attribute 0: Position (float3)
    vd->attributes()->object(0)->setFormat(MTL::VertexFormatFloat3);
    vd->attributes()->object(0)->setOffset(0);
    vd->attributes()->object(0)->setBufferIndex(0);

    // Attribute 1: Color (float3)
    vd->attributes()->object(1)->setFormat(MTL::VertexFormatFloat3);
    vd->attributes()->object(1)->setOffset(12); // After position (3 floats * 4 bytes)
    vd->attributes()->object(1)->setBufferIndex(0);

    // Buffer 0 layout
    vd->layouts()->object(0)->setStride(24); // 6 floats * 4 bytes
    vd->layouts()->object(0)->setStepFunction(MTL::VertexStepFunctionPerVertex);

    return vd;
}