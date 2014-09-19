//
//  Sign.h
//  MagicDeffence
//
//  Created by xiang-chen on 9/18/14.
//
//

#ifndef __MagicDeffence__Sign__
#define __MagicDeffence__Sign__

#include <stdio.h>
#include "cocos2d.h"

#define kEnumTypeCount 5

class Sign:public cocos2d::Sprite{
public:
    
    virtual bool init();
    Sprite* createSprite(cocos2d::Value weight, cocos2d::Value signRank);
    bool initWithParams(cocos2d::Value weight, cocos2d::Value signRank);
    CC_SYNTHESIZE(int, signType, SignType);
    CC_SYNTHESIZE(cocos2d::Value, signWeight, SignWeight);
    CC_SYNTHESIZE(cocos2d::Value, signRank, SignRank);
    CREATE_FUNC(Sign);
};
#endif /* defined(__MagicDeffence__Sign__) */
