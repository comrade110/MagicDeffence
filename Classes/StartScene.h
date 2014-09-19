//
//  StartScene.h
//  MagicDeffence
//
//  Created by xiang-chen on 14-9-4.
//
//

#ifndef __MagicDeffence__StartScene__
#define __MagicDeffence__StartScene__

#include <iostream>
#include "cocos2d.h"

class StartScene:public cocos2d::Layer{
public:
    StartScene();
    ~StartScene();
    static cocos2d::Scene * scene();
    virtual bool init();
    CREATE_FUNC(StartScene);
    void startGame();
};

#endif /* defined(__MagicDeffence__StartScene__) */
