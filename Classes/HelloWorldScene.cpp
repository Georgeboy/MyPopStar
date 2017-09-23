#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "PopSprite.h"
USING_NS_CC;

Scene* HelloWorld::createScene()
{
//    auto scene = Scene::create();
//    auto layer = HelloWorld::create();
//    scene -> addChild(layer);
//    return scene;
    return HelloWorld::create();
}

void  HelloWorld::autoCreatePopSprite(cocos2d::Size size){
    //加入随机种子
    srand((unsigned)time(NULL));
    
    //求出每个pop的高度和宽度
    int lon = (size.width - 20)/10;
    for (int j = 0; j < 10; j++) {
        for (int i = 0; i < 10; i++) {
            int maxX = 5;
            int minX = 0;
            int rangeX = maxX - minX;
            int actualX = (rand()%rangeX)+minX;
            PopSprite *pop = PopSprite::createPopSprite(-1, lon,lon ,lon*j+10, lon*i + 10 + size.height/6.0);
            pop->setPOPX(j);
            pop->setPOPY(i);
            pop->setNumber(actualX);
           this-> addChild(pop,0);
            popStarSprite[j][i] = pop;
        }
    }
}

bool HelloWorld::onTouchBegan(cocos2d::Touch*touch,cocos2d::Event*pevent){
    //初始化
    popsArr = cocos2d::__Array::create();
    //获取触摸的X值和Y值
    Point touchPO = touch->getLocation();
    auto visibleSize = Director::getInstance()->getVisibleSize();
    PopSprite *pops = getPopStarSprite(visibleSize, touchPO);
    if (pops != NULL) {
        //点击的时候检测
        popsArr = checkPopUDLR(pops);
        if (popsArr->count() >= 2) {
            checkPopISNEW(popsArr);
        }
    }
     return true;
}

void HelloWorld::checkPopISNEW(cocos2d::__Array*arrold){
    //获取到的新数据
    cocos2d::__Array *arrnew = cocos2d::__Array::create();
    for (int i = 0; i < arrold->count(); i++) {
        PopSprite *pop = (PopSprite*)arrold->getObjectAtIndex(i);
        cocos2d::__Array *arrnews =  checkPopUDLR(pop);
        for (int j = 0; j < arrnews->count(); j++) {
            bool isSave = false;
            PopSprite *popnew = (PopSprite*)arrnews->getObjectAtIndex(j);
            for (int k = 0; k < popsArr->count(); k++) {
                PopSprite *popOld = (PopSprite*)popsArr->getObjectAtIndex(k);
                if ((popnew->getPOPY() == popOld->getPOPY()) &&(popnew->getPOPX() == popOld->getPOPX()) ) {
                    isSave = true;
                    break;
                }
            }
            if (!isSave) {
                arrnew -> addObject(popnew);
            }
        }

    }
    
    if (arrnew -> count() > 0) {
        for (int f= 0; f < arrnew->count(); f++) {
            popsArr->addObject(arrnew->getObjectAtIndex(f));
        }
        checkPopISNEW(popsArr);
    }else{
        //清空数据
        for (int s = 0; s< popsArr->count(); s++) {
            PopSprite *sp = (PopSprite*)popsArr->getObjectAtIndex(s);
            sp->setNumber(-1);
        }
        
        //填充空白区
        reDiessPopStar();
    }
}

//让空白区域被上面填充
void HelloWorld::reDiessPopStar(){
    for (int x = 0; x < 10; x++) {
        reDiessPopStarRun(x);
    }
    //判断完成上下移动，是否需要左右移动
    reDiessPopStarRT();
    reGameOver();
}

void HelloWorld:: reDiessPopStarRT(){
    for (int x= 0; x < 10 ; x++) {
        //检测出每列的空格数
        int number = 0;
        for (int k = 0; k < 10; k++) {
            if (popStarSprite[x][k]->getNumber() == -1) {
                number++;
            }
        }
        
        if (number == 10) {
            for (int z = 0; z < 10; z++) {
                for (int s = x;s < 9; s++) {
                    popStarSprite[s][z]->setNumber(popStarSprite[s+1][z]->getNumber());
                    popStarSprite[s+1][z]->setNumber(-1);
                }
            }
        }    }
}

