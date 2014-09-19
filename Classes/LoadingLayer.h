//
//  LoadingLayer.h
//  MagicDeffence
//
//  Created by xiang-chen on 14-9-4.
//
//

#ifndef __MagicDeffence__LoadingLayer__
#define __MagicDeffence__LoadingLayer__

#include <iostream>
#include "cocos2d.h"

class LoadingLayer:public cocos2d::Layer{
public:
    void update(float dt);
    virtual bool init();
    static cocos2d::Scene *scene();
    static LoadingLayer* create();
    bool initWithResources();
    int currentCount;
    int totalCount;
    void startGame(float dt);
    cocos2d::ProgressTimer* process;
    
};

#endif /* defined(__MagicDeffence__LoadingLayer__) */
