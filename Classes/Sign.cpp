//
//  Sign.cpp
//  MagicDeffence
//
//  Created by xiang-chen on 9/18/14.
//
//

#include "Sign.h"
USING_NS_CC;

Sprite* Sign::createSprite(cocos2d::Value weight, cocos2d::Value signRank){
    
    int curType = arc4random()%kEnumTypeCount+1;
    Sprite* sp = Sprite::create(StringUtils::format("sign_%d%d.png",curType,weight.asInt()));
    log("cur泰普:%d",curType);
    this->setSignType(curType);
    this->setSignWeight(weight);
    this->setSignRank(signRank);
    return sp;
    
}

bool Sign::init(){
    
    return true;
}

bool Sign::initWithParams(Value weight, Value signRank){
    
    
    return true;

}