//
//  LoadingLayer.cpp
//  MagicDeffence
//
//  Created by xiang-chen on 14-9-4.
//
//

#include "LoadingLayer.h"
#include "GameScene.h"
USING_NS_CC;

#define ToTalResCount 100

Scene* LoadingLayer::scene(){
    do {
        auto layer = LoadingLayer::create();
        CC_BREAK_IF(!layer);
        Scene *scene = Scene::create();
        scene->addChild(layer);
        return scene;
    }while(0);
    return NULL;
}


LoadingLayer* LoadingLayer::create(){

    auto layer = new LoadingLayer;
    if (layer && layer->initWithResources()) {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    return NULL;
}


bool LoadingLayer::init(){

    bool bRet = false;
    do {
        CC_BREAK_IF(!CCLayer::init());
        
        bRet = true;
    }while(0);
    
    return bRet;
}

bool LoadingLayer::initWithResources(){

    bool bRet = false;
    do {
        CC_BREAK_IF(!LoadingLayer::init());
        auto winsize = Director::getInstance()->getWinSize();
        auto label = Label::create();
        label->setSystemFontSize(30);
        label->setPosition(winsize.width/2, winsize.height/2);
        label->setTag(123);
        this->addChild(label);
        currentCount = 2;
        totalCount = ToTalResCount;
        bRet = true;
        scheduleUpdate();
    }while(0);
    
    return bRet;
}

void LoadingLayer::startGame(float dt){
    Director::getInstance()->replaceScene(GameScene::createScene());
    log("start game");
}

void LoadingLayer::update(float dt){
    currentCount++;
    float percent = (float)currentCount/(float)totalCount*100;
    Label* label = (Label*)getChildByTag(123);
    std::string curStr = StringUtils::format("Loading(%d%%)...",(int)percent);
    label->setString(curStr);
    if (currentCount == totalCount) {
        label->setString("Load finished");
        unscheduleUpdate();
        scheduleOnce(schedule_selector(LoadingLayer::startGame), 0.3f);
    }

}
