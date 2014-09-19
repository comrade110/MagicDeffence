//
//  StartScene.cpp
//  MagicDeffence
//
//  Created by xiang-chen on 14-9-4.
//
//

#include "StartScene.h"
#include "LoadingLayer.h"

USING_NS_CC;

StartScene::StartScene()
{
}

StartScene::~StartScene()
{
}

Scene* StartScene::scene(){
    Scene *scene = NULL;
    do {
        scene = Scene::create();
        CC_BREAK_IF(!scene);
        auto layer = StartScene::create();
        CC_BREAK_IF(!layer);
        scene->addChild(layer);
    }while (0);
    return scene;
}

bool StartScene::init()
{
    bool retBool = false;
    do {
        CC_BREAK_IF(!Layer::init());
        auto wSize = Director::getInstance()->getWinSize();
        auto origin = Director::getInstance()->getVisibleOrigin();
        MenuItemFont *start = MenuItemFont::create("Start game",  [&](Ref* sender)
                                                  {
                                                      Director::getInstance()->replaceScene(LoadingLayer::scene());
                                                      log("Start game Callback called!");
                                                  }
                                                  );
        start->setPosition(origin.x + wSize.width/2, origin.y+wSize.height/2);
        start->setFontSizeObj(50);
        
        
        MenuItemFont *share = MenuItemFont::create("Share Friends",  [&](Ref* sender)
                                                  {
                                                      log("Share Friends Callback called!");
                                                  }
                                                  );
        share->setPosition(start->getPositionX(), start->getPositionY()-50);
        share->setFontSizeObj(30);
        
        Menu *menu = Menu::create(start,share, NULL);
        menu->setPosition(Vec2::ZERO);
        this->addChild(menu);
        retBool = true;
        
    }while (0);
    
    return retBool;
}

void StartScene::startGame(){

}