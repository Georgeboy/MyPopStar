#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "PopSprite.h"
class HelloWorld : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
//   void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
    
    void autoCreatePopSprite(cocos2d::Size size);
    //监听手势识别
    virtual bool onTouchBegan(cocos2d::Touch*touch,cocos2d::Event*pevent);
    

    
private:
    PopSprite *popStarSprite[10][10];
    //点击得到POP对象
    PopSprite *getPopStarSprite(cocos2d::Size size,cocos2d::Point touch);
    //创建一个数组存放点击的pop
    cocos2d::__Array*popsArr;
    //通过传体过来的pop获取它的上下左右数据
    cocos2d:: __Array *checkPopUDLR(PopSprite*pop);
    
    //通过检测到的上下左右数据来循环每一个pop的上下左右
    void checkPopISNEW(cocos2d::__Array*arrold);
    
    //让空白部分被上面填充
    void reDiessPopStar();
    void reDiessPopStarRun(int x);
    //空白左移
    void reDiessPopStarRT();
    //判断游戏是否可以继续
    bool reGameOver();
    
};

#endif // __HELLOWORLD_SCENE_H__
