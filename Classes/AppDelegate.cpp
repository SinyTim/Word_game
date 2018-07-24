#include "AppDelegate.h"

#include "audio/include/SimpleAudioEngine.h"
#include "constants.h"
#include "MenuScene.h"



USING_NS_CC;



static Size designResolutionSize = Size(480, 640);

static Size smallResolutionSize = Size(480, 320);
static Size mediumResolutionSize = Size(1024, 768);
static Size largeResolutionSize = Size(2048, 1536);



float AppDelegate::_fallingSpeed = 150.0f;



AppDelegate::~AppDelegate() {
    CocosDenshion::SimpleAudioEngine::end();
} 

void AppDelegate::initGLContextAttrs() {
    // set OpenGL context attributes: red,green,blue,alpha,depth,stencil,multisamplesCount
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8, 0};
    GLView::setGLContextAttrs(glContextAttrs);
}

// if you want to use the package manager to install more packages,  
// don't modify or remove this function
static int register_all_packages() {
    return 0; //flag for packages manager
}

bool AppDelegate::applicationDidFinishLaunching() {

    initOpenGL();
    initDirector();
    initMultiResolution();
    register_all_packages();
    createAndRunScene();

    return true;
}

// This function will be called when the app is inactive.
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();
    CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
    CocosDenshion::SimpleAudioEngine::getInstance()->pauseAllEffects();
}

// this function will be called when the app is active again.
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();
    CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
    CocosDenshion::SimpleAudioEngine::getInstance()->resumeAllEffects();
}

void AppDelegate::createBackground(cocos2d::Scene* scene) {

    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    auto _background = Sprite::create(backgroundImage);

    _background->setPosition(origin + visibleSize / 2);

    float scaleX = visibleSize.width / _background->getContentSize().width;
    float scaleY = visibleSize.height / _background->getContentSize().height;
    _background->setScale(scaleX, scaleY);

    scene->addChild(_background, -10);
}

void AppDelegate::setFallingSpeedPercent(int percentInt) {
    float percent = percentInt / 100.0f;
    _fallingSpeed = minFallingSpeed + percent * (maxFallingSpeed - minFallingSpeed);
}

float AppDelegate::getFallingSpeed() {
    return _fallingSpeed;
}

void AppDelegate::initOpenGL() {

    auto director = Director::getInstance();
    auto glView = director->getOpenGLView();

    if (!glView) {
        glView = GLViewImpl::createWithRect(
            "WordGame",
            Rect(0, 0, designResolutionSize.width, designResolutionSize.height)
        );
        director->setOpenGLView(glView);
    }
}

void AppDelegate::initDirector() {
    auto director = Director::getInstance();
    director->setAnimationInterval(1.0f / 60);
    //director->setDisplayStats(true);
}

void AppDelegate::initMultiResolution() {

    auto director = Director::getInstance();
    auto glView = director->getOpenGLView();

    glView->setDesignResolutionSize(
        designResolutionSize.width,
        designResolutionSize.height,
        ResolutionPolicy::NO_BORDER
    );

    Size frameSize = glView->getFrameSize();
    float scaleFactor = 1.0f;

    if (frameSize.height > mediumResolutionSize.height) {
        scaleFactor = MIN(largeResolutionSize.height / designResolutionSize.height,
                          largeResolutionSize.width / designResolutionSize.width);

    } else if (frameSize.height > smallResolutionSize.height) {
        scaleFactor = MIN(mediumResolutionSize.height / designResolutionSize.height,
                          mediumResolutionSize.width / designResolutionSize.width);

    } else {
        scaleFactor = MIN(smallResolutionSize.height / designResolutionSize.height,
                          smallResolutionSize.width / designResolutionSize.width);
    }

    director->setContentScaleFactor(scaleFactor);
}

void AppDelegate::createAndRunScene() {

    auto audioEngine = CocosDenshion::SimpleAudioEngine::getInstance();
    audioEngine->playBackgroundMusic(backgroundMusic.c_str(), true);

    auto director = Director::getInstance();
    auto menuScene = MenuScene::create();
    director->runWithScene(menuScene);
}
