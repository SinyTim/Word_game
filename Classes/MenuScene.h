#pragma once

#include "cocos2d.h"



class MenuScene 
    : public cocos2d::Scene {

public:
    CREATE_FUNC(MenuScene);

protected:
    bool init() override;
    void createMenu();

    void menuPlayCallback(cocos2d::Ref* pSender);
    void menuSettingsCallback(cocos2d::Ref* pSender);
    void menuExitCallback(cocos2d::Ref* pSender);
};
