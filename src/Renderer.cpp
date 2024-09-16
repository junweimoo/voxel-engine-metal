//
// Created by Jun Wei Moo on 16/9/24.
//

#include "Renderer.h"

Renderer::Renderer(MTL::Device *pDevice): _pDevice(pDevice->retain())  {
    _pCommandQueue = _pDevice->newCommandQueue();
}

Renderer::~Renderer() {

}

void Renderer::draw(MTK::View* pView) {
    NS::AutoreleasePool* pPool = NS::AutoreleasePool::alloc()->init();

    MTL::CommandBuffer* pCmd = _pCommandQueue->commandBuffer();
    MTL::RenderPassDescriptor* pRpd = pView->currentRenderPassDescriptor();
    MTL::RenderCommandEncoder* pEnc = pCmd->renderCommandEncoder( pRpd );
    pEnc->endEncoding();
    pCmd->presentDrawable( pView->currentDrawable() );
    pCmd->commit();

    pPool->release();
}