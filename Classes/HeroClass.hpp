#ifndef __HERO_CLASS__
#define __HERO_CLASS__
#include "cocos2d.h"
#include "AniReader.hpp"
USING_NS_CC;
class Hero:public CCNode{
public:
	CCTexture2D* texture;
	CCAnimation* animation;
	CCAction* action;
	CCActionInterval* animate;
	CCSprite *sprite;
	float speed;
	int bubble_num;
	int bubble_range;
	int num;
	int direction;
	int list[100][4];
	virtual ~Hero() {}
	virtual void createhero(CCPoint a,float scale) {}
	CCAnimation* moveanimation(int);
	void moveto(CCPoint a);
	void clearMove();
	void stand();
};

CCAnimation* Hero::moveanimation(int dir)
{
	animation = CCAnimation::create();
	if (dir < 3)
	{
		animation->setDelayPerUnit(1.0/speed);
		for(int i = dir * 4; i < dir * 4 + 4; i ++)
			animation->addSpriteFrameWithTexture(texture, CCRectMake(list[i+9][0],list[i+9][1],list[i+9][2],list[i+9][3]));
	} else {
		animation->setDelayPerUnit(3.0);
		animation->addSpriteFrameWithTexture(texture, CCRectMake(list[36+(dir-3)*4][0],list[36+(dir-3)*4][1],list[36+(dir-3)*4][2],list[36+(dir-3)*4][3]));
	}
	return animation;
}

void Hero::moveto(CCPoint ptNode){
	if(action!=NULL)return;
	CCMoveTo *move = CCMoveTo::create(ccpDistance(sprite->getPosition(),ptNode)/200, ptNode);
	CCFiniteTimeAction *clearmove=CCCallFuncN::create(this,callfuncN_selector(Hero::clearMove));
	action=CCSequence::create(move,clearmove,NULL);
	sprite->runAction(action);
	sprite->setFlipX(ptNode.x<sprite->getPosition().x);
	bool t = true;
	if (ptNode.y < sprite->getPosition().y)
	{
		if (direction == 1)
			t = false;
		direction = 1;
	} else if (ptNode.y > sprite->getPosition().y)
	{
		if (direction == 0)
			t = false;
		direction = 0;
	} else
	{
		if (direction == 2)
			t = false;
		direction = 2;
	}
	if (t)
	{
		sprite->stopAction(animate);
		animate = CCRepeatForever::create(CCAnimate::create(moveanimation(direction)));
		sprite->runAction(animate);
	}

}

void Hero::clearMove(){
	sprite->stopAction(action);
	action=NULL;
}

void Hero::stand() {
	if (direction == 5) return;
	sprite->stopAction(animate);
	animate = CCRepeatForever::create(CCAnimate::create(moveanimation(direction+3)));
	sprite->runAction(animate);
	direction = 5;
}
#endif
