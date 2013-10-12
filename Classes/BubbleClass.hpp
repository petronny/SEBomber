#ifndef __BUBBLE_CLASS__
#define __BUBBLE_CLASS__
#include "cocos2d.h"
USING_NS_CC;
using namespace CocosDenshion;
class Bubble{
	Bubble(int type,float time,int range,CCPoint a);
	CCSprite *bubble;
};
Bubble::Bubble(int type,float time,int range,CCPoint a){
	bubble=CCSprite::create();
	CCTexture2D *texture = CCTextureCache::sharedTextureCache()->addImage("image/unit/green_bird.png");
	float w = texture->getContentSize().width / 2;
	float h = texture->getContentSize().height;
	CCAnimation *animation = CCAnimation::create();
	animation->setDelayPerUnit(0.2f);
	for(int i = 0; i <2; i ++)
		animation->addSpriteFrameWithTexture(texture, CCRectMake(i * w, 0, w, h));
	CCAnimate *animate = CCAnimate::create(animation);
	bubble->runAction(CCRepeatForever::create(animate));
}
#endif
