//
//  Enemy.h
//  MagicDeffence
//
//  Created by xiang-chen on 14-9-5.
//
//

#ifndef __MagicDeffence__Enemy__
#define __MagicDeffence__Enemy__

#include <iostream>
#include "cocos2d.h"
#include "Sign.h"


enum kEnumType{
    kEnumTypeLine,
    kEnumTypeTied,
    kEnumTypeCircle,
    kEnumTypeSharp,
    kEnumTypeTriangle,
} ;


class Enemy:public cocos2d::Sprite{
public:
    Enemy();
    ~Enemy();
    CREATE_FUNC(Enemy);
    virtual bool init();
    cocos2d::Sprite* createEnemy();
    CC_SYNTHESIZE(int, enemyType, EnemyType);
    CC_SYNTHESIZE(int, signNum, SignNum);
    CC_SYNTHESIZE(int, enemyWeight, EnemyWeight);
    CC_SYNTHESIZE(int, dropSpeed, DropSpeed);
    void update(float dt) override;
    int getRandNum();
    void matchingSigns(cocos2d::Value str);
    void addSigns(Sign* sn,Sprite* enemy,int lvl);
    CC_SYNTHESIZE(cocos2d::Vector<Sign*>,signArr,SignArr);
private:
};


#endif /* defined(__MagicDeffence__Enemy__) */
