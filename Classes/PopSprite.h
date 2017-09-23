//
//  PopSprite.h
//  MyPopStar
//
//  Created by apple on 2017/9/20.
//
//

#ifndef PopSprite_h
#define PopSprite_h
#include "cocos2d.h"
class PopSprite : public cocos2d::Sprite{
public:
    static PopSprite *createPopSprite(int numbers, int width,int height,float PopSpriteX,float PopSpriteY);
    virtual bool init();
    CREATE_FUNC(PopSprite);
    //获取数字
    int getNumber();
    void setNumber(int num);
    //获取色块的坐标
    cocos2d::Point getColorBGPoint();
    //获取pop的位置
    int popX, popY;
    int getPOPX();
    int getPOPY();
    void setPOPX(int x);
    void setPOPY(int y);
//    void enemyInit(int numbers, int width, int height,float PopSpriteX,float PopSpriteY);
    
private:
    //显示的颜色
    int number;
    
    //显示的背景
    cocos2d::LayerColor *layColorBG;
    
    void enemyInit(int numbers, int width, int height,float PopSpriteX,float PopSpriteY);
    

};

#endif /* PopSprite_h */
