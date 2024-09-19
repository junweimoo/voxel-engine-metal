//
// Created by Jun Wei Moo on 16/9/24.
//

#ifndef VOXELAPP_H
#define VOXELAPP_H
#include "Renderer.h"
#include "World.h"

class VoxelApp {
    public:
        VoxelApp();
        ~VoxelApp();

        void run();

    private:
        NS::Application* pSharedApplication;
};

class VoxelViewDelegate : public MTK::ViewDelegate {
    public:
        VoxelViewDelegate(Renderer* renderer, Camera* camera, World* world);
        virtual ~VoxelViewDelegate() override;

        virtual void drawInMTKView( MTK::View* pView ) override;

    private:
        World* world;
        Camera* camera;
        Renderer* _pRenderer;
};

class VoxelAppDelegate : public NS::ApplicationDelegate {
    public:
        ~VoxelAppDelegate();

        NS::Menu* createMenuBar();

        virtual void applicationWillFinishLaunching( NS::Notification* pNotification ) override;
        virtual void applicationDidFinishLaunching( NS::Notification* pNotification ) override;
        virtual bool applicationShouldTerminateAfterLastWindowClosed( NS::Application* pSender ) override;

    private:
        Renderer* renderer;
        Camera* camera;
        World* world;

        NS::Window* _pWindow;
        MTL::Device* _pDevice;
        MTK::View* _pMtkView;
        VoxelViewDelegate* _pViewDelegate = nullptr;
};

#endif //VOXELAPP_H