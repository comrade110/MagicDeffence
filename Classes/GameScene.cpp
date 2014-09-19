//
//  GameScene.cpp
//  MagicDeffence
//
//  Created by xiang-chen on 14-9-5.
//
//

#include "GameScene.h"
#include "GeometricRecognizer.h"
#include "StartScene.h"
USING_NS_CC;


GameScene::~GameScene(){
    CC_SAFE_DELETE(g_rGemertricRecognizer);
}

Scene* GameScene::createScene(){
    
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
    
}

bool GameScene::init(){

    if ( !Layer::init() )
    {
        return false;
    }
    auto background = Sprite::create("bg.png");
    background->setPosition(Vec2::ZERO);
    background->setAnchorPoint(Vec2::ZERO);
    
    this->addChild(background);
    GameScene::addNewEnemyByLevel(0);
    
    g_rGemertricRecognizer=new GeometricRecognizer;
    g_rGemertricRecognizer->loadTemplates();
    
    
    auto listener1 = EventListenerTouchOneByOne::create();//创建一个触摸监听
    listener1->setSwallowTouches(true); //设置是否想下传递触摸
    listener1->onTouchBegan = [](Touch* touch, Event* event){
        return true;
    };
    listener1->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
    listener1->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener1, this);
    return true;
}

void GameScene::addNewEnemyByLevel(int lvl){
    
    auto wSize = Director::getInstance()->getWinSize();
    int quantity = 4;
    int start = 0;
    int end = 8;
    int total = abs(end - start);
    if (quantity >total) {
        CCLOG("随机数错误");
    }
    int sequence[total];  //存放随机数的数组
    int output[quantity]; //最终生成的不重复一系列随机数
    
    //将sequence 初始化
    for (int i = 0; i < total; i++) {
        sequence[i] = start+i;
    }
    //随机数种子
    timeval psv;
    gettimeofday(&psv, NULL);
    unsigned seed = (unsigned)psv.tv_sec*1000 + (unsigned)psv.tv_usec/1000;
    srand(seed);
    
    for (int i = 0; i < quantity; i++) {
        Enemy * obj = Enemy::create();
        log("zhongzi:%d",(end-start+1)+start);
        int num = CCRANDOM_0_1()*end;//在指定范围下产生随机数
        output[i] = sequence[num];//将产生的随机数存储
        sequence[num] = sequence[end-1];//将最后个下标的值填充到随机产生的下标中
        end--;//在指定范围 向前移
        
        Sprite *em = obj->createEnemy();
        auto width = em->getContentSize().width;
        float f = output[i]*width+width*.5f;
        em->setPosition(f, wSize.height+80);
        log("--%d--%.2f-  %.2f-",output[i],f,width);
        this->addChild(em,i+100);
        GameScene::startDrop(10.f, em);
        curWave.pushBack(obj);
        curEnWave.pushBack(em);
        
    }
}



void GameScene::startDrop(float dt,Sprite* em){
    auto winsize = Director::getInstance()->getWinSize();
    DelayTime *delay = DelayTime::create(CCRANDOM_0_1()*1.5f);
    FiniteTimeAction *actionMove = MoveTo::create(dt, Point(em->getPosition().x, -winsize.height+em->getContentSize().height*.5));
    FiniteTimeAction *actionMoveDone = CallFuncN::create([&](Node* node){
        for (auto sp : curWave){
            sp->removeFromParent();
        }
        auto scene = StartScene::scene();
        auto transition=TransitionFade::create(1.0f,scene);
        Director::getInstance()->replaceScene(transition);
    });
    em->runAction(Sequence::create(delay,actionMove,actionMoveDone, NULL));
}

void GameScene::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event){
    Point location = touch->getLocationInView();
    Point2D p_Point2DTemp;
    p_Point2DTemp.x=location.x;
    p_Point2DTemp.y=location.y;
    //记录
    p_2dPath.push_back(p_Point2DTemp);
}

void GameScene::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event){
    log("done");
    if (p_2dPath.size() < 1){
        return ;
    }
    RecognitionResult result = g_rGemertricRecognizer->recognize(p_2dPath);
    log("%s--%.2f",result.name.c_str(),result.score);
    if (result.score<0.7) {
        return;
    }
    size_t len = curWave.size();
    
    for (size_t i =0; i < len; i ++) {
        auto em = curWave.at(i);         // 获取enmey数组  主要目的是获取signarr
        
        log("curi:%zu signArr.size:%zd ",i,em->getSignArr().size());
        auto emy = curEnWave.at(i);      // 获取sprite
        auto sign = em->getSignArr().back();  // 获取signarr中最上层的一个
        
        //判断最上层标志是否与手势相符
        
        log("界面图片%d:用户手势%d",sign->getSignType(),this->resultTypeByName(Value(result.name)));
        if (sign->getSignType()==this->resultTypeByName(Value(result.name))) {
            auto lastObj = emy->getChildren().back();      // 相等的话 直接获取sprite中子类最新一个精灵
            lastObj->removeFromParent();                   // 移除该精灵
            if (em->getChildrenCount()==0) {               // 移除之后判断有无子精灵
                emy->removeFromParent();      // 没有则销毁该精灵
            }
        }
        
    }

}

int GameScene::resultTypeByName(Value v){

    if (v == Value("Line")) {
        return 1;
    }else if (v == Value("Tied")){
        
        return 2;
    }else if (v == Value("Circle")){
        
        return 3;
    }else if (v == Value("Sharp")){
        
        return 4;
    }else if (v == Value("Triangle")){
        
        return 5;
    }
    return -1;

}


