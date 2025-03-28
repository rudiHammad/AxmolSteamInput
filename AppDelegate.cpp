#include "AppDelegate.h"
#include "_testScenes/inputScene.h"


#define USE_AUDIO_ENGINE 1

#if USE_AUDIO_ENGINE
#    include "audio/AudioEngine.h"
#endif

using namespace ax;


int resolutionScale = 2;
static ax::Size designResolutionSize = ax::Size(640, 360);

AppDelegate::AppDelegate() {}

AppDelegate::~AppDelegate() {}

// if you want a different context, modify the value of glContextAttrs
// it will affect all platforms
void AppDelegate::initGLContextAttrs()
{
    // set OpenGL context attributes: red,green,blue,alpha,depth,stencil,multisamplesCount
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8, 0};
    // since axmol-2.2 vsync was enabled in engine by default
    // glContextAttrs.vsync = false;

    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    auto director = Director::getInstance();
    auto glView   = director->getGLView();
    if (!glView)
    {
#if (AX_TARGET_PLATFORM == AX_PLATFORM_WIN32) || (AX_TARGET_PLATFORM == AX_PLATFORM_MAC) || \
    (AX_TARGET_PLATFORM == AX_PLATFORM_LINUX)
        glView = GLViewImpl::createWithRect(
            "core", ax::Rect(0, 0, designResolutionSize.width * resolutionScale, designResolutionSize.height * resolutionScale));

#else
        glView = GLViewImpl::create("core");
#endif
        director->setGLView(glView);
    }

    // turn on display FPS
    director->setStatsDisplay(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0f / 60);

    // Set the design resolution
    glView->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height,
                                    ResolutionPolicy::SHOW_ALL);

    ///////////////////////////////
    // initialize steam api here //
    ///////////////////////////////

    // 1. initialize Steam API 
    if (!SteamAPI_Init())
    {
        AXLOG(">>> Failed to initialize SteamAPI. Ensure Steam app is launched and that 'steam_appid.txt' is present in \n"
        "the output directory. For instance axmolProject/build/bin/axmolProject/Debug (or /Release)");
        return false;
    }
    else {  AXLOG(">>> SteamAPI initialized successfully");  }

    // 2. Initialize Steam Input
    if(SteamInput())
    {
        SteamInput()->Init(true);
        AXLOG(">>> SteamInput initialized successfully");
    }
    else {  AXLOG(">>> Failed to initialize SteamInput");    }



    auto scene = utils::createInstance<InputScene>();                         


    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. Note, when receiving a phone call it is invoked.
void AppDelegate::applicationDidEnterBackground()
{
    Director::getInstance()->stopAnimation();

#if USE_AUDIO_ENGINE
    AudioEngine::pauseAll();
#endif
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    Director::getInstance()->startAnimation();

#if USE_AUDIO_ENGINE
    AudioEngine::resumeAll();
#endif
}
