#ifndef __BUBBLE_CLASS
#define __BUBBLE_CLASS
#include "cocos2d.h"
USING_NS_CC;
using namespace CocosDenshion;
class Bubble : public CCNode{
public:
	Bubble(CCPoint a,float scale,int type,int r);
	CCSprite *sprite;
	CCTexture2D *texture;
	CCAnimation *animation;
	CCActionInterval* animate;
	CCFiniteTimeAction *delay;
	CCAction *action;
	float time;
	int num;
	int list[100][4];
	int range;
	void bomb();
};
Bubble::Bubble(CCPoint a,float scale,int type,int r){

	sprite=CCSprite::create();
	sprite->setPosition(a);
	sprite->setScale(scale);
	time = 3.0;
	range = r;
	AniReader::read("unit_bombwater.ani");
	num = AniReader::num;
	for (int i = 0; i < 100; i++)
		for(int j = 0; j < 4; j++)
		{
			list[i][j] = AniReader::list[i][j];
		}
	texture = CCTextureCache::sharedTextureCache()->addImage("image/unit/unit_bombwater.png");
	animation = CCAnimation::create();
	animation->setDelayPerUnit(0.2f);
	for(int i = 1; i <= 4; i++)
	animation->addSpriteFrameWithTexture(texture,CCRectMake(list[i][0],list[i][1],list[i][2],list[i][3]));
	animate = CCRepeatForever::create(CCAnimate::create(animation));
	sprite->runAction(animate);
	/*delay = CCDelayTime::create(time);
	CCFiniteTimeAction* bomb = CCCallFuncN::create(this,callfuncN_selector(Bubble::bomb));
	action = CCSequence::create(delay,bomb);
	sprite->runAction(action);*/


	/*float w = texture->getContentSize().width / 2;
	float h = texture->getContentSize().height;

	animation->setDelayPerUnit(0.2f);
	for(int i = 0; i <2; i ++)
		animation->addSpriteFrameWithTexture(texture, CCRectMake(i * w, 0, w, h));
	CCAnimate *animate = CCAnimate::create(animation);
	sprite->runAction(CCRepeatForever::create(animate));*/
}

void Bubble::bomb()
{
	sprite->stopAction(animate);
	animation = CCAnimation::create();
	animation->setDelayPerUnit(0.1f);
	for(int i = 0; i < 3; i++)
		animation->addSpriteFrameWithTexture(texture,CCRectMake(list[i+5][0],list[i+5][1],list[i+5][2],list[i+5][3]));
	animate = CCAnimate::create(animation);
	sprite->runAction(animate);
	//animat
}
#endif
