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
#include <stdio.h>


#define DropActionTag 1000

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
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    auto background = Sprite::create("bg_cell.png", Rect(0, 0, visibleSize.width, visibleSize.height));
    background->getTexture()->setTexParameters({GL_LINEAR, GL_LINEAR, GL_REPEAT,GL_REPEAT});
    background->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));
    this->addChild(background,-1);
    background->setGlobalZOrder(-1);
    
    waveCount = 1;
    lvl = 1;
    
    GameScene::addNewEnemyByLevel(1);
    
    g_rGemertricRecognizer=new GeometricRecognizer;
    g_rGemertricRecognizer->loadTemplates();
    
    auto listener1 = EventListenerTouchOneByOne::create();//创建一个触摸监听
    listener1->setSwallowTouches(true); //设置是否想下传递触摸
//    listener1->onTouchBegan = [](Touch* touch, Event* event){
//        Point location = touch->getLocation();
//        pre_point = cur_point = location;
//        return true;
//    };
    listener1->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
    listener1->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
    listener1->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener1, this);
    return true;
}




// 每波数量控制
int GameScene::hardControlForNumByLvl(int lvl){

    
    switch (lvl) {
        case 1:
            return (arc4random()%2)+2;
            break;
        case 2:
            return (arc4random()%3)+3;
            break;
        case 3:
            return (arc4random()%2)+4;
            break;
        case 4:
            return (arc4random()%2)+4;
            break;
        default:
            return 0;
            break;
    }
}

// 每单位数量层级控制
int GameScene::hardControlForCountByLvl(int lvl){
    int curCount = arc4random()%100+1;
    switch (lvl) {
        case 1:{
            if(curCount<=80){
                return 1;
            }else if(curCount<=95 && curCount>80){
                return 2;
            }else{
                return 3;
            }
        }
            break;
        case 2:{
            if(curCount<=60){
                return 1;
            }else if(curCount<=90 && curCount>60){
                return 2;
            }else{
                return 3;
            }
        }
            break;
        case 3:{
            if(curCount<=40){
                return 1;
            }else if(curCount<=70 && curCount>40){
                return 2;
            }else if(curCount<=90 && curCount>70){
                return 3;
            }else{
                return 4;
            }
        }
            break;
        case 4:{
            if(curCount>=35){
                return 1;
            }else if(curCount<=70 && curCount>35){
                return 2;
            }else if(curCount<=85 && curCount>70){
                return 3;
            }else{
                return 4;
            }
        }
            break;
        default:
            return 0;
            break;
    }
}


int GameScene::addNewEnemyByLevel(int lvl){
    
    float dropTime = 1 + ((lvl-1)/4);
    auto wSize = Director::getInstance()->getWinSize();
    int quantity = GameScene::hardControlForNumByLvl(lvl);
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
        int weight = GameScene::hardControlForCountByLvl(lvl);
        obj->setEnemyWeight(weight);
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
        GameScene::startDrop(20/dropTime+5*(weight-1), em, false);
        curWave.pushBack(obj);
        curEnWave.pushBack(em);
        
    }
    return waveCount;
}



void GameScene::startDrop(float dt,Sprite* em,bool isMoving){
    auto winsize = Director::getInstance()->getWinSize();

    FiniteTimeAction *actionMove = MoveTo::create(dt, Point(em->getPosition().x, -winsize.height+em->getContentSize().height*.5));
    FiniteTimeAction *actionMoveDone = CallFuncN::create([&](Node* node){
        for (auto sp : curWave){
            sp->removeFromParent();
        }
        auto scene = StartScene::scene();
        auto transition=TransitionFade::create(1.0f,scene);
        Director::getInstance()->replaceScene(transition);
    });

    if (isMoving) {
        Sequence *emyAction = Sequence::create(actionMove,actionMoveDone, NULL);
        emyAction->setTag(DropActionTag);
        em->runAction(emyAction);
    }else{
        DelayTime *delay = DelayTime::create(CCRANDOM_0_1()*1.5f);
        Sequence *emyAction = Sequence::create(delay,actionMove,actionMoveDone, NULL);
        emyAction->setTag(DropActionTag);
        em->runAction(emyAction);
    }
}


bool GameScene::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event){
    
    Point beginPoint = touch->getLocationInView();
    beginPoint = Director::getInstance()->convertToGL(beginPoint);
    // beginPoint 检测
    pointList.push_back(beginPoint);
    
    Point location = touch->getLocation();
    pre_point = cur_point = location;
    return true;
}



void GameScene::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event){
    
    Point nextPoint = touch->getLocationInView( );
    nextPoint = Director::getInstance()->convertToGL(nextPoint);
    // nextPoint 检测
    Point preMovePoint = touch->getPreviousLocationInView();
    preMovePoint = Director::getInstance()->convertToGL(preMovePoint);
    float distance = nextPoint.getDistance(preMovePoint);
    if (distance > 1)
    {
        int d = (int)distance;
        for (int i =0; i < d; i++ )
        {
            float distanceX = nextPoint.x - preMovePoint.x;
            float distanceY = nextPoint.y - preMovePoint.y;
            
            float percent = i / distance;
            Point newPoint;
            newPoint.x = preMovePoint.x + (distanceX * percent);
            newPoint.y = preMovePoint.y + (distanceY * percent);
            
            pointList.push_back(newPoint);
        }
    }

    
    
    Point location = touch->getLocation();
    cur_point = location;
    if((pre_point - cur_point).getLengthSq()>25){
        seg.p1=pre_point;
        seg.p2=cur_point;
        segment.push_back(seg);
        pre_point=cur_point;
    }
    Point2D p_Point2DTemp;
    p_Point2DTemp.x=location.x;
    p_Point2DTemp.y=location.y;
    //记录
    p_2dPath.push_back(p_Point2DTemp);
}

