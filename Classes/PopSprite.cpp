//
//  PopSprite.cpp
//  MyPopStar
//
//  Created by apple on 2017/9/20.
//
//

#include <stdio.h>
#include "PopSprite.h"
USING_NS_CC;

PopSprite *PopSprite :: createPopSprite(int numbers, int width,int height,float PopSpriteX,float PopSpriteY){
    PopSprite *enemy = new PopSprite();
    if (enemy && enemy->init()) {
        enemy -> autorelease();
        enemy -> enemyInit(numbers, width, height, PopSpriteX, PopSpriteY);
        return enemy;
        
    }
    CC_SAFE_DELETE(enemy);
    return NULL;
}

bool PopSprite::init(){
    if (!Sprite :: init()) {
        return false;
    }
    return true;
}

int PopSprite::getNumber(){
    return number;
}

void PopSprite::setNumber(int num){
    number = num;
    //判断数字给调整格子颜色
    if (number == -1) {
        layColorBG->setColor(cocos2d::Color3B(200,190,180));
    }
    
    if (number == 0) {
         layColorBG->setColor(cocos2d::Color3B(250,130,40));
    }
    if (number == 1) {
        layColorBG->setColor(cocos2d::Color3B(40,180,250));
    }
    if (number == 2) {
        layColorBG->setColor(cocos2d::Color3B(130,220,110));
    }
    if (number == 3) {
        layColorBG->setColor(cocos2d::Color3B(250,80,130));
    }
    if (number == 4) {
        layColorBG->setColor(cocos2d::Color3B(180,50,250));
    }
}
void PopSprite::enemyInit(int numbers, int width, int height, float PopSpriteX, float PopSpriteY){
    number = numbers;
    popX = 0;
    popY = 0;
    CCLOG("坐标：width:%d----PopSpriteX:%f---PopSpriteY:%.0f\n",width,PopSpriteX,PopSpriteY);
    layColorBG = cocos2d::LayerColor::create(cocos2d::Color4B(200, 190, 180, 255), width-5, height-5);
    layColorBG->setPosition(PopSpriteX, PopSpriteY);
    layColorBG->setAnchorPoint(Vec2(0, 0));
    this->addChild(layColorBG);
}

cocos2d::Point PopSprite:: getColorBGPoint(){
    
    return layColorBG->getPosition();
}

int PopSprite:: getPOPX(){
    return popX;
}
int PopSprite:: getPOPY(){
    return popY;
}

void PopSprite::setPOPX(int x)
{
    popX = x;
}
void PopSprite:: setPOPY(int y){
    popY = y;
}

