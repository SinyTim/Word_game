#include "SettingsScene.h"

#include "AppDelegate.h"
#include "constants.h"
#include "MenuScene.h"



USING_NS_CC;



bool SettingsScene::init() {

    if (!Scene::init()) {
        return false;
    }

    AppDelegate::createBackground(this);
    createMenu();
    createSliderWithLabel();

    return true;
}

void SettingsScene::createMenu() {

    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    auto menuItem = MenuItemImage::create(
        menuButtonImage, menuButtonImage,
        CC_CALLBACK_1(SettingsScene::menuMenuCallback, this)
    );
    menuItem->setPosition(origin + menuItem->getContentSize() / 2);

    auto menu = Menu::create(menuItem, nullptr);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
}

void SettingsScene::createSliderWithLabel() {

    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    auto label = Label::create("Falling speed: ", fontFile, fontSize);
    label->setTextColor(Color4B::YELLOW);
    auto halfLabelSizes = label->getContentSize() / 2;
    label->setPosition(
        origin + Vec2(halfLabelSizes.width + 50, visibleSize.height / 2 + 60)
    );
    this->addChild(label);


    auto slider = ui::Slider::create();

    slider->loadBarTexture("slider/sliderBar.png");
    slider->loadProgressBarTexture("slider/sliderProgressBar.png");
    slider->loadSlidBallTextureNormal("slider/ballNormal.png");
    slider->loadSlidBallTexturePressed("slider/ballPressed.png");
    slider->loadSlidBallTextureDisabled("slider/ballDisabled.png");

    auto labelBox = label->getBoundingBox();
    auto halfSliderSize = slider->getContentSize() / 2;
    slider->setPosition(Vec2(
        labelBox.origin.x + labelBox.size.width + halfSliderSize.width + 20.0f, 
        label->getPosition().y
    ));

    slider->addEventListener(CC_CALLBACK_2(SettingsScene::sliderCallback, this));

    int percent = (AppDelegate::getFallingSpeed() - minFallingSpeed) * 100.0f
                  / (maxFallingSpeed - minFallingSpeed);
    slider->setPercent(percent);

    this->addChild(slider);
}

void SettingsScene::sliderCallback(Ref* sender, 
                                   ui::Slider::EventType eventType) {

    switch (eventType) {
        case ui::Slider::EventType::ON_SLIDEBALL_UP:
            auto slider = dynamic_cast<ui::Slider*>(sender);
            AppDelegate::setFallingSpeedPercent(slider->getPercent());
            break;
    }
}

void SettingsScene::menuMenuCallback(Ref* sender) {
    Director::getInstance()->popScene();
}