void GameScene::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event){
    
    pointList.clear();

    
    Point location = touch->getLocation();
    cur_point = location;
    if((pre_point - cur_point).getLengthSq()>25){
        seg.p1=pre_point;
        seg.p2=cur_point;
        segment.push_back(seg);
        pre_point=cur_point;
    }
    log("done");
    if (p_2dPath.size() < 1){
        return ;
    }
    RecognitionResult result = g_rGemertricRecognizer->recognize(p_2dPath);
    log("%s--%.2f",result.name.c_str(),result.score);
    p_2dPath.clear();
    if (result.score<0.70) {
        return;
    }
    size_t len = curWave.size();
    ValueVector temp_vec;
    log(" 剩余数量 :%zd ",curWave.size());
    for (int i =0; i < len; i ++) {
        auto em = curWave.at(i);         // 获取enmey数组  主要目的是获取signarr
        auto emy = curEnWave.at(i);      // 获取sprite
        auto sign = em->getSignArr().back();  // 获取signarr中最上层的一个
        
        //判断最上层标志是否与手势相符
        log("界面图片%d:用户手势%d",sign->getSignType(),this->resultTypeByName(Value(result.name)));
        if (sign->getSignType()==this->resultTypeByName(Value(result.name))) {
            log(" em->getSignArr().capacity()-BEFORE:%zd getSignArrBEFORE:%zd ",emy->getChildrenCount(),em->getSignArr().size());
            emy->removeChildByTag(sign->getTag());
            Vector<Sign*> arr = em->getSignArr();
            arr.eraseObject(sign);
            em->setSignArr(arr);
            arr.clear();
            log(" em->getSignArr().capacity():%zd getSignArr:%zd",emy->getChildrenCount(),em->getSignArr().size());
            if (emy->getChildrenCount() == 0) {               // 移除之后判断有无子精灵
//                em->removeFromParent();      // 没有则销毁该精灵
//                emy->removeFromParent();
//                curWave.eraseObject(em);
//                curEnWave.eraseObject(emy);
                temp_vec.push_back(Value(i));

            }else{
                emy->stopActionByTag(DropActionTag);
                GameScene::startDrop(10.f, emy,true);
            }
        }
        
    }
    //
    size_t curLen = len;
    for(Value val:temp_vec){
        int curIndex = val.asInt();
        curWave.at(curIndex)->removeFromParent();
        curEnWave.at(curIndex)->removeFromParent();
        curWave.erase(curIndex);
        curEnWave.erase(curIndex);
        curLen--;
        if (curLen == 0) {
            waveCount++;
            if (waveCount>=1&&waveCount<=3) {
                lvl = 1;
            }else if(waveCount>=4&&waveCount<=8){
                lvl = 2;
            }else if (waveCount>=9&&waveCount<=14){
                lvl = 3;
            }else if (waveCount>14){
                lvl = 4;
            }
            GameScene::addNewEnemyByLevel(lvl);
        }
    }
    temp_vec.clear();
}

int GameScene::resultTypeByName(Value v){

    if (v == Value("Line")) {
        return 1;
    }else if (v == Value("Tied") || v == Value("TiedLeft")){
        
        return 2;
    }else if (v == Value("Circle")|| v==Value("CircleBottom")){
        
        return 3;
    }else if (v == Value("V") || v == Value("V2")){
        
        return 4;
    }else if (v == Value("TriangleLeft") || v == Value("TriangleRight")){
        
        return 5;
    }
    return -1;

}
void GameScene::onDrawPrimitives(const Mat4 &transform, bool transformUpdated)
{
//    kmGLPushMatrix();
//    kmGLLoadMatrix(&transform);
    
    //add your primitive drawing code here
    drawLine();
}

void GameScene::draw(Renderer *renderer,const Mat4& transform,uint32_t flags){

    _customCommand.init(_globalZOrder);
    _customCommand.func = CC_CALLBACK_0(GameScene::onDrawPrimitives, this, transform, _transformUpdated);
    renderer->addCommand(&_customCommand);
    
}

void GameScene::drawLine()
{
    int tickSubCount = 10;
    int pointListKeepCount = 500;
    
    for (int i=0; i<tickSubCount ; i++)
    {
        if (pointList.size() >0)
        {
            pointList.pop_front();
        }
        else
        {
            break;
        }
    }
    while (pointList.size() > pointListKeepCount)
    {
        pointList.pop_front();
    }
    
    float max_lineWidth = 5;
    float min_lineWidth = 1;
    int   alpha_min = 10;
    int   alpha_max =  200;
    
    int  R = arc4random()%255;
    int  G = arc4random()%255;
    int  B = arc4random()%255;
    
    unsigned long pointListCount = pointList.size();
    std::list <Point>::iterator it =pointList.begin();
    
    float pointIndex = 0;
    for(;it!=pointList.end();it++)
    {
        int distanceToMiddle = fabs(pointIndex-pointListCount/2);
        float percent = 1.0-(float)distanceToMiddle/(float)(pointListCount/2.0);
        float lintWidth = min_lineWidth + max_lineWidth*percent;
        int alpha = alpha_min +alpha_max*percent;
        
        Color4B(R,G,B,alpha);
        DrawPrimitives::setPointSize(lintWidth);
        DrawPrimitives::drawPoint( *it );
        
        pointIndex++;
    }
}


