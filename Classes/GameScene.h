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
struct _segment{
    cocos2d::Point p1;
    cocos2d::Point p2;
};

using namespace DollarRecognizer;

class GameScene : public cocos2d::Layer{
public:
    ~GameScene();
    static cocos2d::Scene* createScene();
    virtual bool init();
    
    CREATE_FUNC(GameScene);
    virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event) override;
    virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event) override;
    virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event) override;
    void addNewEnemyByLevel(int lvl);
    void startDrop(float dt,cocos2d::Sprite* em);
    int resultTypeByName(cocos2d::Value v);
    virtual void draw(cocos2d::Renderer *renderer,const cocos2d::Mat4& transform,uint32_t flags) override;
    void drawLine();
    std::list<cocos2d::Point> pointList;

private:
    cocos2d::PhysicsWorld* m_world;
    GeometricRecognizer* g_rGemertricRecognizer;
    Path2D p_2dPath;
    cocos2d::Vector<Enemy*> curWave;
    cocos2d::Vector<cocos2d::Sprite*> curEnWave;
    
    cocos2d::Point pre_point;
    cocos2d::Point cur_point;
    _segment seg;
    std::vector<_segment> segment;
};


#endif /* defined(__MagicDeffence__GameScene__) */
