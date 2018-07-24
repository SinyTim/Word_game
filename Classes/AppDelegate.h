#pragma once

#include "cocos2d.h"



class AppDelegate 
    : private cocos2d::Application {

public:
    AppDelegate() = default;
    virtual ~AppDelegate();

    void initGLContextAttrs() override;

    /**
    @brief    Implement Director and Scene init code here.
    @return true    Initialize success, app continue.
    @return false   Initialize failed, app terminate.
    */
    bool applicationDidFinishLaunching() override;

    /**
    @brief  Called when the application moves to the background
    @param  the pointer of the application
    */
    void applicationDidEnterBackground() override;

    /**
    @brief  Called when the application reenters the foreground
    @param  the pointer of the application
    */
    void applicationWillEnterForeground() override;

    static void createBackground(cocos2d::Scene* scene);

    static void setFallingSpeedPercent(int percent);
    static float getFallingSpeed();

private:
    void initOpenGL();
    void initDirector();
    void initMultiResolution();
    void createAndRunScene();


private:
    static float _fallingSpeed;
};
