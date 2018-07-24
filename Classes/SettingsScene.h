#pragma once

#include "cocos2d.h"
#include "ui/UISlider.h"



class SettingsScene 
    : public cocos2d::Scene {

public:
    CREATE_FUNC(SettingsScene);

protected:
    bool init() override;
    void createMenu();
    void createSliderWithLabel();

    void sliderCallback(cocos2d::Ref* sender,
                        cocos2d::ui::Slider::EventType eventType);
    void menuMenuCallback(cocos2d::Ref* sender);
};
