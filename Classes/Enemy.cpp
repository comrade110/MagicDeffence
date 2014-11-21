//
//  Enemy.cpp
//  MagicDeffence
//
//  Created by xiang-chen on 14-9-5.
//
//

#include "Enemy.h"
#include "GameScene.h"
USING_NS_CC;

Enemy::Enemy(){
}

Enemy::~Enemy(){
}

//Enemy* Enemy::createEnemy(){
//    Enemy *enemy = new Enemy;
//    if (enemy && enemy->init()) {
//        enemy->autorelease();
//        return enemy;
//    }else{
//        CC_SAFE_DELETE(enemy);
//        enemy = NULL;
//        return NULL;
//    }
//    
//
//}

bool Enemy::init(){
//    
//    bool bRet = false;
//    do{
//        Sprite *enemy = Sprite::create("circle.png");
//        enemy->setTag(9);
//        log("diaodiao");
//        this->setContentSize(enemy->getContentSize());
//        this->addChild(enemy);
//        FiniteTimeAction* r = RotateBy::create(2.f, 360.f);
//        enemy->runAction(RepeatForever::create((ActionInterval*)r));
//        Enemy::startDrop(4.f);
//        signNum = 1;
//        scheduleUpdate();
//        
//        
//        for (int i=0; i<signNum; i++) {
//            //随机数种子
//            auto signSprite = Sign::createSprite(Value(1),Value(1));
//            signSprite->setPosition(Point(enemy->getContentSize().width/2,enemy->getContentSize().height/2));
//            enemy->addChild(signSprite, i+999);
//        }
//        
//        bRet = true;
//    }while (0);
    return true;
}

Sprite* Enemy::createEnemy(){
    Sprite *enemy = Sprite::create("circle.png");
    enemy->setTag(9);
    log("diaodiao");
//    this->addChild(enemy);
    FiniteTimeAction* r = RotateBy::create(2.f, 360.f);
    enemy->runAction(RepeatForever::create((ActionInterval*)r));
    signNum = 2;
    scheduleUpdate();
    
    
    for (int i=1; i<=signNum; i++) {
        //随机数种子
        Sign *sign = Sign::create();
        sign->setTag(i);
        log("shaW %.1f",sign->getContentSize().width);
        log("shab %.1f",sign->getContentSize().height);
        Enemy::addSigns(sign,enemy,i);
    }
    log("singarr count:%zd",this->signArr.capacity());
    return enemy;
}

void Enemy::addSigns(Sign* sn,Sprite* enemy,int lvl){
    Sprite* sign = sn->createSprite(Value(lvl), Value(1));
    sign->setTag(sn->getTag());
    log("sha2 %.1f",sn->getContentSize().width);
    log("sha1 %.1f",sn->getContentSize().height);
    sign->setPosition(sign->getContentSize().width/2, sign->getContentSize().height/2);
    enemy->addChild(sign);
    this->signArr.pushBack(sn);
}


void matchingSigns(Value str){

    
}


void Enemy::update(float dt){
    
    
}