//游戏是否继续
bool HelloWorld::reGameOver(){
    bool isGameOver = true;
    for (int j= 0; j < 10; j++) {
        for (int i = 0; i < 10; i++) {
            if (checkPopUDLR(popStarSprite[j][i])->count() > 0 && popStarSprite[j][i] -> getNumber() != -1) {
                isGameOver = false;
                break;
            }
        }
        if (isGameOver == false) {
            break;
        }
    }
    if (isGameOver ) {
        Director::getInstance()->replaceScene(TransitionFade::create(1, HelloWorld::create()));
    }else{
        //游戏模式
    }
    
    return isGameOver;
}
void HelloWorld::reDiessPopStarRun(int x){
    //检测出每列的空格数
    int number = 0;
    for (int k = 0; k< 10;k++){
        if (popStarSprite[x][k] ->getNumber() == -1) {
            number++;
        }
    }
    
    
    if (number > 0) {
        for (int y = 0; y < 10; y++) {
            //判断是否继续回调自己
            if (popStarSprite[x][y]->getNumber() == -1) {
                if (10-popStarSprite[x][y]->getPOPY() > number) {
                    for (int s = y; s < 10; s++) {
                        if (s + 1 == 10) {
                            popStarSprite[x][s] -> setNumber(-1);
                        }else{
                            popStarSprite[x][s] ->setNumber(popStarSprite[x][s+1]->getNumber());
                        }
                    }
                    reDiessPopStarRun(x);
                }else{
                    break;
                }
            }
        }
    }
}
cocos2d:: __Array *HelloWorld::checkPopUDLR(PopSprite*pop){
    cocos2d:: __Array *arr = cocos2d::__Array::create();
    bool isDoublePop = false;
        //判断点的位置往上的相同数
    int up = pop ->getPOPY();
    for (int yu = up + 1; yu<10; yu++) {
        if (popStarSprite[pop->getPOPX()][yu]->getNumber() == popStarSprite[pop->getPOPX()][up]->getNumber())
        {
            arr->addObject(popStarSprite[pop->getPOPX()][yu]);
//            popStarSprite[pop->getPOPX()][yu] ->setNumber(-1);
            isDoublePop = true;
        }else{
            break;
        }
    }
    
    //判断点的位置往下的相同数
    int ud = pop ->getPOPY();
    for (int yd = ud - 1; yd >= 0; yd--) {
        if (popStarSprite[pop->getPOPX()][yd]->getNumber() == popStarSprite[pop->getPOPX()][ud]->getNumber())
        {
            arr->addObject(popStarSprite[pop->getPOPX()][yd]);
//            popStarSprite[pop->getPOPX()][yd] ->setNumber(-1);
            isDoublePop = true;
        }else{
            break;
        }
    }
    
    //判断点的位置往右的相同数
    int ur = pop ->getPOPX();
    for (int xr = ur + 1; xr < 10; xr++) {
        if (popStarSprite[xr][pop->getPOPY()]->getNumber() == popStarSprite[ur][pop->getPOPY()]->getNumber())
        {
            arr->addObject(popStarSprite[xr][pop->getPOPY()]);
//            popStarSprite[xr][pop->getPOPY()] ->setNumber(-1);
            isDoublePop = true;
        }else{
            break;
        }
    }

    //判断点的位置往左的相同数
    int ul = pop ->getPOPX();
    for (int xl = ul - 1; xl >=0; xl--) {
        if (popStarSprite[xl][pop->getPOPY()]->getNumber() == popStarSprite[ul][pop->getPOPY()]->getNumber())
        {
            arr->addObject(popStarSprite[xl][pop->getPOPY()]);
//            popStarSprite[xl][pop->getPOPY()] ->setNumber(-1);
            isDoublePop = true;
        }else{
            break;
        }
    }

    if (isDoublePop) {
        arr->addObject(popStarSprite[pop->getPOPX()][pop->getPOPY()]);
    }
    return arr;
}

PopSprite *  HelloWorld::getPopStarSprite(cocos2d::Size size,cocos2d::Point touch){
    int lon = (size.width -20)/10;
    float x = (touch.x - 10)/lon;
    float y = ( touch.y - size.height/6.0 - 10)/lon;
    if (x < 10 && y< 10 && x>= 0&& y>=0) {
        int x1 = (touch.x - 10)/lon;
        int y1 = ( touch.y - size.height/6.0 -10)/lon;
        log("%i,%i",x1,y1);
        return popStarSprite[x1][y1];
    }else{
        return nullptr;
    }
}
// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }
    
    auto layerColorBG = cocos2d::LayerColor::create(Color4B(188, 170, 160, 255));
    this->addChild(layerColorBG,0);
    auto visibleSize = Director::getInstance()->getVisibleSize();
    autoCreatePopSprite(visibleSize);
    //设置监听
    auto touchLisenter = EventListenerTouchOneByOne::create();
    touchLisenter->setSwallowTouches(true);
    
    touchLisenter->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchLisenter, this);
//    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    //创建游戏背景
    
    return true;
}
//
//void HelloWorld::menuCloseCallback(Ref* pSender)
//{
//    //Close the cocos2d-x game scene and quit the application
//    Director::getInstance()->end();
//
//    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//    exit(0);
//#endif
//    
//    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/
//    
//    //EventCustom customEndEvent("game_scene_close_event");
//    //_eventDispatcher->dispatchEvent(&customEndEvent);
//    
//    
//}
