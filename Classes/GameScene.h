//
//  GameScene.h
//  MagicDeffence
//
//  Created by xiang-chen on 14-9-5.
//
//

#ifndef __MagicDeffence__GameScene__
#define __MagicDeffence__GameScene__

#include <iostream>
#include "cocos2d.h"
#include "GeometricRecognizer.h"
#include "Enemy.h"


using namespace DollarRecognizer;

class GameScene : public cocos2d::Layer{
public:
    ~GameScene();
    static cocos2d::Scene* createScene();
    virtual bool init();
    
    CREATE_FUNC(GameScene);
    virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event) override;
    virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event) override;
    void addNewEnemyByLevel(int lvl);
    void startDrop(float dt,cocos2d::Sprite* em);
    int resultTypeByName(cocos2d::Value v);
private:
    cocos2d::PhysicsWorld* m_world;
    GeometricRecognizer* g_rGemertricRecognizer;
    Path2D p_2dPath;
    cocos2d::Vector<Enemy*> curWave;
    cocos2d::Vector<cocos2d::Sprite*> curEnWave;
};


#endif /* defined(__MagicDeffence__GameScene__) */
