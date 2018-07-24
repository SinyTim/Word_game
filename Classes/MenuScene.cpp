#include "MenuScene.h"

#include "AppDelegate.h"
#include "constants.h"
#include "PlayScene.h"
#include "SettingsScene.h"



USING_NS_CC;



bool MenuScene::init() {

    if (!Scene::init()) {
        return false;
    }

    AppDelegate::createBackground(this);
    createMenu();

    return true;
}

void MenuScene::createMenu() {

    std::vector<std::pair<std::string, ccMenuCallback>> menuItemsInfo = {
        {"Play", CC_CALLBACK_1(MenuScene::menuPlayCallback, this)},
        {"Settings", CC_CALLBACK_1(MenuScene::menuSettingsCallback, this)},
        {"Exit", CC_CALLBACK_1(MenuScene::menuExitCallback, this)}
    };

    Vector<MenuItem*> menuItems;
    for (auto& itemInfo : menuItemsInfo) {
        auto menuItem = MenuItemFont::create(itemInfo.first, itemInfo.second);
        menuItem->setColor(Color3B::YELLOW);
        menuItems.pushBack(menuItem);
    }

    auto origin = Director::getInstance()->getVisibleOrigin();
    auto visibleSize = Director::getInstance()->getVisibleSize();

    auto menu = Menu::createWithArray(menuItems);
    menu->setPosition(origin + visibleSize / 2);
    menu->alignItemsVerticallyWithPadding(menuPadding);
    this->addChild(menu, 1);
}

void MenuScene::menuPlayCallback(Ref* pSender) {
    Director::getInstance()->pushScene(PlayScene::create());
}

void MenuScene::menuSettingsCallback(Ref* pSender) {
    Director::getInstance()->pushScene(SettingsScene::create());
}

void MenuScene::menuExitCallback(Ref* pSender) {
    Director::getInstance()->end();
}
